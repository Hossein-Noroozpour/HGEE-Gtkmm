#ifndef HGETERRAINSUNSHADER_HPP
#define	HGETERRAINSUNSHADER_HPP
#include "hge-math.hpp"
#include "hge-main-window.hpp"
#include "hge-shader-unit.hpp"
#define HGETERRAINSUNSHADERDEBUGMODE
#define HGETERRAINSUNSHADERNUMBEROFTEXTURES 8
#define HGEPRINTCODELINE std::cout << "Debugging: file:" << __FILE__ << " line:" << __LINE__ << std::endl << std::flush;
/*
 * \TODO must have a good initializing and removing
 * all program must be removed!!
 */
namespace hge
{
	namespace shader
	{
		class TerrainSunShader : public ShaderUnit
		{
		private:
			/// Model View Projection Matrix Uniform Location
			GLuint mvpmul;
			/// Model Matrix Uniform Location
			GLuint mmul;
			/// Sun Light Direction Location
			GLuint sldul;
			/// Camera Position Relative To Model
			GLuint cprtmul;
			/// Level Of Detail Number
			GLuint lodnul;
			GLuint shaderProgram;
			GLuint vertexShaderProgram;
			GLuint geometryShaderProgram;
			GLuint fragmentShaderProgram;
			/// texture Sampler Location
			GLuint tsl[HGETERRAINSUNSHADERNUMBEROFTEXTURES];
		public:
			///\note You must initialize OpenGL before call of this function.
			TerrainSunShader();
			~TerrainSunShader();
			void setModelMatrix(const glm::mat4 &modelMatrix);
			void setModelViewProjectionMatrix(const glm::mat4 &modelViewProjectionMatrix);
			void setLODNumber(const GLuint& lodNumber);
			void setSunLightDirection(const glm::vec3 &sunDirection);
			void setCameraPositionRelativeToModel(const glm::vec3 &p);
			void use();
			GLuint getModelViewProjectionMatrixUniformLocation();
			GLuint getModelMatrixUniformLoaction();
			GLuint getVertexShaderProgram();
			GLuint getGeometryShaderProgram();
			GLuint getFragmentShaderProgram();
			GLuint getShaderProgram();
			GLuint* getTextureSamplerLocations();
			std::string readShaderFile(const std::string &fileName);
		};
	}
}
#endif
