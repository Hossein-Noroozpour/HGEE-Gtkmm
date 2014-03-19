#ifndef HGETEXTUREUNIT_HPP
#define	HGETEXTUREUNIT_HPP
#include "hge-main-window.hpp"
#include <string>
#include <ImageMagick-6/Magick++.h>
namespace hge
{
	namespace texture
	{
		class TextureUnit
		{
		public:
			TextureUnit(GLenum TextureTarget, const std::string& FileName);
			bool load();
			void bind(GLenum TextureUnit);
		private:
			std::string m_fileName;
			GLenum m_textureTarget;
			GLuint m_textureObj;
			Magick::Image* m_pImage;
			Magick::Blob m_blob;
		};
	}
}
#endif	/* TEXTURE_H */
