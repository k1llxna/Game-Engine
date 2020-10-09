#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel()
{
	currentTexture = 0;
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel()
{
	OnDestroy();
}

void LoadOBJModel::LoadModel(const std::string & objFilePath_, const std::string & mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

void LoadOBJModel::LoadModel(const std::string & filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);


	if (!in) {
		Debug::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
	}

	float tempV = 0; // for sorting min/max data
	std::string line;
	
	while (std::getline(in, line)) {
		// v
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));

			float x, y, z;
			v >> x >> y >> z;

			vertices.push_back(glm::vec3(x, y, z));		

			// starting value
			if (tempV == 0) {
				box.minVert.x = x;
				box.minVert.y = y;
				box.minVert.z = z;
			}

			// x
			if (box.minVert.x > x) {
				box.minVert.x = x;
			}
			if (box.maxVert.x < x) {
				box.maxVert.x = x;
			}

			// y
			if (box.minVert.y > y) {
				box.minVert.y = y;
			}
			if (box.maxVert.y < y) {
				box.maxVert.y = y;
			}

			// z
			if (box.minVert.z > z) {
				box.minVert.z = z;
			}
			if (box.maxVert.z < z) {
				box.maxVert.z = z;
			}
			tempV = 1;
		}

		// n
		else if (line.substr(0, 3) == "vn ")
		{
			std::stringstream vn(line.substr(2));

			float x, y, z;
			vn >> x >> y >> z;		
		
			normals.push_back(glm::vec3(x, y, z));
		}

		// t
		else if (line.substr(0, 3) == "vt ")
		{
			std::stringstream vt(line.substr(2));
			
			float x, y;
			vt >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}

		// f
		else if (line.substr(0, 2) == "f ") {
			std::string data = line.substr(2);
			int currentEndPos = 0;
			while ((currentEndPos = data.find(' ')) != std::string::npos) {
				std::string chunk = data.substr(0, currentEndPos);
				int subEndPos = 0;
				int vector = 0;

				for (int i = 0; i < 3; i++) {
					int pushBack;
					if ((subEndPos = chunk.find('/')) != std::string::npos) {

						pushBack = std::stoi(chunk.substr(0, subEndPos));

						chunk.erase(0, subEndPos + 1);
					}
					else {
						pushBack = std::stoi(chunk);
					}

					pushBack--;

					switch (i) {
					default:
					case 0:
						indices.push_back(pushBack);
						break;
					case 1:
						textureIndices.push_back(pushBack);
						break;
					case 2:
						normalIndices.push_back(pushBack);
						break;
					}
				}
				vector = 0;
				data.erase(0, currentEndPos + 1);
			}
		}
		//NEW MESH
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

std::vector<Vertex> LoadOBJModel::GetVerts()
{
	return meshVertices;
}

std::vector<int> LoadOBJModel::GetIndices()
{
	return indices;
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox()
{
	return box;
}

void LoadOBJModel::OnDestroy()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::PostProcessing() // convert data to obj
//	  1  	//	 1    //	1
// indices // normal // texture
{
	for (int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh subMesh;
	subMesh.vertexList = meshVertices;
	subMesh.meshIndices = indices;
	subMesh.textureID = currentTexture;

	subMeshes.push_back(subMesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentTexture = 0;
}

void LoadOBJModel::LoadMaterial(const std::string & matName_)
{
	currentTexture = TextureHandler::GetInstance()->GetTexture(matName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(matName_, "./Resources/Textures/" + matName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(matName_);
	}
}

void LoadOBJModel::LoadMaterialLibrary(const std::string & matFilePath_)
{
	std::ifstream in(matFilePath_.c_str(), std::ios::in); 

	if (!in) {
		Debug::Warning("Cannot open MTL file: " + matFilePath_, "LoadOBJModel.cpp", __LINE__);
	}

	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			LoadMaterial(line.substr(7));
		}
	 }
}