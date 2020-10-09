#include "TextureHandler.h"

std::unique_ptr<TextureHandler> TextureHandler::textureInstance = nullptr;
std::vector<Texture*> TextureHandler::textures = std::vector<Texture*>();

TextureHandler::TextureHandler()
{
	textures.reserve(10); // change more later
}

TextureHandler::~TextureHandler()
{
	if (textureInstance == nullptr) {
		OnDestroy();
	}
}

TextureHandler* TextureHandler::GetInstance() {
	if (textureInstance.get() == nullptr) {
		textureInstance.reset(new TextureHandler);
	}
	return textureInstance.get();
}

void TextureHandler::OnDestroy() {
	if (textures.size() > 0) {
		for (auto t : textures) {
			glDeleteTextures(sizeof(GLuint), &t->textureID);
			delete t;
			t = nullptr;
		}
		textures.clear();
	}
}

void TextureHandler::CreateTexture(const std::string& textureName_, const std::string& textureFilePath_) {
	// creat texture object
	Texture* t = new Texture();
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(textureFilePath_.c_str()); // try finding this texture

	if (!surface) { // == nullptr
		Debug::Error("Surface for texture " + textureName_ + " failed to be created", "TextureHandler.cpp", __LINE__);
		delete t;
		t = nullptr;
		return;
	}

	// generate text from opengl
	glGenTextures(1, &t->textureID); // ONLY 2D
	glBindTexture(GL_TEXTURE_2D, t->textureID);
	int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB; // mode = rgba OR rgb

	//	text target(2d,3d), mipmap lvl(detail lvl), format (rgba/rgb), width, height, 0, image data format, data type, actual img data
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels); //

	// set up options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//create mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	//close door
	glBindTexture(GL_TEXTURE_2D, 0);

	t->width = surface->w;
	t->height = surface->h;
	t->textureName = textureName_;

	textures.push_back(t);

	SDL_FreeSurface(surface);
	surface = nullptr;
}

const GLuint TextureHandler::GetTexture(const std::string& textureName_) {
	for (auto t : textures) {
		if (t->textureName == textureName_) {
			return t->textureID;
		}
	}
	return 0;
}

const Texture* TextureHandler::GetTextureData(const std::string textureName_) {
	for (auto t : textures) {
		if (t->textureName == textureName_) {
			return t;
		}
	}
	return nullptr; // or 0
}