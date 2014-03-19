#ifndef OPENGLRENDERWIDGET_HPP
#define	OPENGLRENDERWIDGET_HPP
#include <gtkmm.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>
#include <GL/glew.h>
#include <GL/glx.h>
#include <chrono>
#include "hge-application.hpp"
namespace hge
{
	namespace ui
	{
		class OpenGLRenderWidget
		{
		public:
			OpenGLRenderWidget(volatile double *frame_rate_per_second,
				std::shared_ptr<hge::core::Application> hgeapp);
			~OpenGLRenderWidget();
			Gtk::DrawingArea *get_widget();
			void set_frame_rate_per_second_pointer(
				volatile double *frame_rate_per_second);
		private:
			Gtk::DrawingArea *da;
			Display *xd;
			XVisualInfo *xvi;
			GLXContext glxc;
			volatile double *frps;
			std::chrono::high_resolution_clock::time_point t1, t2;
			std::shared_ptr<core::Application> hgeapp;
			bool is_not_drawn;
			/// Previous X and Y for motion notification
			double preX, preY;
			//SLOTS---------------------------------------------------------
			bool on_button_press_event(GdkEventButton *event);
			bool on_button_release_event(GdkEventButton *event);
			void on_child_notify(GParamSpec *pspec);
			void on_composited_changed();
			bool on_configure_event(GdkEventConfigure *e);
			bool on_damage_event(GdkEventExpose *event);
			bool on_delete_event(GdkEventAny *event);
			void on_direction_changed(Gtk::TextDirection direction);
			void on_drag_begin(const Glib::RefPtr<Gdk::DragContext> &context);
			void on_drag_data_delete(const Glib::RefPtr<Gdk::DragContext> &context);
			void on_drag_data_get(const Glib::RefPtr<Gdk::DragContext> &context,
				Gtk::SelectionData &selection_data, guint info, guint time);
			void on_drag_data_received(const Glib::RefPtr<Gdk::DragContext> &context, int x, int y,
				const Gtk::SelectionData &selection_data, guint info, guint time);
			bool on_drag_drop(const Glib::RefPtr<Gdk::DragContext> &context, int x, int y, guint time);
			void on_drag_end(const Glib::RefPtr<Gdk::DragContext> &context);
			bool on_drag_failed(const Glib::RefPtr<Gdk::DragContext> &context, Gtk::DragResult result);
			void on_drag_leave(const Glib::RefPtr<Gdk::DragContext> &context, guint time);
			bool on_drag_motion(const Glib::RefPtr<Gdk::DragContext> &context, int x, int y, guint time);
			bool on_draw(const Cairo::RefPtr<Cairo::Context> &c);
			bool on_enter_notify_event(GdkEventCrossing *event);
			bool on_event(GdkEvent *event);
			void on_event_after(GdkEvent *event);
			bool on_focus(Gtk::DirectionType direction);
			bool on_focus_in_event(GdkEventFocus *event);
			bool on_focus_out_event(GdkEventFocus *event);
			bool on_grab_broken_event(GdkEventGrabBroken *event);
			void on_grab_focus();
			void on_grab_notify(bool was_grabbed);
			void on_hide();
			void on_hierarchy_changed(Gtk::Widget *previous_toplevel);
			bool on_key_press_event(GdkEventKey* event);
			bool on_key_release_event(GdkEventKey *event);
			bool on_leave_notify_event(GdkEventCrossing *event);
			void on_map();
			bool on_map_event(GdkEventAny *event);
			bool on_mnemonic_activate(bool group_cycling);
			bool on_motion_notify_event(GdkEventMotion *event);
			void on_parent_changed(Gtk::Widget *previous_parent);
			bool on_popup_menu();
			bool on_property_notify_event(GdkEventProperty *event);
			bool on_proximity_in_event(GdkEventProximity *event);
			bool on_proximity_out_event(GdkEventProximity *event);
			bool on_query_tooltip(int x, int y, bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip> &tooltip);
			void on_realize();
			void on_screen_changed(const Glib::RefPtr<Gdk::Screen> &previous_screen);
			bool on_scroll_event(GdkEventScroll *event);
			bool on_selection_clear_event(GdkEventSelection *event);
			void on_selection_get(Gtk::SelectionData &selection_data, guint info, guint time);
			bool on_selection_notify_event(GdkEventSelection *event);
			void on_selection_received(const Gtk::SelectionData &selection_data, guint time);
			bool on_selection_request_event(GdkEventSelection *event);
			void on_show();
			void on_size_allocate(Gtk::Allocation& allocation);
			void on_state_changed(Gtk::StateType previous_state);
			void on_state_flags_changed(Gtk::StateFlags previous_state_flags);
			void on_style_updated();
			bool on_touch_event(GdkEventTouch *event);
			void on_unmap();
			bool on_unmap_event(GdkEventAny *event);
			void on_unrealize();
			bool on_visibility_notify_event(GdkEventVisibility *event);
			bool on_window_state_event(GdkEventWindowState *event);
			//END OF SLOTS--------------------------------------------------
			bool render_loop(void);
		};
	}
}
#endif	/* OPENGLRENDERWIDGET_HPP */

