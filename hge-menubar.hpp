#ifndef HGEMENUBAR_HPP
#define HGEMENUBAR_HPP
#include "hge-main-window.hpp"
namespace hge
{
	namespace ui
	{
		class MenuBar : public Gtk::MenuBar
		{
		private:
			Gtk::MenuBar  *m_menu_bar;
			Gtk::Menu     *m_menu_file;
			Gtk::MenuItem *m_menu_item_file;
			Gtk::MenuItem *m_menu_item_file_new;
			Gtk::MenuItem *m_menu_item_file_open;
			Gtk::MenuItem *m_menu_item_file_quit;
			Gtk::MenuItem *m_menu_item_file_add;
			Gtk::MenuItem *m_menu_item_edit;
			Gtk::Menu     *m_menu_edit;
			Gtk::MenuItem *m_menu_item_help;
			Gtk::Menu     *m_menu_help;
			void on_menu_file_new();
			void on_menu_file_add();
		public:
			MenuBar();
			Gtk::MenuBar *getMenuBar();
		};
	}
}
#endif
