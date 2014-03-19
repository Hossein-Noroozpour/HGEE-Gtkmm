/*
 * File:   hge-mesh-tab.hpp
 * Author: Hossein Noroozpour
 */

#ifndef HGE_MESH_TAB_HPP
#define	HGE_MESH_TAB_HPP
#include "hge-opengl-render-widget.hpp"
#include <Poco/SharedPtr.h>
namespace hge
{
	namespace ui
	{
		class MeshTab {
		public:
			MeshTab();
			~MeshTab();
			Poco::SharedPtr<Gtk::ScrolledWindow> getScrolledWindow();
		private:
			class ModelColumns : public Gtk::TreeModel::ColumnRecord
			{
			public:
				ModelColumns()
				{
					add(m_col_id); 
					add(m_col_name); 
					add(m_col_number_vertices);
				}
				Gtk::TreeModelColumn<unsigned int> m_col_id;
				Gtk::TreeModelColumn<Glib::ustring> m_col_name;
				Gtk::TreeModelColumn<unsigned int> m_col_number_vertices;
			};
			Poco::SharedPtr<ModelColumns> m_refColumns;
			Poco::SharedPtr<Gtk::Grid> m_refGrid;
			Poco::SharedPtr<Gtk::ScrolledWindow> m_refScrolledWindow;
			Poco::SharedPtr<Gtk::TreeView> m_refTreeView;
			Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
		};
	}
}
#endif

