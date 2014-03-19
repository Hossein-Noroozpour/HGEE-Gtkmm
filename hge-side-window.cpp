#include "hge-side-window.hpp"

hge::ui::SideWindow::SideWindow()
{
	m_debug_window = new Gtk::ScrolledWindow();
	m_debug_window->set_hexpand(true);
	m_debug_window->set_vexpand(true);

	m_frame_rate_text = new Gtk::Label();
	m_frame_rate_text->set_text("FRPS");
	m_frame_rate_text->set_hexpand(true);
	m_frame_rate_text->set_vexpand(true);
	m_frame_rate_text->set_halign(Gtk::ALIGN_START);
	m_frame_rate_text->set_valign(Gtk::ALIGN_START);

	m_frame_rate_label = new Gtk::Label();
	m_frame_rate_label->set_hexpand(true);
	m_frame_rate_label->set_vexpand(true);
	m_frame_rate_label->set_halign(Gtk::ALIGN_START);
	m_frame_rate_label->set_valign(Gtk::ALIGN_START);
//	Glib::signal_timeout().connect(sigc::mem_fun(*this,
//			&hge::ui::MainWindow::update_frame_rate_per_second_label), 2000, 10);

	m_debug_grid = new Gtk::Grid();
	m_debug_grid->attach(*m_frame_rate_text, 0, 0, 1, 1);
	m_debug_grid->attach(*m_frame_rate_label, 1, 0, 1, 1);
	m_debug_grid->set_hexpand(true);
	m_debug_grid->set_vexpand(true);
	m_debug_window->add(*m_debug_grid);
	this->append_page(*m_debug_window, "_Debugging",
		true);

	m_refMeshTab = std::shared_ptr<MeshTab>(new MeshTab());
	this->append_page(*(m_refMeshTab->getScrolledWindow()), "Meshes", true);
}
