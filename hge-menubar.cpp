#include "hge-menubar.hpp"

hge::ui::MenuBar::MenuBar()
{
	m_menu_item_file = new Gtk::MenuItem();
	m_menu_item_file->set_label("_File");
	m_menu_item_file->set_use_underline(true);

	m_menu_item_file_new = new Gtk::MenuItem();
	m_menu_item_file_new->set_label("_New");
	m_menu_item_file_new->set_use_underline(true);

	m_menu_item_file_open = new Gtk::MenuItem();
	m_menu_item_file_open->set_label("_Open");
	m_menu_item_file_open->set_use_underline(true);

	m_menu_item_file_quit = new Gtk::MenuItem();
	m_menu_item_file_quit->set_label("_Quit");
	m_menu_item_file_quit->set_use_underline(true);

	m_menu_item_file_add = new Gtk::MenuItem();
	m_menu_item_file_add->set_label("_Add");
	m_menu_item_file_add->set_use_underline(true);
	m_menu_item_file_add->signal_activate().connect(sigc::mem_fun(*this,
		&hge::ui::MenuBar::on_menu_file_add));

	m_menu_file = new Gtk::Menu();
	m_menu_item_file->set_submenu(*m_menu_file);
	m_menu_file->append(*m_menu_item_file_new);
	m_menu_file->append(*m_menu_item_file_open);
	m_menu_file->append(*m_menu_item_file_add);
	m_menu_file->append(*m_menu_item_file_quit);

	m_menu_item_edit = new Gtk::MenuItem();
	m_menu_item_edit->set_label("_Edit");
	m_menu_item_edit->set_use_underline(true);

	m_menu_edit = new Gtk::Menu();
	m_menu_item_edit->set_submenu(*m_menu_edit);

	m_menu_item_help = new Gtk::MenuItem();
	m_menu_item_help->set_label("_Help");
	m_menu_item_help->set_use_underline(true);

	m_menu_help = new Gtk::Menu();
	m_menu_item_help->set_submenu(*m_menu_help);

	this->append(*m_menu_item_file);
	this->append(*m_menu_item_edit);
	this->append(*m_menu_item_help);
}
void hge::ui::MenuBar::on_menu_file_new(){}
void hge::ui::MenuBar::on_menu_file_add(){}
