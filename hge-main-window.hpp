#ifndef HGE_MAIN_WINDOW_HPP
#define	HGE_MAIN_WINDOW_HPP
#include "hge-opengl-render-widget.hpp"
#include "hge-application.hpp"
#include "hge-mesh-tab.hpp"
#include <memory>
namespace hge
{
	namespace ui
	{
		class MainWindow : public Gtk::Window
		{
		public:
			MainWindow(const std::shared_ptr<hge::core::Application>& hgeapp);
			~MainWindow();
		private:
			//Signal handlers:
			void add_file();
			void on_menu_file_open();
			void on_menu_file_quit();
			void on_menu_others();
			void on_menu_choices_one();
			void on_menu_choices_two();
			bool on_key_press_event(GdkEventKey *event);
			bool on_key_release_event(GdkEventKey *event);
			//bool update_frame_rate_per_second_label();
			Gtk::Grid     *m_grid;
			//Paned Window
			Gtk::Paned *m_pane_main;
			//viewport notebook
			Gtk::Grid *m_viewport;
			//RenderWidget m_render_widget;
			OpenGLRenderWidget *m_openGLRenderDevice;
			//taskbar image
			Glib::RefPtr<Gdk::Pixbuf> m_task_bar_image;
			//tray icon
			Glib::RefPtr<Gtk::StatusIcon> m_tray_icon;
			volatile double m_frame_rate_per_second;
			std::shared_ptr<core::Application> hgeapp;
		};
	}
}
#endif
