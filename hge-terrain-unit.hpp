#ifndef HGETERRAINUNIT_HPP
#define	HGETERRAINUNIT_HPP
#include <string>
#include <vector>
#include "hge-mesh-unit.hpp"
#include "hge-model-matrix.hpp"
#include "hge-shader-unit.hpp"
#include "hge-texture-unit.hpp"
namespace hge
{
	namespace render
	{
		///\note This terrain gets meshes and shaders and in its draw-call uses each meshes and shaders with same index
		/// for rendering and all the textures will be feed to the all the shaders.
		class TerrainUnit
		{
		public:
			TerrainUnit();
			virtual ~TerrainUnit();
			virtual void draw(const glm::mat4 &vp);
			///\warning This function does not delete vertices pointer and caller must take care of it.
			virtual void setVBO    (const GLfloat *const &vertices, const GLuint &verticesBytes);
			///\warning This function does not delete indices pointer and caller must take care of it.
			virtual void addIBO    (const GLuint  *const &ibo, const GLuint &indicesBytes);
			virtual void setShader (const std::shared_ptr<shader::ShaderUnit>& s);
			virtual void addTexture(const std::shared_ptr<texture::TextureUnit>& texture);
			///\warning Do not delete this pointer.
			math::ModelMatrix* getModelMatrix();
		private:
			GLuint vboBuffer;
			GLuint numberOfIndices;
			std::vector<GLuint> iboBuffers;
			std::vector<GLuint> iboElements;
			glm::mat4 mvp;
			math::ModelMatrix modelMatrix;
			std::shared_ptr<shader::ShaderUnit> shader;
			std::vector<std::shared_ptr<texture::TextureUnit>> textures;
		};
	}
}
#endif
