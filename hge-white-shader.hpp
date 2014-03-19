#ifndef HGEWHITESHADER_HPP
#define	HGEWHITESHADER_HPP
#include "hge-math.hpp"
#include "hge-main-window.hpp"
#include "hge-shader-unit.hpp"
#define HGEPRINTCODELINE std::cout << "Debugging: file:" << __FILE__ << " line:" << __LINE__ << std::endl << std::flush;
/*
 * \TODO must have a good initializing and removing
 * all program must be removed!!
 */
namespace hge
{
	namespace shader
	{
		class WhiteShader : public ShaderUnit
		{
		private:
			GLuint modelViewProjectionMatrixUniformLocation;
			GLuint shaderProgram;
			GLuint vertexShaderProgram;
			GLuint fragmentShaderProgram;
		public:
			///\note You must initialize OpenGL before call of this function.
			WhiteShader();
			~WhiteShader();
			void setModelMatrix(const glm::mat4 &modelMatrix);
			void setModelViewProjectionMatrix(const glm::mat4 &modelViewProjectionMatrix);
			void setLODNumber(const GLuint& lodNumber);
			void use();
			GLuint getModelViewProjectionMatrixUniformLocation();
			GLuint getModelMatrixUniformLoaction();
			GLuint getVertexShaderProgram();
			GLuint getGeometryShaderProgram();
			GLuint getFragmentShaderProgram();
			GLuint getShaderProgram();
		};
	}
}
#endif
