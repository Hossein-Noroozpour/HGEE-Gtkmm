#ifndef HGETOOLBAR_HPP
#define HGETOOLBAR_HPP
#include "hge-main-window.hpp"
#include "hge-terrain-window.hpp"
#include "hge-application.hpp"
namespace hge
{
	namespace ui
	{
		class ToolBar : public Gtk::ScrolledWindow
		{
		private:
			std::shared_ptr<core::Application> application;
			Gtk::Grid   *m_tool_bar_grid;
			Gtk::Button *m_tool_bar_file_new;
			Gtk::Button *m_tool_bar_file_open;
			Gtk::Button *m_tool_bar_file_quit;
			Gtk::Button *m_tool_bar_file_add;
			Gtk::Button *m_tool_bar_terrain;
			Gtk::Image  *m_tool_bar_file_new_image;
			Gtk::Image  *m_tool_bar_file_open_image;
			Gtk::Image  *m_tool_bar_file_add_image;
			Gtk::Image  *m_tool_bar_file_quit_image;
			Gtk::Image  *m_tool_bar_terrain_image;
			std::shared_ptr<TerrainWindow> trnW;
			void onFileAddClicked();
			void onTerrainClicked();
		public:
			ToolBar(const std::shared_ptr<core::Application>& application);
		};
	}
}
#endif
