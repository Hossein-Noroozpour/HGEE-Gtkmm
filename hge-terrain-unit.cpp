#include "hge-terrain-unit.hpp"
#include <iostream>
hge::render::TerrainUnit::TerrainUnit()
{}
hge::render::TerrainUnit::~TerrainUnit()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vboBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	for(unsigned int i = 0; i < iboBuffers.size(); i++)
	{
		glDeleteBuffers(1, &(iboBuffers[i]));
	}
}
void hge::render::TerrainUnit::draw(const glm::mat4 &vp)
{
	glBindBuffer(GL_ARRAY_BUFFER, vboBuffer);
	shader->use();
	for(unsigned int i = 0; i < textures.size(); i++)
	{
		textures[i]->bind(GL_TEXTURE0 + i);
	}
	shader->setModelViewProjectionMatrix(vp * modelMatrix.modelM);
//	for(unsigned int i = 0; i < iboBuffers.size(); i++)
//	{
		shader->setLODNumber(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBuffers[0]);
		glDrawElements(GL_TRIANGLES, iboElements[0], GL_UNSIGNED_INT, 0);
//	}
}
void hge::render::TerrainUnit::setVBO(const GLfloat * const &vertices, const GLuint &verticesBytes)
{
	glGenBuffers(1, &vboBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vboBuffer);
	glBufferData(GL_ARRAY_BUFFER, verticesBytes, vertices, GL_STATIC_DRAW);
}
void hge::render::TerrainUnit::addIBO(const GLuint * const &indices, const GLuint &indicesBytes)
{
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesBytes, indices, GL_STATIC_DRAW);
	iboElements.push_back(indicesBytes / sizeof(GLuint));
	iboBuffers.push_back(ibo);
	std::cout << iboElements[0] << std::endl;
}
void hge::render::TerrainUnit::setShader(const std::shared_ptr<shader::ShaderUnit>& s)
{
	shader = s;
}
void hge::render::TerrainUnit::addTexture(const std::shared_ptr<texture::TextureUnit>& texture)
{
	textures.push_back(texture);
}
hge::math::ModelMatrix* hge::render::TerrainUnit::getModelMatrix()
{
	return &modelMatrix;
}
