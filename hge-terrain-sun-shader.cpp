#include "hge-terrain-sun-shader.hpp"
#include "hge-shader-engine.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#define HGEPRINTCODELINE std::cout << "Debugging: file:" << __FILE__ << " line:" << __LINE__ << std::endl << std::flush;
hge::shader::TerrainSunShader::TerrainSunShader():
	shaderProgram(render::ShaderEngine::createProgram())
{
	std::string pVS = readShaderFile("../HGE-Editor/hge-terrain-shader-string.vertexShader");
	std::string pGS = readShaderFile("../HGE-Editor/hge-terrain-shader-string.geometryShader");
	std::string pFS = readShaderFile("../HGE-Editor/hge-terrain-shader-string.fragmentShader");
	vertexShaderProgram = render::ShaderEngine::addShaderToProgram(pVS, GL_VERTEX_SHADER, shaderProgram);
#ifdef HGETERRAINSUNSHADERDEBUGMODE
	std::cout << "Vertext shader compiled." << std::endl;
	HGEPRINTCODELINE
#endif
	geometryShaderProgram = render::ShaderEngine::addShaderToProgram(pGS, GL_GEOMETRY_SHADER, shaderProgram);
#ifdef HGETERRAINSUNSHADERDEBUGMODE
	std::cout << "Geometry shader compiled." << std::endl;
	HGEPRINTCODELINE
#endif
	fragmentShaderProgram = render::ShaderEngine::addShaderToProgram(pFS, GL_FRAGMENT_SHADER, shaderProgram);
#ifdef HGETERRAINSUNSHADERDEBUGMODE
	std::cout << "Fragment shader compiled." << std::endl;
	HGEPRINTCODELINE
#endif
	hge::render::ShaderEngine::run(shaderProgram);
	mvpmul = render::ShaderEngine::getUniformLocation(std::string("mvpm"), shaderProgram);
#ifdef HGETERRAINSUNSHADERDEBUGMODE
	assert(mvpmul != 0xFFFFFFFF);
#endif
	glUniformMatrix4fv(mvpmul, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	cprtmul = render::ShaderEngine::getUniformLocation(std::string("cprtm"), shaderProgram);
#ifdef HGETERRAINSUNSHADERDEBUGMODE
	assert(cprtmul != 0xFFFFFFFF);
#endif
	glUniform3fv(cprtmul, 1, glm::value_ptr(glm::vec3(1.0f)));
	lodnul = render::ShaderEngine::getUniformLocation(std::string("lodn"), shaderProgram);
#ifdef HGETERRAINSUNSHADERDEBUGMODE
	assert(lodnul != 0xFFFFFFFF);
#endif
	glUniform1i(lodnul, 0);
	for(GLuint i = 0; i < HGETERRAINSUNSHADERNUMBEROFTEXTURES; i++)
	{
		tsl[i] = render::ShaderEngine::getUniformLocation(
				std::string("ts[") + std::to_string(i) + "]", shaderProgram);
#ifdef HGETERRAINSUNSHADERDEBUGMODE
		assert(tsl[i] != 0xFFFFFFFF);
#endif
		glUniform1i(tsl[i], i);
	}
}
hge::shader::TerrainSunShader::~TerrainSunShader()
{
	hge::render::ShaderEngine::endObject(vertexShaderProgram);
	hge::render::ShaderEngine::endObject(geometryShaderProgram);
	hge::render::ShaderEngine::endObject(fragmentShaderProgram);
	hge::render::ShaderEngine::endProgram(shaderProgram);
}
void hge::shader::TerrainSunShader::setModelMatrix(const glm::mat4 &modelMatrix)
{
	glUniformMatrix4fv(mmul, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}
void hge::shader::TerrainSunShader::setModelViewProjectionMatrix(const glm::mat4 &modelViewProjectionMatrix)
{
	glUniformMatrix4fv(mvpmul, 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));
}
void hge::shader::TerrainSunShader::setCameraPositionRelativeToModel(const glm::vec3& p)
{
	glUniform3fv(cprtmul, 1, glm::value_ptr(p));
}
void hge::shader::TerrainSunShader::setLODNumber(const GLuint& lodNumber)
{
	glUniform1i(lodnul, lodNumber);
}
void hge::shader::TerrainSunShader::use()
{
	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
}
GLuint hge::shader::TerrainSunShader::getModelViewProjectionMatrixUniformLocation()
{
	return mvpmul;
}
GLuint hge::shader::TerrainSunShader::getModelMatrixUniformLoaction()
{
	return mmul;
}
GLuint hge::shader::TerrainSunShader::getVertexShaderProgram()
{
	return vertexShaderProgram;
}
GLuint hge::shader::TerrainSunShader::getGeometryShaderProgram()
{
	return geometryShaderProgram;
}
GLuint hge::shader::TerrainSunShader::getFragmentShaderProgram()
{
	return fragmentShaderProgram;
}
GLuint hge::shader::TerrainSunShader::getShaderProgram()
{
	return shaderProgram;
}
GLuint* hge::shader::TerrainSunShader::getTextureSamplerLocations()
{
	return tsl;
}
std::string hge::shader::TerrainSunShader::readShaderFile(const std::string &fileName)
{
	std::string result;
	std::ifstream in(fileName, std::ios::in);
	if(in)
	{
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
		return result;
	}
	std::terminate();
}
