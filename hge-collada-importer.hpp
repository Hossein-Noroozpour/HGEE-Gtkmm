#ifndef HGECOLLADAIMPORTER_HPP
#define	HGECOLLADAIMPORTER_HPP
#include "hge-scene-unit.hpp"
#include "hge-geometry-unit.hpp"
#include "hge-mesh-unit.hpp"
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/NodeIterator.h>
#include <Poco/DOM/NodeFilter.h>
#include <Poco/DOM/AutoPtr.h>
#include <Poco/SAX/InputSource.h>
#include <Poco/DOM/NamedNodeMap.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
//#define HGECOLLADADEBUG
#define HGEPRINTCODELINE std::cout << "Debugging: file:" << __FILE__ << " line:" << __LINE__ << std::endl << std::flush;
namespace hge
{
	namespace utility
	{
		class ColladaImporter
		{
		public:
			static std::shared_ptr<render::SceneUnit> importFromFile(const std::string& fileName);
		private:
			static std::shared_ptr<render::SceneUnit> colladaNode(Poco::XML::Node* const& node);
			static std::vector<render::GeometryUnit> libraryGeometriesNode(Poco::XML::Node* const& node,
					std::shared_ptr<render::SceneUnit>& scene);
			static render::GeometryUnit geometryNode(Poco::XML::Node* const& node);
			/// this function will be used for occlusion query object
			static render::GeometryUnit geometryNodeOcclusionQuery(Poco::XML::Node* const& node);
			/// this function will be used for terrain object
			static render::GeometryUnit geometryNodeTerrainLOD(Poco::XML::Node* const& node);
			///\warning I assumed that all UVs are sorted.
			///\warning It does not support multichannel texture coordinating.
			///\TODO Support multichannel texture coordinating.
			static std::shared_ptr<render::MeshUnit> meshNode(Poco::XML::Node* const& node, const std::string& geoid);
			static std::shared_ptr<render::MeshUnit> meshNodeOcclusionQuery(Poco::XML::Node* const& node, const std::string& geoid);
			static std::shared_ptr<render::MeshUnit> meshNodeTerrainLOD(Poco::XML::Node* const& node, const std::string& geoid);
			static std::vector<GLfloat> sourceDataNode(Poco::XML::Node* const& node);
			static std::vector<GLuint> sourcePolyListNode(Poco::XML::Node* const& node);
		};
	}
}
#endif
