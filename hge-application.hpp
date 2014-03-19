#ifndef HGEAPPLICATION_H
#define	HGEAPPLICATION_H
#include <string>
#include <memory>
namespace hge
{
	namespace render
	{
		class TerrainUnit;
	}
	namespace core
	{
		class Application
		{
		public:
			enum HGEButton
			{
				/// Mouse Buttons
				rightMouseButton,
				middleMouseButton,
				leftMouseButton,
				/// Arrow Key Buttons
				upArrowKeyButton,
				downArrowKeyButton,
				leftArrowKeyButton,
				rightArrowKeyButton,
				/// Normal key Buttons
				wKeyButton,
				sKeyButton,
				aKeyButton,
				dKeyButton
			};
			/// \warning this function will be called in starting process of
			/// do not call any OpenGL function in it.
			virtual void start() = 0;
			/// \note this function will be called in OpenGL initializing
			/// procedure.
			virtual void initialize() = 0;
			/// this function will be called in every frame update
			virtual void update() = 0;
			/// \return true if every things went correct
			/// else false if any thing went wrong.
			virtual void buttonPressed(const HGEButton& key) = 0;
			virtual void buttonReleased(const HGEButton& key) = 0;
			virtual void mouseMoved(const float& dx, const float& dy) = 0;
			virtual bool addFromColladaFile(const std::string& filename) = 0;
			virtual bool addFromHGEFile(const std::string& filename) = 0;
			virtual bool addTerrain(const std::shared_ptr<render::TerrainUnit>& terrain) = 0;
		};
	}
}
#endif
