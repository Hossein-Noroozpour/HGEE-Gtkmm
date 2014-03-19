#ifndef HGEMAIN_HPP
#define	HGEMAIN_HPP
#include "hge-application.hpp"
#include <memory>
#include "hge-camera-matrix.hpp"
#include "hge-perspective-matrix.hpp"
#include "hge-scene-unit.hpp"
#include "hge-sun-shader.hpp"
#include "hge-texture-unit.hpp"
class MyGame : public hge::core::Application
{
public:
	MyGame();
	virtual ~MyGame();
	void start();
	void initialize();
	void update();
	void buttonPressed(const HGEButton& key);
	void buttonReleased(const HGEButton& key);
	void mouseMoved(const float& dx, const float& dy);
	bool addFromColladaFile(const std::string &filename);
	bool addFromHGEFile(const std::string &filename);
	bool addTerrain(const std::shared_ptr<hge::render::TerrainUnit> &terrain);
private:
	std::shared_ptr<hge::render::SceneUnit> scene;
	bool goForward;
	bool goDownward;
	bool goRightward;
	bool goLeftward;
	bool middleMouseDown;
	float m_cameraRotationSpeed;
	float m_cameraMoveSpeed;
};
#endif
