#include "hge-sun-shader.hpp"
#include "hge-shader-engine.hpp"
#include <iostream>
#include <cassert>
#define HGEPRINTCODELINE std::cout << "Debugging: file:" << __FILE__ << " line:" << __LINE__ << std::endl << std::flush;
hge::shader::SunShader::SunShader(const glm::vec3 &sunDirection):
	shaderProgram(render::ShaderEngine::createProgram())
{
	std::string pVS(
		"#version 430\n"
		"layout (location = 0) in vec3 vertex;"
		//All of the normals must be normalized.
		"layout (location = 1) in vec3 normal;"
		"layout (location = 2) in vec2 uv;"
		"out vec2 outUV;"
		"out float lightIntensity;"
		"uniform mat4 mvp;"
		"uniform mat4 m;"
		//Sun direction must be normalized.
		"uniform vec3 s;"
		"void main()"
		"{"
			"lightIntensity = float(max(float(dot(s, vec3(m * vec4(normal, 1.0)))), 0.1));"
			"gl_Position = mvp * vec4(vertex, 1.0);"
			"outUV = uv;"
		"}");
	///////////////////////////////////////////////////////////////////////
	std::string pFS(
		"#version 430\n"
		"in vec2 outUV;"
		"out vec4 fragColor;"
		"in float lightIntensity;"
		"uniform sampler2D textureSampler;"
		"void main()"
		"{"
			"fragColor=texture2D(textureSampler,outUV.xy)*lightIntensity;"
		"};");
	///////////////////////////////////////////////////////////////////////
	vertexShaderProgram = render::ShaderEngine::addShaderToProgram(pVS, GL_VERTEX_SHADER, shaderProgram);
	fragmentShaderProgram = render::ShaderEngine::addShaderToProgram(pFS, GL_FRAGMENT_SHADER, shaderProgram);
	hge::render::ShaderEngine::run(shaderProgram);
	modelMatrixUniformLocation = render::ShaderEngine::getUniformLocation(std::string("m"), shaderProgram);
	assert(modelMatrixUniformLocation != 0xFFFFFFFF);
	modelViewProjectionMatrixUniformLocation = render::ShaderEngine::getUniformLocation(std::string("mvp"), shaderProgram);
	assert(modelViewProjectionMatrixUniformLocation != 0xFFFFFFFF);
	sunLightDirectionUniformLocation = render::ShaderEngine::getUniformLocation(std::string("s"), shaderProgram);
	assert(sunLightDirectionUniformLocation != 0xFFFFFFFF);
	textureSamplerLocation = render::ShaderEngine::getUniformLocation(std::string("textureSampler"), shaderProgram);
	assert(textureSamplerLocation != 0xFFFFFFFF);
	glUniform1i(textureSamplerLocation, 0);
}
hge::shader::SunShader::~SunShader()
{
	hge::render::ShaderEngine::endObject(vertexShaderProgram);
	hge::render::ShaderEngine::endObject(fragmentShaderProgram);
	hge::render::ShaderEngine::endProgram(shaderProgram);
}
void hge::shader::SunShader::setModelMatrix(const glm::mat4 &modelMatrix)
{
	glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}
void hge::shader::SunShader::setModelViewProjectionMatrix(const glm::mat4 &modelViewProjectionMatrix)
{
	glUniformMatrix4fv(modelViewProjectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));
}
void hge::shader::SunShader::setLODNumber(const GLuint& lodNumber)
{
	std::cerr << "Error this shader does not have LOD system." << std::endl;
	HGEPRINTCODELINE
	std::terminate();
}
void hge::shader::SunShader::setSunDirection(const glm::vec3 &sunDirection)
{
	glUniform3fv(sunLightDirectionUniformLocation, 1, glm::value_ptr(sunDirection));
}
void hge::shader::SunShader::use()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
}
GLuint hge::shader::SunShader::getModelViewProjectionMatrixUniformLocation()
{
	return modelViewProjectionMatrixUniformLocation;
}
GLuint hge::shader::SunShader::getModelMatrixUniformLoaction()
{
	return modelMatrixUniformLocation;
}
GLuint hge::shader::SunShader::getVertexShaderProgram()
{
	return vertexShaderProgram;
}
GLuint hge::shader::SunShader::getGeometryShaderProgram()
{
	std::cerr << "Error this shader program does not have geometry shader." << std::endl;
	HGEPRINTCODELINE
	std::terminate();
}
GLuint hge::shader::SunShader::getFragmentShaderProgram()
{
	return fragmentShaderProgram;
}
GLuint hge::shader::SunShader::getShaderProgram()
{
	return shaderProgram;
}
GLuint hge::shader::SunShader::getTextureSamplerLocation()
{
	return textureSamplerLocation;
}
