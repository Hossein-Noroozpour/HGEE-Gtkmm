#include "hge-white-shader.hpp"
#include <iostream>
#include <cassert>
#define HGEPRINTCODELINE std::cout << "Debugging: file:" << __FILE__ << " line:" << __LINE__ << std::endl << std::flush;
hge::shader::WhiteShader::WhiteShader():
	shaderProgram(render::ShaderEngine::createProgram())
{
	std::string pVS(
		"#version 430\n"
		"layout (location = 0) in vec3 vertex;"
		"uniform mat4 mvp;"
		"void main()"
		"{"
			"gl_Position = mvp * vec4(vertex, 1.0);"
		"}");
	///////////////////////////////////////////////////////////////////////
	std::string pFS(
		"#version 430\n\n"
		"out vec4 fragColor;\n"
		"void main()\n"
		"{\n"
			"fragColor =  vec4(1.0);\n"
		"};\n");
	///////////////////////////////////////////////////////////////////////
	vertexShaderProgram = render::ShaderEngine::addShaderToProgram(pVS, GL_VERTEX_SHADER, shaderProgram);
	fragmentShaderProgram = render::ShaderEngine::addShaderToProgram(pFS, GL_FRAGMENT_SHADER, shaderProgram);
	hge::render::ShaderEngine::run(shaderProgram);
	modelViewProjectionMatrixUniformLocation = render::ShaderEngine::getUniformLocation(std::string("mvp"), shaderProgram);
	assert(modelViewProjectionMatrixUniformLocation != 0xFFFFFFFF);
}
hge::shader::WhiteShader::~WhiteShader()
{
	hge::render::ShaderEngine::endObject(vertexShaderProgram);
	hge::render::ShaderEngine::endObject(fragmentShaderProgram);
	hge::render::ShaderEngine::endProgram(shaderProgram);
}
void hge::shader::WhiteShader::setModelMatrix(const glm::mat4 &modelMatrix)
{
	std::cerr << "Error this shader does not have model matrix." << std::endl;
	HGEPRINTCODELINE
	std::terminate();
}
void hge::shader::WhiteShader::setModelViewProjectionMatrix(const glm::mat4 &modelViewProjectionMatrix)
{
	glUniformMatrix4fv(modelViewProjectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));
}
void hge::shader::WhiteShader::setLODNumber(const GLuint& lodNumber)
{
	std::cerr << "Error this shader does not have LOD system." << std::endl;
	HGEPRINTCODELINE
	std::terminate();
}
void hge::shader::WhiteShader::use()
{
	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
}
GLuint hge::shader::WhiteShader::getModelViewProjectionMatrixUniformLocation()
{
	return modelViewProjectionMatrixUniformLocation;
}
GLuint hge::shader::WhiteShader::getModelMatrixUniformLoaction()
{
	std::cerr << "Error this shader does not have model matrix." << std::endl;
	HGEPRINTCODELINE
	std::terminate();
}
GLuint hge::shader::WhiteShader::getVertexShaderProgram()
{
	return vertexShaderProgram;
}
GLuint hge::shader::WhiteShader::getGeometryShaderProgram()
{
	std::cerr << "Error this shader program does not have geometry shader." << std::endl;
	HGEPRINTCODELINE
	std::terminate();
}
GLuint hge::shader::WhiteShader::getFragmentShaderProgram()
{
	return fragmentShaderProgram;
}
GLuint hge::shader::WhiteShader::getShaderProgram()
{
	return shaderProgram;
}
