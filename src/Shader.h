#pragma once
#include <glad/glad.h>

#include "glm/glm.hpp"

#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FramgentSource;
};


class Shader
{
private:
	unsigned int m_RendererID;
	// caching for uniforms
	std::unordered_map <std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	unsigned int getID() { return m_RendererID; }

	// Set uniforms
	void SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4);
	void SetUniform3f(const std::string& name, float f1, float f2, float f3);
	void SetUniform2f(const std::string& name, float f1, float f2);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform1i(const std::string& name, int value);
	void SetUniformMatrix4fv(const std::string& name, glm::mat4 matrix);

private:
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name);
};