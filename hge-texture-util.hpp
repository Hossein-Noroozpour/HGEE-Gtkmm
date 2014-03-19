#ifndef HGETEXTUREUTIL_HPP
#define HGETEXTUREUTIL_HPP
#include "hge-main-window.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>
namespace hge
{
	namespace texture
	{
		class TextureUtil
		{
		private:
			/// Equivalent to "DXT1" in ASCII
			static const GLuint FOURCC_DXT1;
			/// Equivalent to "DXT3" in ASCII
			static const GLuint FOURCC_DXT3;
			/// Equivalent to "DXT5" in ASCII
			static const GLuint FOURCC_DXT5;
		protected:
		public:
			/// \warning this function must called after glfw and glew
			/// initialization. In addition this function seems to be not very
			/// type safe. Look in implementation.
			static GLuint loadDDS(const char * const & imagepath);
		};
	}
}
#endif
