#pragma once
#include <string>
#include <unordered_map>

struct ShaderSrc
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	std::string m_filePath;
	unsigned int m_rendererID;
	std::unordered_map<std::string, int> m_locationCache;
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int i);
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
private:
	ShaderSrc ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, std::string& str);
	unsigned int CreateShader(std::string& vertexShader, std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
};