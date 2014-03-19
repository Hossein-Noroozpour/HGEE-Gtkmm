#include "hge-main-window.hpp"
#include "hge-menubar.hpp"
#include "hge-toolbar.hpp"
#include "hge-statusbar.hpp"
#include "hge-side-window.hpp"
#include <iostream>
hge::ui::MainWindow::MainWindow(const std::shared_ptr<core::Application> &hgeapp):
	hgeapp(hgeapp)
{
	set_title("Hulixerian Game Engine Editor");
	set_default_size(1000, 600);
	set_position(Gtk::WIN_POS_CENTER);
	Glib::RefPtr<Gdk::Pixbuf> m_task_bar_image =
		Gdk::Pixbuf::create_from_file("HGE-Logo64x64.png");
	set_default_icon(m_task_bar_image);
	set_events(Gdk::ALL_EVENTS_MASK);
	set_border_width(5);

	m_tray_icon = Gtk::StatusIcon::create(m_task_bar_image);
	m_tray_icon->set_visible(true);

	m_viewport = new Gtk::Grid();
	m_viewport->set_events(Gdk::ALL_EVENTS_MASK);
	m_viewport->set_hexpand(true);
	m_viewport->set_vexpand(true);

	m_openGLRenderDevice = new OpenGLRenderWidget(&m_frame_rate_per_second,
		hgeapp);

	m_viewport->attach(*(m_openGLRenderDevice->get_widget()), 0, 0, 1, 1);



	m_pane_main = new Gtk::Paned(Gtk::ORIENTATION_HORIZONTAL);
	m_pane_main->set_events(Gdk::ALL_EVENTS_MASK);
	m_pane_main->pack1(*m_viewport, true, true);
	m_pane_main->pack2(*(new SideWindow()), true, true);
	m_pane_main->set_position(850);

	m_grid = new Gtk::Grid();
	m_grid->set_events(Gdk::ALL_EVENTS_MASK);
	add(*m_grid);
	m_grid->set_vexpand(true);
	m_grid->set_hexpand(true);
	m_grid->attach(*(new MenuBar()), 0, 0, 1, 1);
	m_grid->attach(*(new ToolBar(hgeapp)), 0, 1, 1, 1);
	m_grid->attach(*m_pane_main, 0, 2, 1, 1);
	m_grid->attach(*(new StatusBar()), 0, 3, 1, 1);

	show_all_children(true);
}
hge::ui::MainWindow::~MainWindow()
{
}
//void hge::ui::MainWindow::on_menu_file_new(){}
//void hge::ui::MainWindow::on_menu_file_add()
//{
//	add_file();
//}
//void hge::ui::MainWindow::on_tool_bar_file_add()
//{
//	add_file();
//}
void hge::ui::MainWindow::add_file()
{
	Gtk::Window *addwin = new Gtk::Window();
	addwin->set_title("Add");
	Gtk::Grid *addgrid = new Gtk::Grid();
	addwin->add(*addgrid);
	addwin->set_resizable(false);
	addwin->set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);
	Gtk::RadioButton *addcollada = new Gtk::RadioButton(
		"Import from _Collada file.", true);
	addgrid->attach(*addcollada, 0, 0, 1, 1);
	Gtk::RadioButtonGroup addradiogroup = addcollada->get_group();
	Gtk::RadioButton *addhgemesh = new Gtk::RadioButton(addradiogroup,
		"Import from _HGE-Mesh file.", true);
	addgrid->attach(*addhgemesh, 0, 1, 1, 1);
	Gtk::FileChooserButton *fcbcollada = new Gtk::FileChooserButton(
		"Select your Collada file");
	Glib::RefPtr<Gtk::FileFilter> colladafilter = Gtk::FileFilter::create();
	colladafilter->add_pattern("*.[Dd][Aa][Ee]");
	fcbcollada->set_filter(colladafilter);
	addgrid->attach(*fcbcollada, 0, 2, 1, 1);
	Gtk::FileChooserButton *fcbhgemesh = new Gtk::FileChooserButton(
		"Select your HGE-Mesh file");
	Glib::RefPtr<Gtk::FileFilter> hgemeshfilter = Gtk::FileFilter::create();
	hgemeshfilter->add_pattern("*.[Hh][Gg][Ee]");
	fcbhgemesh->set_filter(hgemeshfilter);
	addgrid->attach(*fcbhgemesh, 0, 3, 1, 1);
	Gtk::Button *addbutton = new Gtk::Button("_Add", true);
	addgrid->attach(*addbutton, 0, 4, 1, 1);
	addwin->show_all();
	fcbhgemesh->set_visible(false);
	addbutton->set_visible(false);
	auto colladaradioclicked = [=] ()
	{
		fcbhgemesh->set_visible(false);
		fcbcollada->set_visible(true);
		if(fcbcollada->get_filenames().size() == 0)
		{
			addbutton->set_visible(false);
		}
		else
		{
			addbutton->set_visible(true);
		}
	};
	auto hgemeshradioclicked = [=] ()
	{
		fcbhgemesh->set_visible(true);
		fcbcollada->set_visible(false);
		if(fcbhgemesh->get_filenames().size() == 0)
		{
			addbutton->set_visible(false);
		}
		else
		{
			addbutton->set_visible(true);
		}
	};
	auto fcbcolladachange = [=] ()
	{
		if(fcbcollada->get_filenames().size() == 0)
		{
			addbutton->set_visible(false);
		}
		else
		{
			addbutton->set_visible(true);
		}
	};
	auto fcbhgemeshchange = [=] ()
	{
		if(fcbhgemesh->get_filenames().size() == 0)
		{
			addbutton->set_visible(false);
		}
		else
		{
			addbutton->set_visible(true);
		}
	};
	auto addoccurred = [=] ()
	{
		if(addcollada->get_active())
		{
			if(!hgeapp->addFromColladaFile(fcbcollada->get_filename()))
			{
				Gtk::MessageDialog error(*addwin, "<b>Error in parsing Collada "
					"file.</b>\n<i>For more information see standard error "
					"output.</i>", true, Gtk::MessageType::MESSAGE_ERROR,
					Gtk::ButtonsType::BUTTONS_CLOSE, true);
				error.run();
			}
		}
		else if(addhgemesh->get_active())
		{
			if(!hgeapp->addFromHGEFile(fcbhgemesh->get_filename()))
			{
				Gtk::MessageDialog error(*addwin, "<b>Error in parsing HGE-Mesh "
					"file.</b>\n<i>For more information see standard error "
					"output.</i>", true, Gtk::MessageType::MESSAGE_ERROR,
					Gtk::ButtonsType::BUTTONS_CLOSE, true);
				error.run();
			}
		}
	};
	//connections
	addcollada->signal_clicked().connect(colladaradioclicked);
	addhgemesh->signal_clicked().connect(hgemeshradioclicked);
	fcbcollada->signal_selection_changed().connect(fcbcolladachange);
	fcbhgemesh->signal_selection_changed().connect(fcbhgemeshchange);
	addbutton->signal_clicked().connect(addoccurred);
}
void hge::ui::MainWindow::on_menu_file_open(){}
void hge::ui::MainWindow::on_menu_file_quit(){}
void hge::ui::MainWindow::on_menu_others(){}
void hge::ui::MainWindow::on_menu_choices_one(){}
void hge::ui::MainWindow::on_menu_choices_two(){}
//bool hge::ui::MainWindow::update_frame_rate_per_second_label()
//{
//	m_frame_rate_label->set_text(Glib::ustring::compose("%1",
//		m_frame_rate_per_second));
//	return true;
//}
bool hge::ui::MainWindow::on_key_press_event(GdkEventKey *event)
{
	switch(event->keyval)
	{
		case GDK_KEY_a :
			hgeapp->buttonPressed(core::Application::aKeyButton);
			break;
		case GDK_KEY_d :
			hgeapp->buttonPressed(core::Application::dKeyButton);
			break;
		case GDK_KEY_s :
			hgeapp->buttonPressed(core::Application::sKeyButton);
			break;
		case GDK_KEY_w :
			hgeapp->buttonPressed(core::Application::wKeyButton);
			break;
	}
}
bool hge::ui::MainWindow::on_key_release_event(GdkEventKey *event)
{
	switch(event->keyval)
	{
		case GDK_KEY_a :
			hgeapp->buttonReleased(core::Application::aKeyButton);
			break;
		case GDK_KEY_d :
			hgeapp->buttonReleased(core::Application::dKeyButton);
			break;
		case GDK_KEY_s :
			hgeapp->buttonReleased(core::Application::sKeyButton);
			break;
		case GDK_KEY_w :
			hgeapp->buttonReleased(core::Application::wKeyButton);
			break;
	}
}
