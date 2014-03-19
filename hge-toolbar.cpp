#include "hge-toolbar.hpp"
hge::ui::ToolBar::ToolBar(const std::shared_ptr<core::Application> &application):
	application(application)
{
	this->set_min_content_height(60);

	m_tool_bar_file_new  = new Gtk::Button();
	m_tool_bar_file_new_image = new Gtk::Image("new.png");
	m_tool_bar_file_new->set_image(*m_tool_bar_file_new_image);

	m_tool_bar_file_add  = new Gtk::Button();
	m_tool_bar_file_add_image = new Gtk::Image("add.png");
	m_tool_bar_file_add->set_image(*m_tool_bar_file_add_image);
	m_tool_bar_file_add->signal_clicked().connect(sigc::mem_fun(*this,
		&hge::ui::ToolBar::onFileAddClicked));

	m_tool_bar_file_open = new Gtk::Button();
	m_tool_bar_file_open_image = new Gtk::Image("open.png");
	m_tool_bar_file_open->set_image(*m_tool_bar_file_open_image);

	m_tool_bar_file_quit = new Gtk::Button();
	m_tool_bar_file_quit_image = new Gtk::Image("quit.png");
	m_tool_bar_file_quit->set_image(*m_tool_bar_file_quit_image);

	m_tool_bar_terrain = new Gtk::Button();
	m_tool_bar_terrain_image = new Gtk::Image("terrain.png");
	m_tool_bar_terrain->set_image(*m_tool_bar_terrain_image);
	m_tool_bar_terrain->signal_clicked().connect(sigc::mem_fun(*this,
		&hge::ui::ToolBar::onTerrainClicked));

	m_tool_bar_grid   = new Gtk::Grid();
	this->add(*m_tool_bar_grid);
	m_tool_bar_grid->set_column_spacing(2);
	m_tool_bar_grid->set_vexpand(false);
	m_tool_bar_grid->set_hexpand(true);
	m_tool_bar_grid->attach(*m_tool_bar_file_new,  0, 0, 1, 1);
	m_tool_bar_grid->attach(*m_tool_bar_file_add,  1, 0, 1, 1);
	m_tool_bar_grid->attach(*m_tool_bar_file_open, 2, 0, 1, 1);
	m_tool_bar_grid->attach(*m_tool_bar_file_quit, 3, 0, 1, 1);
	m_tool_bar_grid->attach(*m_tool_bar_terrain  , 4, 0, 1, 1);
}
void hge::ui::ToolBar::onFileAddClicked(){}
void hge::ui::ToolBar::onTerrainClicked()
{
	trnW = std::shared_ptr<TerrainWindow>(new TerrainWindow(application));
}
