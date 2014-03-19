#ifndef HGESCENEUNIT_HPP
#define HGESCENEUNIT_HPP
#include "hge-geometry-unit.hpp"
#include "hge-terrain-unit.hpp"
#include "hge-camera-matrix.hpp"
#include "hge-perspective-matrix.hpp"
#include <memory>
#include <vector>
namespace hge
{
	namespace render
	{
		class SceneUnit
		{
		private:
			std::vector<std::shared_ptr<GeometryUnit>> geometries;
			std::vector<std::shared_ptr<math::CameraMatrix>> cameras;
			std::vector<std::shared_ptr<math::PerspectiveMatrix>> perspectives;
			std::shared_ptr<shader::ShaderUnit> occlusionQueryShader;
			std::shared_ptr<TerrainUnit> terrain;
			unsigned int currentCameraIndex;
			unsigned int currentPerspectiveIndex;
			bool hasTerrain;
			bool hasGeometry;
		public:
			SceneUnit();
			void addGeometry(const std::shared_ptr<GeometryUnit> &geometry);
			void setTerrain(const std::shared_ptr<TerrainUnit> &terrain);
			void draw();
			std::shared_ptr<GeometryUnit> getGeoByID(const std::string& id);
			std::shared_ptr<math::CameraMatrix> getCamera(const unsigned int& cameraIndex = 0);
		};
	}
}
#endif
