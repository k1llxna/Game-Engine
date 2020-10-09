#include "OctSpacialPartition.h"

int OctNode::childNum = 0;

OctNode::OctNode(glm::vec3 position_, float size_, OctNode* parent_) : octBounds(nullptr), parent(nullptr), children(), objectList(std::vector<GameObject*>())
{
	objectList.reserve(10);
	octBounds = new BoundingBox;
	octBounds->minVert = position_;
	octBounds->maxVert = position_ + glm::vec3(size_);

	size = size_;
	parent = parent_;

	for (int i = 0; i < CHILDREN_NUM; i++) {
		children[i] = nullptr;
	}
}

OctNode::~OctNode()
{
	OnDestroy();
}

void OctNode::OnDestroy()
{
	delete octBounds;
	octBounds = nullptr;

	if (objectList.size() > 0) {
		for (auto obj : objectList) {
			obj = nullptr;
		}
		objectList.clear();
	}

for (int i = 0; i < CHILDREN_NUM; i++) {
	if (children[i] != nullptr) {
		delete children[i];
	}
	children[i] = nullptr;
}
}

void OctNode::Octify(int depth_) // creates children (recursive)
{
	if (depth_ > 0 && this) {
		float half = size / 2.0f;

		// top
		children[static_cast<int>(OctChildren::OCT_TLF)] = new OctNode(glm::vec3(octBounds->minVert.x,        octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
		children[static_cast<int>(OctChildren::OCT_TRF)] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
		children[static_cast<int>(OctChildren::OCT_TLR)] = new OctNode(glm::vec3(octBounds->minVert.x,        octBounds->minVert.y + half, octBounds->minVert.z), half, this);
		children[static_cast<int>(OctChildren::OCT_TRR)] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z), half, this);

		// bottom
		children[static_cast<int>(OctChildren::OCT_BLF)] = new OctNode(glm::vec3(octBounds->minVert.x,        octBounds->minVert.y, octBounds->minVert.z + half), half, this);
		children[static_cast<int>(OctChildren::OCT_BRF)] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y, octBounds->minVert.z + half), half, this);
		children[static_cast<int>(OctChildren::OCT_BLR)] = new OctNode(glm::vec3(octBounds->minVert.x,        octBounds->minVert.y, octBounds->minVert.z), half, this);
		children[static_cast<int>(OctChildren::OCT_BRR)] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y, octBounds->minVert.z), half, this);

		childNum += 8;
	}

	if (depth_ > 0 && this) {
		for (int i = 0; i < CHILDREN_NUM; i++) {
			children[i]->Octify(depth_ - 1);
		}
	}
}

void OctNode::AddCollisionObject(GameObject* obj_)
{
	objectList.push_back(obj_);
}

OctNode* OctNode::GetParent()
{
	return parent;
}

OctNode* OctNode::GetChild(OctChildren childPos_)
{
	return children[static_cast<int>(childPos_)];
}

int OctNode::GetObjectCount() const
{
	return objectList.size();
}

int OctNode::GetChildCount() const
{
	return childNum;
}

bool OctNode::IsLeaf() const
{
	if (children[0] == nullptr) {
		return true;
	}
	return false;
}

BoundingBox* OctNode::GetBoundingBox() const
{
	return octBounds;
}


OctSpacialPartition::OctSpacialPartition(float worldSize_) : root(nullptr), rayIntersectionList(std::vector<OctNode*>())
{
	root = new OctNode(glm::vec3(-(worldSize_ / 2.0f)), worldSize_, nullptr); // ex worldsize = 100 then cubes will range -50 to +50
	root->Octify(3);
	std::cout << "There are " << root->GetChildCount() << " child Nodes" << std::endl;

	rayIntersectionList.reserve(20);
}

OctSpacialPartition::~OctSpacialPartition()
{
	OnDestroy();
}

void OctSpacialPartition::OnDestroy()
{
	if (rayIntersectionList.size() > 0) {
		for (auto cell : rayIntersectionList) {
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}

	delete root;
	root = nullptr;
}

void OctSpacialPartition::AddObject(GameObject* obj_)
{
	AddObjectToCell(root, obj_);
}

GameObject* OctSpacialPartition::GetCollision(Ray ray_)
{
	if (rayIntersectionList.size() > 0){
		for (auto cell : rayIntersectionList) {
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}
	PrepareCollisionQuery(root, ray_);

	GameObject* result = nullptr;

	float shortestDistance = FLT_MAX;

	for (auto cell : rayIntersectionList) {
		for (auto obj : cell->objectList) {
			if (ray_.IsColliding(&obj->GetBoundingBox())) {
				if (ray_.intersectionDistance < shortestDistance) {
					result = obj;
					shortestDistance = ray_.intersectionDistance;
				}
			}
		}
		if (result != nullptr) {
			return result;
		}
	}
	return nullptr;
}

void OctSpacialPartition::AddObjectToCell(OctNode* cell_, GameObject* obj_)
{ // check obj intersect w cell -> if leaf node then add, else go all children find which is the leaf
	if (cell_) {

		if (cell_->GetBoundingBox()->Intersects(&obj_->GetBoundingBox())) {
			if (cell_->IsLeaf()) {
				cell_->AddCollisionObject(obj_);
			}
			else {
				for (int i = 0; i < 8; i++) {
					cell_->GetChild(static_cast<OctChildren>(i))->AddCollisionObject(obj_); //
					std::cout << obj_->GetTag() << " was added" << std::endl; // check
				}
			}
		}				
	}
}

void OctSpacialPartition::PrepareCollisionQuery(OctNode* cell_, Ray ray_)
{ // go through all cells, look for leaf
	if (cell_) { // != nullptr
		BoundingBox* currentCell = cell_->GetBoundingBox();
		
		// check if ray collids w octnode bounding box
		if (ray_.IsColliding(currentCell)) {
			if (cell_->IsLeaf()) {
				rayIntersectionList.push_back(cell_);
			}
			else {
				for (int i = 0; i < 8; i++) {
					rayIntersectionList.push_back(cell_->GetChild(static_cast<OctChildren>(i)));
				}
			}
		}
	}
}