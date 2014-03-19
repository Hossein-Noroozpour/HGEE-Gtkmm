#ifndef HGETOTALSHADER_HPP
#define	HGETOTALSHADER_HPP
#include "hge-math.hpp"
#include "hge-shader-engine.hpp"
namespace hge
{
	namespace shader
	{
		class TotalShader
		{
		public:

			enum ShadingMode
			{
				fullShadingMode,
				occlusionQueryShadingMode,
				bakeShadowToTextureShadingMode
			};

		private:

			GLuint modelViewProjectionMatrixUniformLocation;
			GLuint modelMatrixUniformLoaction;
			GLuint sunLightDirectionUniformLocation;
			GLuint mainTextureSamplerLocation;
			GLuint shadingModeUniformLocation;

			GLuint vertexShader;
			GLuint fragmentShader;
			GLuint shaderProgram;

			glm::mat4 modelMatrix;
			glm::mat4 modelViewProjectionMatrix;
			glm::vec3 sunLightDirection;

			ShadingMode shadingMode;

		public:

			///\note You must have initialized OpenGL before calling this function.
			TotalShader();
			~TotalShader();

			void setModelMatrix(const glm::mat4 &modelMatrix);
			void setModelViewProjectionMatrix(const glm::mat4 &modelViewProjectionMatrix);
			void changeSunLightDirection(const glm::vec3 &sun_dir);

			void use();

			GLuint getModelViewProjectionMatrixUniformLocation();
			GLuint getModelMatrixUniformLoaction();
			GLuint getTextureSamplerLocation();
			GLuint getShadingModeUniformLocation();

			GLuint getVertexShader();
			GLuint getFragmentShader();
			GLuint getShaderProgram();

			void goToFullShadingMode();
			void goToOcclusionQueryShadingMode();
			void goToBakeShadowToTextureShadingMode();

			ShadingMode getShadingMode();
		};
	}
}
#endif
