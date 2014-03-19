#include "hge-opengl-render-widget.hpp"
#include <iostream>
hge::ui::OpenGLRenderWidget::OpenGLRenderWidget(volatile double *frame_rate_per_second,
		std::shared_ptr<core::Application> hgeapp):
		da(new Gtk::DrawingArea()),
		xd(gdk_x11_display_get_xdisplay((da->get_display())->gobj())),
		frps(frame_rate_per_second),
		hgeapp(hgeapp),
		is_not_drawn(true)
{
	hgeapp->start();//Starting application--------------------------------
	if(!glXQueryExtension(xd, 0, 0))
	{
		std::cout << "OpenGL not supported\n";
	}
	int attrlist [] =
	{
		GLX_RGBA,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_DOUBLEBUFFER,
		None
	};
	xvi = glXChooseVisual( xd,
		gdk_x11_screen_get_screen_number
		((da->get_screen())->gobj()),
		attrlist);
	if( xvi == 0 )
	{
		std::cerr << "Error configuring OpenGL\n";
	}
	da->set_vexpand(true);
	da->set_hexpand(true);
	da->set_double_buffered(false);
	glxc = glXCreateContext(xd, xvi, NULL, TRUE);
	da->set_events(Gdk::ALL_EVENTS_MASK);
	da->signal_configure_event().connect
			(sigc::mem_fun(*this,
			&hge::ui::OpenGLRenderWidget::on_configure_event));
	da->signal_draw().connect
			(sigc::mem_fun(*this,
			&hge::ui::OpenGLRenderWidget::on_draw));
	da->signal_button_press_event().connect
			(sigc::mem_fun(*this,
			&hge::ui::OpenGLRenderWidget::on_button_press_event));
	da->signal_button_release_event().connect
			(sigc::mem_fun(*this,
			&hge::ui::OpenGLRenderWidget::on_button_release_event));
	da->signal_key_press_event().connect
			(sigc::mem_fun(*this,
			&hge::ui::OpenGLRenderWidget::on_key_press_event));
	da->signal_key_release_event().connect
			(sigc::mem_fun(*this,
			&hge::ui::OpenGLRenderWidget::on_key_release_event));
	da->signal_motion_notify_event().connect
			(sigc::mem_fun(*this,
			&hge::ui::OpenGLRenderWidget::on_motion_notify_event));
	da->signal_scroll_event().connect
			(sigc::mem_fun(*this,
			&hge::ui::OpenGLRenderWidget::on_scroll_event));
}
hge::ui::OpenGLRenderWidget::~OpenGLRenderWidget()
{
}

