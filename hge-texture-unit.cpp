#include "hge-texture-unit.hpp"
#include <iostream>
hge::texture::TextureUnit::TextureUnit(GLenum TextureTarget, const std::string& FileName)
{
	m_textureTarget = TextureTarget;
	m_fileName      = FileName;
	m_pImage        = NULL;
}
bool hge::texture::TextureUnit::load()
{
	try {
		m_pImage = new Magick::Image(m_fileName);
		m_pImage->write(&m_blob, "RGBA");
	}
	catch (Magick::Error& Error)
	{
		std::cout << "Error loading texture '" << m_fileName << "': " << Error.what() << std::endl;
		return false;
	}
	glGenTextures(1, &m_textureObj);
	glBindTexture(m_textureTarget, m_textureObj);
	glTexImage2D(m_textureTarget, 0, GL_RGB, m_pImage->columns(), m_pImage->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
	glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(m_textureTarget);
	return true;
}
void hge::texture::TextureUnit::bind(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(m_textureTarget, m_textureObj);
}
