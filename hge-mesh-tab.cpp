/* 
 * File:   hge-mesh-tab.cpp
 * Author: Hossein Noroozpour
 */

#include "hge-mesh-tab.hpp"

hge::ui::MeshTab::MeshTab():
		m_refColumns(new ModelColumns()),
		m_refGrid(new Gtk::Grid()),
		m_refScrolledWindow(new Gtk::ScrolledWindow()),
		m_refTreeView(new Gtk::TreeView())
{
	m_refScrolledWindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	m_refScrolledWindow->set_vexpand(true);
	m_refScrolledWindow->set_hexpand(true);
	
	m_refTreeView->set_vexpand(true);
	m_refTreeView->set_hexpand(true);
	
	m_refGrid->attach(*m_refTreeView, 0, 0, 1, 1);
	m_refGrid->set_vexpand(true);
	m_refGrid->set_hexpand(true);
	
	m_refScrolledWindow->add(*m_refGrid);
	
	m_refTreeModel = Gtk::ListStore::create(*m_refColumns);
	m_refTreeView->set_model(m_refTreeModel);
	
	Gtk::TreeModel::Row row = *(m_refTreeModel->append());
	row[m_refColumns->m_col_id] = 1;
	row[m_refColumns->m_col_name] = "Billy Bob";
	row[m_refColumns->m_col_number_vertices] = 10;
	
	row = *(m_refTreeModel->append());
	row[m_refColumns->m_col_id] = 2;
	row[m_refColumns->m_col_name] = "Joey Jojo";
	row[m_refColumns->m_col_number_vertices] = 20;
	
	row = *(m_refTreeModel->append());
	row[m_refColumns->m_col_id] = 3;
	row[m_refColumns->m_col_name] = "Rob McRoberts";
	row[m_refColumns->m_col_number_vertices] = 30;
	
	//Add the TreeView's view columns:
	//This number will be shown with the default numeric formatting.
	m_refTreeView->append_column("ID", m_refColumns->m_col_id);
	m_refTreeView->append_column("Name", m_refColumns->m_col_name);
	m_refTreeView->append_column("Number of vertices", m_refColumns->m_col_number_vertices);
	
	//Make all the columns reorderable:
	//This is not necessary, but it's nice to show the feature.
	//You can use TreeView::set_column_drag_function() to more
	//finely control column drag and drop.
	for(guint i = 0; i < 2; i++)
	{
		Gtk::TreeView::Column* pColumn = m_refTreeView->get_column(i);
		pColumn->set_reorderable();
	}
}
///\note There is some doubt about it!
hge::ui::MeshTab::~MeshTab()
{		
}
Poco::SharedPtr<Gtk::ScrolledWindow> hge::ui::MeshTab::getScrolledWindow()
{
	return m_refScrolledWindow;
}