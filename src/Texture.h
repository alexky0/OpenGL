#pragma once
#include <string>

class Texture
{
private:
	unsigned int m_rendererID;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_bitsPerPix;
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline unsigned int getWidth() const { return m_width; }
	inline unsigned int getHeight() const { return m_height; }
};