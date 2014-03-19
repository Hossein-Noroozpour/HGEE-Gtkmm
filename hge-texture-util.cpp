#include "hge-texture-util.hpp"
#include <cstring>
/// Equivalent to "DXT1" in ASCII
const GLuint hge::texture::TextureUtil::FOURCC_DXT1 = 0x31545844;
/// Equivalent to "DXT3" in ASCII
const GLuint hge::texture::TextureUtil::FOURCC_DXT3 = 0x33545844;
/// Equivalent to "DXT5" in ASCII
const GLuint hge::texture::TextureUtil::FOURCC_DXT5 = 0x35545844;

/// Temporary types. Must be corrected soon.
GLuint hge::texture::TextureUtil::loadDDS(const char * const & imagepath)
{
	//variables
	unsigned int header[124/sizeof(unsigned int)];
	FILE *fp;
	char filecode[4];
	unsigned int height;
	unsigned int width;
	unsigned int linearSize;
	unsigned int mipMapCount;
	unsigned int fourCC;
	unsigned char * buffer;
	unsigned int bufsize;
	//unsigned int components;???????????
	unsigned int format;
	unsigned int blockSize;
	unsigned int offset = 0;
	unsigned int tmpint;
	//////////////////////////////
	fp = fopen(imagepath, "r");
	if (fp == NULL)
	{
		std::cout << "Error in opening texture file." << std::endl;
		std::cout << "Line: " << __LINE__ << "  File: ";
		std::cout << __FILE__ << std::endl;
		exit(EXIT_FAILURE);
	}
	tmpint = fread(filecode, 1, 4, fp);
	if(tmpint == 0)
	{
		std::cout << "Error in reading texture file." << std::endl;
		std::cout << "Line: " << __LINE__ << "  File: ";
		std::cout << __FILE__ << std::endl;
		fclose(fp);
		exit(EXIT_FAILURE);
	}
	if (strncmp(filecode, "DDS ", 4) != 0)
	{
		std::cout << "Error wrong format for texture file." << std::endl;
		std::cout << "Line: " << __LINE__ << "  File: ";
		std::cout << __FILE__ << std::endl;
		fclose(fp);
		exit(EXIT_FAILURE);
	}
	tmpint      = fread(&header, 124, 1, fp);
	if(tmpint == 0)
	{
		std::cout << "Error in reading texture file." << std::endl;
		std::cout << "Line: " << __LINE__ << "  File: ";
		std::cout << __FILE__ << std::endl;
		fclose(fp);
		exit(EXIT_FAILURE);
	}
	height      = header[8/sizeof(unsigned int)];
	width       = header[12/sizeof(unsigned int)];
	linearSize  = header[16/sizeof(unsigned int)];
	mipMapCount = header[24/sizeof(unsigned int)];
	fourCC      = header[80/sizeof(unsigned int)];
	bufsize     = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer      = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	tmpint      = fread(buffer, 1, bufsize, fp);
	if(tmpint == 0)
	{
		std::cout << "Error in reading texture file." << std::endl;
		std::cout << "Line: " << __LINE__ << "  File: ";
		std::cout << __FILE__ << std::endl;
		fclose(fp);
		exit(EXIT_FAILURE);
	}
	fclose(fp);
	//components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
	switch(fourCC)
	{
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			free(buffer);
			return 0;
	}
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
		glCompressedTexImage2D(
				GL_TEXTURE_2D, level, format, width,
				height,0, size, buffer + offset);
		offset += size;
		width  /= 2;
		height /= 2;
	}
	free(buffer);
	return textureID;
}