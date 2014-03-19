#include "hge-geometry-unit.hpp"
#include <iostream>
#define HGEPRINTCODELINE std::cout << "Debugging: file:" << __FILE__ << " line:" << __LINE__ << std::endl << std::flush;
hge::render::GeometryUnit::GeometryUnit
(const std::string& id, const std::string& name):
id(id), name(name), mvp(glm::mat4(1.0f))
{
	glGenQueries(HGEGEOMETRYNUMBEROFQUERIES, queries);
}
hge::render::GeometryUnit::~GeometryUnit()
{
	glDeleteQueries(HGEGEOMETRYNUMBEROFQUERIES, queries);
}
void
hge::render::GeometryUnit::setMesh(const std::shared_ptr<hge::render::MeshUnit>& m)
{
	mesh = m;
}
void
hge::render::GeometryUnit::draw()
{
	glBeginConditionalRender(queries[HGEGEOMETRYOCCLUSIONQUERYID], GL_QUERY_WAIT);
	mesh->bindTotal();
	shader->use();
	texture->bind(GL_TEXTURE0);
	shader->setModelMatrix(modelMatrix.modelM);
	shader->setModelViewProjectionMatrix(mvp);
	mesh->draw();
#ifdef HGEGEOMETRYDEBUGMVPVALUECHECK
	{
		auto hexstr = (char *)glm::value_ptr(mvp);
		HGEPRINTCODELINE
		std::cout << "Value of mvp is: ";
		for(int i = 0; i < sizeof(hexstr); i++)
		{
			int tmpint = hexstr[i] / 16;
			if(tmpint < 9)
			{
				std::cout << tmpint;
			}
			else if(tmpint == 10)
			{
				std::cout << "A";
			}
			else if(tmpint == 11)
			{
				std::cout << "B";
			}
			else if(tmpint == 12)
			{
				std::cout << "C";
			}
			else if(tmpint == 13)
			{
				std::cout << "D";
			}
			else if(tmpint == 14)
			{
				std::cout << "E";
			}
			else if(tmpint == 15)
			{
				std::cout << "F";
			}
			tmpint = hexstr[i] % 16;
			if(tmpint < 9)
			{
				std::cout << tmpint;
			}
			else if(tmpint == 10)
			{
				std::cout << "A";
			}
			else if(tmpint == 11)
			{
				std::cout << "B";
			}
			else if(tmpint == 12)
			{
				std::cout << "C";
			}
			else if(tmpint == 13)
			{
				std::cout << "D";
			}
			else if(tmpint == 14)
			{
				std::cout << "E";
			}
			else if(tmpint == 15)
			{
				std::cout << "F";
			}
		}
		std::cout << std::endl << std::endl;
	}
#endif
	glEndConditionalRender();
}
void
hge::render::GeometryUnit::occlusionQuery(const glm::mat4 &vp)
{
	mvp = vp * modelMatrix.modelM;
	glBeginQuery(GL_ANY_SAMPLES_PASSED, queries[HGEGEOMETRYOCCLUSIONQUERYID]);
	occlusionQueryShader->setModelViewProjectionMatrix(mvp);
	occlusionQueryMesh->bindTotal();
	occlusionQueryMesh->draw();
#ifdef HGEGEOMETRYDEBUGMVPVALUECHECK
	{
		auto hexstr = (char *)glm::value_ptr(mvp);
		HGEPRINTCODELINE
		std::cout << "Value of mvp is: ";
		for(int i = 0; i < sizeof(hexstr); i++)
		{
			int tmpint = hexstr[i] / 16;
			if(tmpint < 9)
			{
				std::cout << tmpint;
			}
			else if(tmpint == 10)
			{
				std::cout << "A";
			}
			else if(tmpint == 11)
			{
				std::cout << "B";
			}
			else if(tmpint == 12)
			{
				std::cout << "C";
			}
			else if(tmpint == 13)
			{
				std::cout << "D";
			}
			else if(tmpint == 14)
			{
				std::cout << "E";
			}
			else if(tmpint == 15)
			{
				std::cout << "F";
			}
			tmpint = hexstr[i] % 16;
			if(tmpint < 9)
			{
				std::cout << tmpint;
			}
			else if(tmpint == 10)
			{
				std::cout << "A";
			}
			else if(tmpint == 11)
			{
				std::cout << "B";
			}
			else if(tmpint == 12)
			{
				std::cout << "C";
			}
			else if(tmpint == 13)
			{
				std::cout << "D";
			}
			else if(tmpint == 14)
			{
				std::cout << "E";
			}
			else if(tmpint == 15)
			{
				std::cout << "F";
			}
		}
		std::cout << std::endl << std::endl;
	}
#endif
	glEndQuery(GL_ANY_SAMPLES_PASSED);
}
bool hge::render::GeometryUnit::isThisYourID(const std::string& idstr)
{
	return id == idstr;
}
void hge::render::GeometryUnit::setShader(const std::shared_ptr<shader::ShaderUnit>& sh)
{
	shader = sh;
}
void hge::render::GeometryUnit::setOcclusionQueryShader(const std::shared_ptr<shader::ShaderUnit>& sh)
{
	occlusionQueryShader = sh;
}
void hge::render::GeometryUnit::setTexture(const std::shared_ptr<texture::TextureUnit>& texture)
{
	this->texture = texture;
}
hge::math::ModelMatrix*
hge::render::GeometryUnit::getModelMatrix()
{
	return &modelMatrix;
}
std::shared_ptr<hge::render::MeshUnit> hge::render::GeometryUnit::getMesh()
{
	return mesh;
}
void
hge::render::GeometryUnit::setOcclusionQueryMesh(const std::shared_ptr<MeshUnit> &m)
{
	occlusionQueryMesh = m;
}
