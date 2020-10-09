#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <sstream>
#include <map>
#include <vector>
#include <memory>
#include <glew.h> // access gpu for shading
#include "../Core/Debug.h"

// handlers are singletons (should only be 1)
class ShaderHandler {
public:
	ShaderHandler(const ShaderHandler&) = delete;
	ShaderHandler(ShaderHandler&&) = delete;
	ShaderHandler& operator=(const ShaderHandler&) = delete;
	ShaderHandler& operator=(ShaderHandler&&) = delete;

	static ShaderHandler* GetInstance();

	void CreateProgram(
		const std::string& shaderName_, 
		const std::string& vertexShaderFileName_, 
		const std::string& fragmentShaderFileName_); 

	// use keys 
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// key(string) value = index of shader
	// call keys to render

	GLuint GetShader(const std::string& shaderName_);
	void OnDestroy(); // public

private:
	ShaderHandler();
	~ShaderHandler();

	static std::unique_ptr<ShaderHandler> shaderInstance;
	friend std::default_delete<ShaderHandler>; // access restricted constructors

	// read file
	std::string ReadShader(const std::string& filePath_);

	// create shader, no access required
	GLuint CreateShader(GLenum shaderType_, const std::string& source_, const std::string& shaderName_); // changing enum value

	// save in a map - use keys
	static std::map<std::string, GLuint> programs;
};
#endif