bool hge::ui::OpenGLRenderWidget::on_configure_event(GdkEventConfigure *e)
{
	if(!glXMakeCurrent
		(xd, gdk_x11_window_get_xid(da->get_window()->gobj()), glxc))
	{
		return false;
	}
	GLsizei width = da->get_allocated_width();
	GLsizei height = da->get_allocated_height();
	GLsizei size = MIN( width, height );
	glViewport(0, 0, width, height);
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_draw(
	const Cairo::RefPtr<Cairo::Context> &c)
{
	if(is_not_drawn)
	{
		if (glewInit())
		{
			std::cerr << "Critical Error! In line: " << __LINE__ <<
					" in file: " << __FILE__ << std::endl <<
					"Unable to initialize GLEW!" << std::endl;
			std::terminate();
		}
		glClearColor(0.0, 0.0, 0.0, 0.0);
		Glib::signal_timeout().connect(sigc::mem_fun(*this,
			&hge::ui::OpenGLRenderWidget::render_loop), 17, 10);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		hgeapp->initialize();
		is_not_drawn = false;
	}
	return true;
}
Gtk::DrawingArea *hge::ui::OpenGLRenderWidget::get_widget()
{
	return da;
}
bool hge::ui::OpenGLRenderWidget::render_loop(void)
{
	if(!glXMakeCurrent(xd, gdk_x11_window_get_xid(da->get_window()->gobj()), glxc))
	{
		return false;
	}
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	hgeapp->update();
	glFinish();
	glXSwapBuffers( xd, gdk_x11_window_get_xid(da->get_window()->gobj()));
	t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span =
		std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	*frps = 1.0/time_span.count();
	t1 = std::chrono::high_resolution_clock::now();
	return true;
}
void hge::ui::OpenGLRenderWidget::set_frame_rate_per_second_pointer(
	volatile double *frame_rate_per_second)
{
	frps = frame_rate_per_second;
}
bool hge::ui::OpenGLRenderWidget::on_button_press_event(GdkEventButton *event)
{
	switch(event->button)
	{
		case 1:
			hgeapp->buttonPressed(core::Application::leftMouseButton);
			break;
		case 2:
			hgeapp->buttonPressed(core::Application::middleMouseButton);
			break;
		case 3:
			hgeapp->buttonPressed(core::Application::rightMouseButton);
			break;
		case 4:
			break;
		case 5:
			break;
	}
	return true;
}
bool hge::ui::OpenGLRenderWidget::on_button_release_event(GdkEventButton *event)
{
	switch(event->button)
	{
		case 1:
			hgeapp->buttonReleased(core::Application::leftMouseButton);
			break;
		case 2:
			hgeapp->buttonReleased(core::Application::middleMouseButton);
			break;
		case 3:
			hgeapp->buttonReleased(core::Application::rightMouseButton);
			break;
		case 4:
			break;
		case 5:
			break;
	}
	return true;
}
void hge::ui::OpenGLRenderWidget::on_child_notify(GParamSpec *pspec){}
void hge::ui::OpenGLRenderWidget::on_composited_changed(){}
bool hge::ui::OpenGLRenderWidget::on_damage_event(GdkEventExpose *event)
{
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_delete_event(GdkEventAny *event)
{
	return false;
}
void hge::ui::OpenGLRenderWidget::on_direction_changed(
	Gtk::TextDirection direction)
{

}
void hge::ui::OpenGLRenderWidget::on_drag_begin(
	const Glib::RefPtr<Gdk::DragContext> &context)
{

}
void hge::ui::OpenGLRenderWidget::on_drag_data_delete(
	const Glib::RefPtr<Gdk::DragContext> &context)
{

}
void hge::ui::OpenGLRenderWidget::on_drag_data_get(
	const Glib::RefPtr<Gdk::DragContext> &context,
	Gtk::SelectionData &selection_data, guint info, guint time)
{

}
void hge::ui::OpenGLRenderWidget::on_drag_data_received(
	const Glib::RefPtr<Gdk::DragContext> &context, int x, int y,
	const Gtk::SelectionData &selection_data, guint info, guint time)
{

}
bool hge::ui::OpenGLRenderWidget::on_drag_drop(
	const Glib::RefPtr<Gdk::DragContext> &context, int x, int y, guint time)
{
	return false;
}
void hge::ui::OpenGLRenderWidget::on_drag_end(
	const Glib::RefPtr<Gdk::DragContext> &context)
{

}
bool hge::ui::OpenGLRenderWidget::on_drag_failed(
	const Glib::RefPtr<Gdk::DragContext> &context, Gtk::DragResult result)
{
	return false;
}
void hge::ui::OpenGLRenderWidget::on_drag_leave(
	const Glib::RefPtr<Gdk::DragContext> &context, guint time)
{

}
bool hge::ui::OpenGLRenderWidget::on_drag_motion(
	const Glib::RefPtr<Gdk::DragContext> &context, int x, int y, guint time)
{
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_enter_notify_event(
	GdkEventCrossing *event)
{
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_event(GdkEvent *event)
{
	return false;
}
void hge::ui::OpenGLRenderWidget::on_event_after(GdkEvent *event)
{

}
bool hge::ui::OpenGLRenderWidget::on_focus(Gtk::DirectionType direction)
{
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_focus_in_event(GdkEventFocus *event)
{
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_focus_out_event(GdkEventFocus *event)
{
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_grab_broken_event(
	GdkEventGrabBroken *event)
{
	return false;
}
void hge::ui::OpenGLRenderWidget::on_grab_focus()
{

}
void hge::ui::OpenGLRenderWidget::on_grab_notify(bool was_grabbed)
{

}
void hge::ui::OpenGLRenderWidget::on_hide()
{

}
void hge::ui::OpenGLRenderWidget::on_hierarchy_changed(
	Gtk::Widget *previous_toplevel)
{

}
bool hge::ui::OpenGLRenderWidget::on_key_press_event(GdkEventKey* event)
{
//	switch(event->keyval)
//	{
//		case GDK_KEY_a :
//			hgeapp->buttonPressed(core::Application::aKeyButton);
//			break;
//		case GDK_KEY_d :
//			hgeapp->buttonPressed(core::Application::dKeyButton);
//			break;
//		case GDK_KEY_s :
//			hgeapp->buttonPressed(core::Application::sKeyButton);
//			break;
//		case GDK_KEY_w :
//			hgeapp->buttonPressed(core::Application::wKeyButton);
//			break;
//	}
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_key_release_event(GdkEventKey *event)
{
//	switch(event->keyval)
//	{
//		case GDK_KEY_a :
//			hgeapp->buttonReleased(core::Application::aKeyButton);
//			break;
//		case GDK_KEY_d :
//			hgeapp->buttonReleased(core::Application::dKeyButton);
//			break;
//		case GDK_KEY_s :
//			hgeapp->buttonReleased(core::Application::sKeyButton);
//			break;
//		case GDK_KEY_w :
//			hgeapp->buttonReleased(core::Application::wKeyButton);
//			break;
//	}
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_leave_notify_event(
	GdkEventCrossing *event)
{
	return false;
}
void hge::ui::OpenGLRenderWidget::on_map()
{
}
bool hge::ui::OpenGLRenderWidget::on_map_event(GdkEventAny *event)
{
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_mnemonic_activate(bool group_cycling)
{
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_motion_notify_event(
	GdkEventMotion *event)
{
	hgeapp->mouseMoved(event->x - preX, event->y - preY);
	preX = event->x;
	preY = event->y;
	return true;
}
void hge::ui::OpenGLRenderWidget::on_parent_changed(
	Gtk::Widget *previous_parent)
{

}
bool hge::ui::OpenGLRenderWidget::on_popup_menu()
{
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_property_notify_event(
	GdkEventProperty *event)
{
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_proximity_in_event(
	GdkEventProximity *event)
{
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_proximity_out_event(
	GdkEventProximity *event)
{
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_query_tooltip(
	int x, int y, bool keyboard_tooltip,
	const Glib::RefPtr<Gtk::Tooltip> &tooltip)
{
	return false;
}
void hge::ui::OpenGLRenderWidget::on_realize()
{
}
void hge::ui::OpenGLRenderWidget::on_screen_changed(
	const Glib::RefPtr<Gdk::Screen> &previous_screen)
{

}
bool hge::ui::OpenGLRenderWidget::on_scroll_event(
	GdkEventScroll *event)
{
	return true;
}
bool hge::ui::OpenGLRenderWidget::on_selection_clear_event(
	GdkEventSelection *event)
{
	return false;
}
void hge::ui::OpenGLRenderWidget::on_selection_get(
	Gtk::SelectionData &selection_data, guint info, guint time)
{

}
bool hge::ui::OpenGLRenderWidget::on_selection_notify_event(
	GdkEventSelection *event)
{
	return false;
}
void hge::ui::OpenGLRenderWidget::on_selection_received(
	const Gtk::SelectionData &selection_data, guint time)
{

}
bool hge::ui::OpenGLRenderWidget::on_selection_request_event(
	GdkEventSelection *event)
{
	return false;
}
void hge::ui::OpenGLRenderWidget::on_show()
{

}
void hge::ui::OpenGLRenderWidget::on_size_allocate(
	Gtk::Allocation& allocation)
{

}
void hge::ui::OpenGLRenderWidget::on_state_changed(
	Gtk::StateType previous_state)
{

}
void hge::ui::OpenGLRenderWidget::on_state_flags_changed(
	Gtk::StateFlags previous_state_flags)
{

}
void hge::ui::OpenGLRenderWidget::on_style_updated()
{

}
bool hge::ui::OpenGLRenderWidget::on_touch_event(GdkEventTouch *event)
{
	return false;
}
void hge::ui::OpenGLRenderWidget::on_unmap()
{
}
bool hge::ui::OpenGLRenderWidget::on_unmap_event(GdkEventAny *event)
{
	return false;
}
void hge::ui::OpenGLRenderWidget::on_unrealize()
{
}
bool hge::ui::OpenGLRenderWidget::on_visibility_notify_event(
	GdkEventVisibility *event)
{
	return false;
}
bool hge::ui::OpenGLRenderWidget::on_window_state_event(
	GdkEventWindowState *event)
{
	return false;
}
