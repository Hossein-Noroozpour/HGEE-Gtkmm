#include "hge-total-shader.hpp"
#include "hge-shader-engine.hpp"
#include <iostream>
#include <cassert>
#define HGEPRINTCODELINE std::cout << "Debugging: file:" << __FILE__ << " line:" << __LINE__ << std::endl << std::flush;
hge::shader::TotalShader::TotalShader():
	modelMatrix(glm::mat4(1.0f)),
	modelViewProjectionMatrix(glm::mat4(1.0f)),
	sunLightDirection(glm::vec3(1.0f)),
	shadingMode(fullShadingMode)
{
	std::string pVS(
		"#version 430\n"
		"layout (location = 0) in vec3 vertex;"
		///\WARNING All of the normals must be normalized.
		"layout (location = 1) in vec3 normal;"
		"layout (location = 2) in vec2 uv;"
		"out vec2 outUV;"
		"out float lightIntensity;"
		"uniform mat4 modelViewProjectionMatrix;"
		"uniform mat4 modelMatrix;"
		"uniform uint shadingMode;"
		///\WARNING Must be normalized.
		"uniform vec3 sunLightDirection;"
		"void main()"
		"{"
			"switch(shadingMode)"
			"{"
				//Full Shading Mode
				"case 0 :"
					"vec3 modelNormal = vec3(modelMatrix * vec4(normal, 1.0));"
					"float dotProductNormalSun = float(dot(sunLightDirection, modelNormal));"
					"lightIntensity = float(max(dotProductNormalSun, 0.1));"
					"gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);"
					"outUV = uv;"
					"break;"
				//Occlusion Query Shading Mode
				"case 1 :"
					"gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);"
					"break;"
			"}"
		"}");
	///////////////////////////////////////////////////////////////////////
	std::string pFS(
		"#version 430\n"
		"in vec2 outUV;"
		"out vec4 fragColor;"
		"in float lightIntensity;"
		"uniform sampler2D mainTextureSampler;"
		"uniform uint shadingMode;"
		"void main()"
		"{"
			"switch(shadingMode)"
			"{"
				//Full Shading Mode
				"case 0 :"
					"vec4 tmpColor = texture2D( mainTextureSampler, outUV.xy );"
					"fragColor =  tmpColor * lightIntensity;"
					"break;"
				//Occlusion Query Shading Mode
				"case 1 :"
					"fragColor = vec4(1.0);"
					"break;"
			"}"
		"};");
	///////////////////////////////////////////////////////////////////////
	vertexShader = render::ShaderEngine::addShaderToProgram(pVS, GL_VERTEX_SHADER, shaderProgram);
	fragmentShader = render::ShaderEngine::addShaderToProgram(pFS, GL_FRAGMENT_SHADER, shaderProgram);
	hge::render::ShaderEngine::run(shaderProgram);
	//Model Matrix Uniform Location
	modelMatrixUniformLoaction =
		hge::render::ShaderEngine::getUniformLocation(
			std::string("modelMatrix"), shaderProgram);
	assert(modelMatrixUniformLoaction != 0xFFFFFFFF);
	//Model View Projection Matrix Uniform Location
	modelViewProjectionMatrixUniformLocation =
		hge::render::ShaderEngine::getUniformLocation(
			std::string("modelViewProjectionMatrix"), shaderProgram);
	assert(modelViewProjectionMatrixUniformLocation != 0xFFFFFFFF);
	//Sun Light Direction Uniform Location
	sunLightDirectionUniformLocation =
		hge::render::ShaderEngine::getUniformLocation(
			std::string("sunLightDirection"), shaderProgram);
	assert(sunLightDirectionUniformLocation != 0xFFFFFFFF);
	//Texture Sampler Uniform Location
	mainTextureSamplerLocation =
		hge::render::ShaderEngine::getUniformLocation(
			std::string("mainTextureSampler"), shaderProgram);
	assert(mainTextureSamplerLocation != 0xFFFFFFFF);
	shadingModeUniformLocation =
		hge::render::ShaderEngine::getUniformLocation(
			std::string("shadingMode"), shaderProgram);
	assert(shadingModeUniformLocation != 0xFFFFFFFF);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glUniformMatrix4fv(modelMatrixUniformLoaction, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(modelViewProjectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));
	glUniform3fv(sunLightDirectionUniformLocation, 1, glm::value_ptr(sunLightDirection));
	glUniform1i(mainTextureSamplerLocation, 0);
	glUniform1ui(shadingModeUniformLocation, 0);
	//Full Shading Mode
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glUseProgram(shaderProgram);
}
hge::shader::TotalShader::~TotalShader()
{
	hge::render::ShaderEngine::endObject(vertexShader);
	hge::render::ShaderEngine::endObject(fragmentShader);
	hge::render::ShaderEngine::endProgram(shaderProgram);
}
void hge::shader::TotalShader::setModelMatrix(const glm::mat4& m)
{
	modelMatrix = m;
	//???????????????????????????????????????????????????????????????????????????????????????????
	glUniformMatrix4fv(modelMatrixUniformLoaction, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}
void hge::shader::TotalShader::setModelViewProjectionMatrix(const glm::mat4& m)
{
	modelViewProjectionMatrix = m;
	//???????????????????????????????????????????????????????????????????????????????????????????
	glUniformMatrix4fv(modelViewProjectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));
}
void hge::shader::TotalShader::changeSunLightDirection(const glm::vec3 &s)
{
	sunLightDirection = s;
	//?????????????????????????????????????????????????????????????????????
	glUniform3fv(sunLightDirectionUniformLocation, 1, glm::value_ptr(sunLightDirection));
}
void hge::shader::TotalShader::use()
{
	glUseProgram(shaderProgram);
}
GLuint hge::shader::TotalShader::getModelViewProjectionMatrixUniformLocation()
{
	return modelViewProjectionMatrixUniformLocation;
}
GLuint hge::shader::TotalShader::getModelMatrixUniformLoaction()
{
	return modelMatrixUniformLoaction;
}
GLuint hge::shader::TotalShader::getTextureSamplerLocation()
{
	return mainTextureSamplerLocation;
}
GLuint hge::shader::TotalShader::getShadingModeUniformLocation()
{
	return shadingModeUniformLocation;
}
GLuint hge::shader::TotalShader::getVertexShader()
{
	return vertexShader;
}
GLuint hge::shader::TotalShader::getFragmentShader()
{
	return fragmentShader;
}
GLuint hge::shader::TotalShader::getShaderProgram()
{
	return shaderProgram;
}
void hge::shader::TotalShader::goToFullShadingMode()
{
	glUniform1ui(shadingModeUniformLocation, 0);
	shadingMode = fullShadingMode;
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
}
void hge::shader::TotalShader::goToOcclusionQueryShadingMode()
{
	glUniform1ui(shadingModeUniformLocation, 1);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	shadingMode = occlusionQueryShadingMode;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
}
void hge::shader::TotalShader::goToBakeShadowToTextureShadingMode()
{
	glUniform1ui(shadingModeUniformLocation, 2);
	///\TODO not completed! Need some reconsideration.
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	shadingMode = bakeShadowToTextureShadingMode;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
}
