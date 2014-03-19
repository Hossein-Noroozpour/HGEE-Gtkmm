#ifndef HGEMESHUNIT_HPP
#define HGEMESHUNIT_HPP
#include "hge-main-window.hpp"
//#define HGEMESHDEBUG
//#define HGEOPENGLDEBUGMESH
namespace hge
{
	namespace render
	{
		class MeshUnit
		{
		public:
			///\warning Do not use this ever, this function is only for
			/// internal use.
			MeshUnit();
			///\warning If you do not use this function properly
			/// it will cause core dump!
			MeshUnit(
					const GLfloat* const& vertices,
					const GLuint* const& indices,
					const GLuint& verticesByteSize,
					const GLuint& verticesNumber,
					const GLuint& indicesByteSize);
			~MeshUnit();
			void bindVBO();
			void bindIBO();
			void bindTotal();
			void draw();
			GLuint getVBO();
			GLuint getIBO();
		private:
			GLuint vbo, ibo, vboSize, vboElementsNumber, iboSize, numberOfIndices;
		};
	}
}
#endif
