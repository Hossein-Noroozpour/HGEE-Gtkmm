#ifndef HGESHADERUNIT_HPP
#define	HGESHADERUNIT_HPP
#include "hge-math.hpp"
#include "hge-shader-engine.hpp"
namespace hge
{
	namespace shader
	{
		class ShaderUnit
		{
		public:
			virtual void setModelMatrix(const glm::mat4 &modelMatrix) = 0;
			virtual void setModelViewProjectionMatrix(const glm::mat4 &modelViewProjectionMatrix) = 0;
			virtual void setLODNumber(const GLuint& lodNumber) = 0;
			virtual void use() = 0;
			virtual GLuint getModelViewProjectionMatrixUniformLocation() = 0;
			virtual GLuint getModelMatrixUniformLoaction() = 0;
			virtual GLuint getVertexShaderProgram() = 0;
			virtual GLuint getGeometryShaderProgram() = 0;
			virtual GLuint getFragmentShaderProgram() = 0;
			virtual GLuint getShaderProgram() = 0;
		};
	}
}
#endif
