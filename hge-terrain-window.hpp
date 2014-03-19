#ifndef HGETERRAINWINDOW_HPP
#define HGETERRAINWINDOW_HPP
//#define HGETERRAINWINDOWDEBUG
#include "hge-opengl-render-widget.hpp"
#include "hge-math.hpp"
#include "hge-application.hpp"
namespace hge
{
	namespace ui
	{
		class TerrainWindow : public Gtk::Window
		{
		private:
			std::shared_ptr<core::Application>      application;
			std::shared_ptr<Gtk::Grid>              grid;
			std::shared_ptr<Gtk::Label>             imagePreviewSectionLabel;
			std::shared_ptr<Gtk::Label>             imageAddressLabel;
			std::shared_ptr<Gtk::FileChooserButton> imagePreviewChooser;
			std::shared_ptr<Gtk::Image>             imagePreview;
			std::shared_ptr<Gtk::ScrolledWindow>    imageViewport;
			std::shared_ptr<Gtk::Button>            loadTerrain;
			Glib::Mutex                             loadTerrainButtonMutex;
			unsigned int                            height;
			unsigned int                            width;
			unsigned int                            componentBytes;
			unsigned int                            rowStrid;
			u_int8_t                               *pixels;
			GLfloat                              ***buffer;

			void onImageFileChanged();
			void onLoadClicked     ();
			void calculateNormals  (unsigned int threadIndex);
		public:
			TerrainWindow(const std::shared_ptr<core::Application>& application);
		};
	}
}
#endif
