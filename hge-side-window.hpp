#ifndef HGESIDEWINDOW_HPP
#define HGESIDEWINDOW_HPP
#include "hge-main-window.hpp"
#include "hge-mesh-tab.hpp"
namespace hge
{
	namespace ui
	{
		class SideWindow : public Gtk::Notebook
		{
		private:
			Gtk::ScrolledWindow *m_debug_window;
			Gtk::Grid *m_debug_grid;
			Gtk::Label *m_frame_rate_text;
			Gtk::Label *m_frame_rate_label;
			std::shared_ptr<MeshTab> m_refMeshTab;
		public:
			SideWindow();
		};
	}
}
#endif
