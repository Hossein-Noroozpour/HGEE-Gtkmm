#include "hge-shader-engine.hpp"
#include <iostream>
#include <cstdlib>
GLuint
hge::render::ShaderEngine::createProgram()
{
	GLuint shaderProgram = glCreateProgram();
	if (shaderProgram == 0)
	{
		std::cerr << "Error creating shader program." << std::endl;
		std::cerr << "In Line: " << __LINE__ << "."   << std::endl;
		std::cerr << "In File: " << __FILE__ << "."   << std::endl;
		exit(EXIT_FAILURE);
	}
	return shaderProgram;
}
GLuint
hge::render::ShaderEngine::addShaderToProgram(
	const std::string &shd,
	const GLenum &shaderType,
	const GLuint &shaderProgram)
{
	GLuint shaderObj = glCreateShader(shaderType);
	if (shaderObj == 0)
	{
		std::cerr << "Error creating shader type.";
		std::cerr << shaderType << std::endl;
		std::cerr << "In Line: " << __LINE__ << "." << std::endl;
		std::cerr << "In File: " << __FILE__ << "." << std::endl;
		exit(EXIT_FAILURE);
	}
	const char *chtemp = &(shd[0]);
	const GLint uintemp = shd.length();
	glShaderSource(shaderObj, 1, &(chtemp), &(uintemp));
	glCompileShader(shaderObj);
	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024] = {0};
		glGetShaderInfoLog(shaderObj, 1024, NULL, infoLog);
		std::cerr << "Error compiling shader type." << std::endl;
		std::cerr <<  shaderType << " " << infoLog  << std::endl;
		std::cerr << "In Line: " << __LINE__ << "." << std::endl;
		std::cerr << "In File: " << __FILE__ << "." << std::endl;
		exit(EXIT_FAILURE);
	}
	glAttachShader(shaderProgram, shaderObj);
	return shaderObj;
}
void
hge::render::ShaderEngine::run(
	const GLuint &shaderProgram)
{
	GLint isSuccess = (GLint)0;
	GLchar errorLog[1024] = {0};
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isSuccess);
	if (isSuccess == 0) {
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		std::cerr << "Error linking shader program: " << errorLog << std::endl;
		std::cerr << "In Line: " << __LINE__ << "."   << std::endl;
		std::cerr << "In File: " << __FILE__ << "."   << std::endl;
		exit(EXIT_FAILURE);
	}
	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &isSuccess);
	if (!isSuccess) {
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		std::cerr << "Invalid shader program: " << errorLog << std::endl;
		std::cerr << "In Line: " << __LINE__ << "."   << std::endl;
		std::cerr << "In File: " << __FILE__ << "."   << std::endl;
		exit(EXIT_FAILURE);
	}
	glUseProgram(shaderProgram);
}
GLuint
hge::render::ShaderEngine::getUniformLocation(
	const std::string &uname,
	const GLuint &shaderProgram)
{
	return glGetUniformLocation(shaderProgram, &(uname[0]));
}
void hge::render::ShaderEngine::endProgram(
	const GLuint &shaderProgram)
{
	glDeleteProgram(shaderProgram);
}
void hge::render::ShaderEngine::endObject(
	const GLuint &shaderObject)
{
	glDeleteShader(shaderObject);
}
std::shared_ptr<hge::render::ShaderEngine::hgeUniformBlock>
hge::render::ShaderEngine::initUniformBlock(const std::string &uniformBlockName, const GLuint &shaderProgram)
{
	auto result = std::shared_ptr<hgeUniformBlock>(new hgeUniformBlock);
//	result->index = glGetUniformBlockIndex(shaderProgram, uniformBlockName.c_str());
//	glGenBuffers(1, &(result->buffer));
//	glBindBuffer(GL_UNIFORM_BUFFER, result->buffer);
//	glGetActiveUniformBlockiv(shaderProgram, GL_UNIFORM_BLOCK_DATA_SIZE, uniformBlockName.c_str(), &(result->size));
//	glBindBufferBase(GL_UNIFORM_BUFFER, result->index, result->buffer);

	return result;
}
void hge::render::ShaderEngine::setUniformBlockData(
		const GLuint &offset,
		const GLuint &sizeOfData,
		const void * const &data,
		const hgeUniformBlockPtr &uniformBlock)
{
	glBindBuffer(GL_UNIFORM_BUFFER, uniformBlock->buffer);
	glBufferSubData(GL_UNIFORM_BUFFER, offset , sizeOfData, data);
}
