#include "hge-main.hpp"
#include <iostream>
#include "hge-main-window.hpp"
#include "hge-collada-importer.hpp"
#include "hge-terrain-sun-shader.hpp"
#define HGEPRINTCODELINE std::cout << "Debugging: file:" << __FILE__ << " line:" << __LINE__ << std::endl << std::flush;
MyGame::MyGame():
		goForward(false),
		goDownward(false),
		goRightward(false),
		goLeftward(false),
		middleMouseDown(false),
		m_cameraRotationSpeed(0.001f),
		m_cameraMoveSpeed(1.0f)
{
}
MyGame::~MyGame()
{
}
void MyGame::start()
{
}
void MyGame::initialize()
{
	scene = std::shared_ptr<hge::render::SceneUnit>(new hge::render::SceneUnit());
}
void MyGame::update()
{
	if(goForward)
		scene->getCamera()->moveForward(m_cameraMoveSpeed);
	if(goDownward)
		scene->getCamera()->moveForward(-m_cameraMoveSpeed);
	if(goRightward)
		scene->getCamera()->moveSideward(m_cameraMoveSpeed);
	if(goLeftward)
		scene->getCamera()->moveSideward(-m_cameraMoveSpeed);
	scene->draw();
}
void MyGame::buttonPressed(const HGEButton& key)
{
	switch(key)
	{
		case(wKeyButton):
			goForward = true;
			break;
		case(sKeyButton):
			goDownward = true;
			break;
		case(aKeyButton):
			goLeftward = true;
			break;
		case(dKeyButton):
			goRightward = true;
			break;
		case(middleMouseButton):
			middleMouseDown = true;
			break;
		default:
			break;
	}
}
void MyGame::buttonReleased(const HGEButton& key)
{
	switch(key)
	{
		case(wKeyButton):
			goForward = false;
			break;
		case(sKeyButton):
			goDownward = false;
			break;
		case(aKeyButton):
			goLeftward = false;
			break;
		case(dKeyButton):
			goRightward = false;
			break;
		case(middleMouseButton):
			middleMouseDown = false;
			break;
		default:
			break;
	}
}
void MyGame::mouseMoved(const float& dx, const float& dy)
{
	if(middleMouseDown)
	{
		scene->getCamera()->rotateLocalX(dy * m_cameraRotationSpeed);
		scene->getCamera()->rotateLocalY(dx * m_cameraRotationSpeed);
	}
}
bool MyGame::addFromColladaFile(const std::string &filename)
{
	return false;
}
bool MyGame::addFromHGEFile(const std::string &filename)
{
	return false;
}
bool MyGame::addTerrain(const std::shared_ptr<hge::render::TerrainUnit> &terrain)
{
	std::shared_ptr<hge::shader::TerrainSunShader> shader(new hge::shader::TerrainSunShader());
	terrain->setShader(shader);
	{
		std::string texL = "/home/thany/Programming/QtCreator/build-HGE-Editor-Desktop_Qt_5_2_0_GCC_64bit-Debug/Textures/";
		std::string texF [] =
		{
			"ice.jpg",
			"snow.jpg",
			"stone.jpg",
			"grass1.jpg",
			"grass2.jpg",
			"grass3.jpg",
			"sand.jpg",
			"sea.jpg"
		};
		for(auto i = 0; i < 8; i++)
		{
			auto tex = std::shared_ptr<hge::texture::TextureUnit>(
						new hge::texture::TextureUnit(GL_TEXTURE_2D, texL + texF[i]));
			tex->load();
			terrain->addTexture(tex);
		}
	}
	scene->setTerrain(terrain);
}
int main(int argc, char *argv[])
{
	Magick::InitializeMagick(*argv);
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
	std::shared_ptr<hge::core::Application> game(new MyGame());
	hge::ui::MainWindow *win = new hge::ui::MainWindow(game);
	return app->run(*win);
}
