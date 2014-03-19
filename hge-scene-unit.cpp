#include "hge-scene-unit.hpp"
#include "hge-collada-importer.hpp"
#include "hge-white-shader.hpp"
hge::render::SceneUnit::SceneUnit():
	occlusionQueryShader(new shader::WhiteShader()),
	currentCameraIndex(0),
	currentPerspectiveIndex(0),
	hasTerrain(false),
	hasGeometry(false)
{
	cameras.push_back(std::shared_ptr<math::CameraMatrix>(new math::CameraMatrix()));
	perspectives.push_back(std::shared_ptr<math::PerspectiveMatrix>(new math::PerspectiveMatrix()));
}
void hge::render::SceneUnit::addGeometry(const std::shared_ptr<GeometryUnit>& geometry)
{
	hasGeometry = true;
	geometry->setOcclusionQueryShader(occlusionQueryShader);
	geometries.push_back(geometry);
}
void
hge::render::SceneUnit::draw()
{
	auto vp = perspectives[0]->getMatrix() * cameras[0]->getMatrix();
	if(hasTerrain)
	{
		terrain->draw(vp);
	}
	if(hasGeometry)
	{
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);
		occlusionQueryShader->use();
		geometries[0]->occlusionQuery(vp);
		occlusionQueryShader->use();
		for(auto geoiter = geometries.begin(); geoiter < geometries.end(); geoiter++)
		{
			(*geoiter)->occlusionQuery(vp);
		}
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
		for(auto geoiter = geometries.begin(); geoiter < geometries.end(); geoiter++)
		{
			(*geoiter)->draw();
		}
	}
}
std::shared_ptr<hge::render::GeometryUnit> hge::render::SceneUnit::getGeoByID(const std::string& id)
{
	for(unsigned int i = 0; i < geometries.size(); i++)
	{
		if(geometries[i]->isThisYourID(id))
		{
			return geometries[i];
		}
	}
	HGEPRINTCODELINE
	std::cout << "Geo Not found!" << std::endl;
	return nullptr;
}
void hge::render::SceneUnit::setTerrain(const std::shared_ptr<TerrainUnit>& t)
{
	hasTerrain = true;
	terrain = t;
}
std::shared_ptr<hge::math::CameraMatrix>
hge::render::SceneUnit::getCamera(const unsigned int& cameraIndex)
{
	return cameras[cameraIndex];
}
