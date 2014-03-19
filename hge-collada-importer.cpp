#include <Poco/DOM/Node.h>
#include "hge-collada-importer.hpp"
#include "hge-vertex-data.hpp"
#include "hge-terrain-unit.hpp"
#include <iostream>
#include <fstream>
#include <set>
#include <typeinfo>
#include <sstream>
std::shared_ptr<hge::render::SceneUnit>
hge::utility::ColladaImporter::importFromFile(const std::string& fileName)
{
	std::shared_ptr<render::SceneUnit> result;
	std::ifstream in(fileName);
	Poco::XML::InputSource inputSource(in);
	Poco::XML::DOMParser parser;
	Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&inputSource);
	Poco::XML::NodeIterator it(pDoc, Poco::XML::NodeFilter::SHOW_ELEMENT);
	Poco::XML::Node* pNode = it.nextNode();
#ifdef HGECOLLADADEBUG
	HGEPRINTCODELINE
#endif
	while (pNode)
	{
		if(pNode->nodeName() == "COLLADA")
		{
#ifdef HGECOLLADADEBUG
			HGEPRINTCODELINE
			std::cout << "I've seen collada." << std::endl;
#endif
			result = colladaNode(pNode);
		}
		pNode = pNode->nextSibling();
	}
	return result;
}
std::shared_ptr<hge::render::SceneUnit>
hge::utility::ColladaImporter::colladaNode(Poco::XML::Node* const& node)
{
	std::shared_ptr<render::SceneUnit> result(new render::SceneUnit());
	std::vector<render::GeometryUnit> geometries;
	for(auto child = node->firstChild(); child; child = child->nextSibling())
	{
		if(child->nodeName() == "library_geometries")
		{
#ifdef HGECOLLADADEBUG
			HGEPRINTCODELINE
			std::cout << "I've seen library_geometries." << std::endl;
#endif
			geometries = libraryGeometriesNode(child, result);
		}
	}
	//result->setGeometries(geometries);
	return result;
}
std::vector<hge::render::GeometryUnit>
hge::utility::ColladaImporter::libraryGeometriesNode(Poco::XML::Node* const& node, std::shared_ptr<render::SceneUnit> &scene)
{
	bool terrainNotImported = true;
	std::vector<render::GeometryUnit> result;
	for(auto child = node->firstChild(); child; child = child->nextSibling())
	{
		if(child->nodeName() == "geometry")
		{
			Poco::XML::NamedNodeMap *atts = child->attributes();
			Poco::XML::Node *nameatt = atts->getNamedItem("name");
			std::string namestr = nameatt->getNodeValue();
			atts->release();
#ifdef HGECOLLADADEBUG
			HGEPRINTCODELINE
			std::cout << "I've seen geometry." << std::endl;
#endif
			if(namestr.find("Terrain") == 0)
			{
				if(terrainNotImported)
				{
#ifdef HGECOLLADADEBUG
					HGEPRINTCODELINE
					std::cout << "I've seen a terrain." << std::endl;
					if(namestr.find("_LOD") == std::string::npos)
					{
						std::cout << "There is a bug in your scene, terrain does not have LOD." << std::endl;
						std::terminate();
					}
#endif
					//terrain prefix
					std::string terpre = "Terrain_LOD";
					//terrain prefix size
					auto tpsize = terpre.size();
					//"<number of LOD>_<LOD number>" decending from higher-more details- to lower-less details.
					auto nl_ln = namestr.substr(tpsize);
					auto nl_ln_index = nl_ln.find("_");
					char nlchararr[4];
					nlchararr[nl_ln.copy(nlchararr, nl_ln_index)] = 0;
					auto nlstr = std::string(nlchararr);
					auto lnstr = nl_ln.substr(nl_ln_index + 1);
					auto nl = std::stoi(nlstr);
					auto ln = std::stoi(lnstr);
					auto terrain = std::shared_ptr<render::TerrainUnit>(new render::TerrainUnit());
					scene->setTerrain(terrain);
					if(ln == nl)
					{
						terrainNotImported = false;
						for(auto i = nl; i >= 0; i--)
						{
							std::string terrainLodName = terpre + nlstr + "_" + std::to_string(i);
							for(auto terchild = node->firstChild(); terchild; terchild = terchild->nextSibling())
							{
								if(terchild->nodeName() == "geometry")
								{
#ifdef HGECOLLADADEBUG
									HGEPRINTCODELINE
									std::cout << "I'm searching for " << terrainLodName << "." << std::endl;
#endif
									Poco::XML::NamedNodeMap *teratts = terchild->attributes();
#ifdef HGECOLLADADEBUG
									HGEPRINTCODELINE
									std::cout << "I'm searching for " << terrainLodName << "." << std::endl;
#endif
									Poco::XML::Node *ternameatt = teratts->getNamedItem("name");
#ifdef HGECOLLADADEBUG
									HGEPRINTCODELINE
									std::cout << "I'm searching for " << terrainLodName << "." << std::endl;
#endif
									namestr = ternameatt->getNodeValue();
#ifdef HGECOLLADADEBUG
									HGEPRINTCODELINE
									std::cout << "I'm searching for " << terrainLodName << "." << std::endl;
#endif
									teratts->release();
#ifdef HGECOLLADADEBUG
									HGEPRINTCODELINE
									std::cout << "I'm searching for " << terrainLodName << "." << std::endl;
#endif
									if(terrainLodName == namestr)
									{
#ifdef HGECOLLADADEBUG
										HGEPRINTCODELINE
										std::cout << "I've seen terrain LOD " << i << " mesh." << std::endl;
#endif
										//terrain->addMesh(geometryNodeTerrainLOD(terchild).getMesh());
									}
								}
							}
						}
					}
				}
			}
			else if(namestr.find("_occlusion_test") == std::string::npos)
			{
				auto geo = geometryNode(child);
				std::string occQryStr = namestr + "_occlusion_test";
				for(auto occchild = node->firstChild(); occchild; occchild = occchild->nextSibling())
				{
					if(occchild->nodeName() == "geometry")
					{
#ifdef HGECOLLADADEBUG
						HGEPRINTCODELINE
						std::cout << "I'm searching for " << occQryStr << "." << std::endl;
#endif
						Poco::XML::NamedNodeMap *occatts = occchild->attributes();
#ifdef HGECOLLADADEBUG
						HGEPRINTCODELINE
						std::cout << "I'm searching for " << occQryStr << "." << std::endl;
#endif
						Poco::XML::Node *occnameatt = occatts->getNamedItem("name");
#ifdef HGECOLLADADEBUG
						HGEPRINTCODELINE
						std::cout << "I'm searching for " << occQryStr << "." << std::endl;
#endif
						namestr = occnameatt->getNodeValue();
#ifdef HGECOLLADADEBUG
						HGEPRINTCODELINE
						std::cout << "I'm searching for " << occQryStr << "." << std::endl;
#endif
						occatts->release();
#ifdef HGECOLLADADEBUG
						HGEPRINTCODELINE
						std::cout << "I'm searching for " << occQryStr << "." << std::endl;
#endif
						if(occQryStr == namestr)
						{
#ifdef HGECOLLADADEBUG
							HGEPRINTCODELINE
							std::cout << "I've seen occlusion query mesh." << std::endl;
#endif
							auto occgeo = geometryNodeOcclusionQuery(occchild);
							geo.setOcclusionQueryMesh(occgeo.getMesh());
							break;
						}
					}
				}
				result.push_back(geo);
			}
		}
	}
	return result;
}
hge::render::GeometryUnit
hge::utility::ColladaImporter::geometryNode(Poco::XML::Node* const& node)
{
	Poco::XML::NamedNodeMap *atts = node->attributes();
	Poco::XML::Node *idat = atts->getNamedItem("id");
	std::string idstr = idat->nodeValue();
	Poco::XML::Node *nameatt = atts->getNamedItem("name");
	std::string namestr = nameatt->getNodeValue();
	atts->release();
	render::GeometryUnit result(idstr, namestr);
	for(auto child = node->firstChild(); child; child = child->nextSibling())
	{
		if(child->nodeName() == "mesh")
		{
#ifdef HGECOLLADADEBUG
			HGEPRINTCODELINE
			std::cout << "I've seen mesh." << std::endl;
#endif
			auto mesh = meshNode(child, idstr);
			result.setMesh(mesh);
		}
	}
	return result;
}
hge::render::GeometryUnit
hge::utility::ColladaImporter::geometryNodeOcclusionQuery(Poco::XML::Node* const& node)
{
	Poco::XML::NamedNodeMap *atts = node->attributes();
	Poco::XML::Node *idat = atts->getNamedItem("id");
	std::string idstr = idat->nodeValue();
	Poco::XML::Node *nameatt = atts->getNamedItem("name");
	std::string namestr = nameatt->getNodeValue();
	atts->release();
	render::GeometryUnit result(idstr, namestr);
	for(auto child = node->firstChild(); child; child = child->nextSibling())
	{
		if(child->nodeName() == "mesh")
		{
#ifdef HGECOLLADADEBUG
			HGEPRINTCODELINE
			std::cout << "I've seen mesh for occlusion." << std::endl;
#endif
			auto mesh = meshNodeOcclusionQuery(child, idstr);
			result.setMesh(mesh);
		}
	}
	return result;
}
hge::render::GeometryUnit
hge::utility::ColladaImporter::geometryNodeTerrainLOD(Poco::XML::Node* const& node)
{
	Poco::XML::NamedNodeMap *atts = node->attributes();
	Poco::XML::Node *idat = atts->getNamedItem("id");
	std::string idstr = idat->nodeValue();
	Poco::XML::Node *nameatt = atts->getNamedItem("name");
	std::string namestr = nameatt->getNodeValue();
	atts->release();
	render::GeometryUnit result(idstr, namestr);
	for(auto child = node->firstChild(); child; child = child->nextSibling())
	{
		if(child->nodeName() == "mesh")
		{
#ifdef HGECOLLADADEBUG
			HGEPRINTCODELINE
			std::cout << "I've seen mesh for occlusion." << std::endl;
#endif
			auto mesh = meshNodeTerrainLOD(child, idstr);
			result.setMesh(mesh);
		}
	}
	return result;
}
std::shared_ptr<hge::render::MeshUnit>
hge::utility::ColladaImporter::meshNode(Poco::XML::Node* const& node, const std::string& geoid)
{
	std::string positionStr = geoid + "-positions";
	std::string normalStr   = geoid + "-normals";
	std::string uvStr       = geoid + "-map-";
	std::vector<GLfloat> positions;
	std::vector<GLfloat> normals;
	std::vector<std::vector<GLfloat> > uvs;
	std::vector<GLuint> polylist;
	std::set<hge::core::VertexData, hge::core::VertexData::Compare> vertexSet;
	for(auto child = node->firstChild(); child; child = child->nextSibling())
	{
		if(child->nodeName() == "source")
		{
			Poco::XML::NamedNodeMap * tempatts = child->attributes();
			Poco::XML::Node *tmpnode = tempatts->getNamedItem("id");
#ifdef HGECOLLADADEBUG
			HGEPRINTCODELINE
			std::cout << "I've seen source." << std::endl;
#endif
			std::string tmpstr = tmpnode->nodeValue();
			if(tmpstr == positionStr)
			{
				positions = sourceDataNode(child);
#ifdef HGECOLLADADEBUG
				HGEPRINTCODELINE
				std::cout << "Positions: ";
				for(auto i : positions)
				{
					std::cout << i << " ";
				}
				std::cout << std::endl;
#endif
			}
			else if(tmpstr == normalStr)
			{
				normals = sourceDataNode(child);
#ifdef HGECOLLADADEBUG
				HGEPRINTCODELINE
				std::cout << "Normals: ";
				for(auto i : normals)
				{
					std::cout << i << " ";
				}
				std::cout << std::endl;
#endif
			}
			else if(tmpstr.find(uvStr) == 0)
			{
				uvs.push_back(sourceDataNode(child));
#ifdef HGECOLLADADEBUG
				HGEPRINTCODELINE
				std::cout << "UVs: ";
				for(auto i : uvs[0])
				{
					std::cout << i << " ";
				}
				std::cout << "Size of UVs: " << uvs[0].size() << std::endl;
#endif
			}
			tempatts->release();
		}
	}
	for(auto child = node->firstChild(); child; child = child->nextSibling())
	{
		if(child->nodeName() == "polylist")
		{
			polylist = sourcePolyListNode(child);
#ifdef HGECOLLADADEBUG
				HGEPRINTCODELINE
				std::cout << "polylist: ";
				for(auto i : polylist)
				{
					std::cout << i << " ";
				}
				std::cout << std::endl;
#endif
		}
	}
	unsigned int j = 0;
	for(unsigned int i = 0, tmpint = 0; i < polylist.size(); j++)
	{
		core::VertexData tmpv;
		tmpint = polylist[i++] * 3;
		tmpv.px = positions[tmpint++];
		tmpv.py = positions[tmpint++];
		tmpv.pz = positions[tmpint];
		tmpint = polylist[i++] * 3;
		tmpv.nx = normals[tmpint++];
		tmpv.ny = normals[tmpint++];
		tmpv.nz = normals[tmpint];
		tmpint = polylist[i++] * 2;
		tmpv.ux = uvs[0][tmpint++];
		tmpv.uy = uvs[0][tmpint];
		auto iter = vertexSet.find(tmpv);
		if(iter == vertexSet.end())
		{
			tmpv.indices.push_back(j);
			vertexSet.insert(tmpv);
		}
		else
		{
			const_cast<std::vector<unsigned int>*>(&(iter->indices))->push_back(j);
		}
	}
#ifdef HGECOLLADADEBUG
	std::cout << "Vertices size: " << vertexSet.size() << std::endl;
	std::cout << "Indices size: " << j << std::endl;
	for(auto i : vertexSet)
	{
		i.print();
	}
	HGEPRINTCODELINE
#endif
	GLuint *indices = new GLuint[j];
	GLfloat *vertices = new GLfloat[vertexSet.size() * 8];
	unsigned int tmpint = 0, realIndex = 0;
	for(auto iter: vertexSet)
	{
		vertices[tmpint++] = iter.px;
		vertices[tmpint++] = iter.py;
		vertices[tmpint++] = iter.pz;
		vertices[tmpint++] = iter.nx;
		vertices[tmpint++] = iter.ny;
		vertices[tmpint++] = iter.nz;
		vertices[tmpint++] = iter.ux;
		vertices[tmpint++] = 1.0 - iter.uy;
		for(auto index: iter.indices)
		{
			indices[index] = realIndex;
		}
		++realIndex;
	}

	std::shared_ptr<render::MeshUnit> mesh(
			new render::MeshUnit(vertices, indices, vertexSet.size() * 8 * sizeof(GLfloat),
			vertexSet.size(), j * sizeof(GLuint)));
	return mesh;
}
std::shared_ptr<hge::render::MeshUnit>
hge::utility::ColladaImporter::meshNodeOcclusionQuery(Poco::XML::Node* const& node, const std::string& geoid)
{
	std::string positionStr = geoid + "-positions";
	std::vector<GLfloat> positions;
	std::vector<GLuint> polylist;
	std::set<hge::core::VertexData, hge::core::VertexData::Compare> vertexSet;
	for(auto child = node->firstChild(); child; child = child->nextSibling())
	{
		if(child->nodeName() == "source")
		{
			Poco::XML::NamedNodeMap *tempatts = child->attributes();
			Poco::XML::Node *tmpnode = tempatts->getNamedItem("id");
#ifdef HGECOLLADADEBUG
			HGEPRINTCODELINE
			std::cout << "I've seen source." << std::endl;
#endif
			std::string tmpstr = tmpnode->nodeValue();
			if(tmpstr == positionStr)
			{
				positions = sourceDataNode(child);
#ifdef HGECOLLADADEBUG
				HGEPRINTCODELINE
				std::cout << "Positions: ";
				for(auto i : positions)
				{
					std::cout << i << " ";
				}
				std::cout << std::endl;
#endif
			}
			tempatts->release();
		}
	}
	for(auto child = node->firstChild(); child; child = child->nextSibling())
	{
		if(child->nodeName() == "polylist")
		{
			polylist = sourcePolyListNode(child);
#ifdef HGECOLLADADEBUG
				HGEPRINTCODELINE
				std::cout << "polylist: ";
				for(auto i : polylist)
				{
					std::cout << i << " ";
				}
				std::cout << std::endl;
#endif
		}
	}
	unsigned int j = 0;
	for(unsigned int i = 0, tmpint = 0; i < polylist.size(); j++, i += 3)
	{
		core::VertexData tmpv;
		tmpint = polylist[i] * 3;
		tmpv.px = positions[tmpint++];
		tmpv.py = positions[tmpint++];
		tmpv.pz = positions[tmpint];
		///\TODO create a new VertexData to do not waste time to compare zeroes.
		tmpv.nx = 0.0;
		tmpv.ny = 0.0;
		tmpv.nz = 0.0;
		tmpv.ux = 0.0;
		tmpv.uy = 0.0;
		auto iter = vertexSet.find(tmpv);
		if(iter == vertexSet.end())
		{
			tmpv.indices.push_back(j);
			vertexSet.insert(tmpv);
		}
		else
		{
			const_cast<std::vector<unsigned int>*>(&(iter->indices))->push_back(j);
		}
	}
#ifdef HGECOLLADADEBUG
	std::cout << "Vertices size: " << vertexSet.size() << std::endl;
	std::cout << "Indices size: " << j << std::endl;
	for(auto i : vertexSet)
	{
		i.print();
	}
	HGEPRINTCODELINE
#endif
	GLuint *indices = new GLuint[j];
	GLfloat *vertices = new GLfloat[vertexSet.size() * 3];
	unsigned int tmpint = 0, realIndex = 0;
	for(auto iter: vertexSet)
	{
		vertices[tmpint++] = iter.px;
		vertices[tmpint++] = iter.py;
		vertices[tmpint++] = iter.pz;
		for(auto index: iter.indices)
		{
			indices[index] = realIndex;
		}
		++realIndex;
	}
	std::shared_ptr<render::MeshUnit> mesh(
			new render::MeshUnit(vertices, indices, vertexSet.size() * 3 * sizeof(GLfloat),
			vertexSet.size(), j * sizeof(GLuint)));
	return mesh;
}
std::shared_ptr<hge::render::MeshUnit>
hge::utility::ColladaImporter::meshNodeTerrainLOD(Poco::XML::Node* const& node, const std::string& geoid)
{
	std::string positionStr = geoid + "-positions";
	std::string normalStr   = geoid + "-normals";
	std::vector<GLfloat> positions;
	std::vector<GLfloat> normals;
	std::vector<GLuint> polylist;
	std::set<hge::core::VertexData, hge::core::VertexData::Compare> vertexSet;
	for(auto child = node->firstChild(); child; child = child->nextSibling())
	{
		if(child->nodeName() == "source")
		{
			Poco::XML::NamedNodeMap * tempatts = child->attributes();
			Poco::XML::Node *tmpnode = tempatts->getNamedItem("id");
#ifdef HGECOLLADADEBUG
			HGEPRINTCODELINE
			std::cout << "I've seen source." << std::endl;
#endif
			std::string tmpstr = tmpnode->nodeValue();
			if(tmpstr == positionStr)
			{
				positions = sourceDataNode(child);
#ifdef HGECOLLADADEBUG
				HGEPRINTCODELINE
				std::cout << "Positions: ";
				for(auto i : positions)
				{
					std::cout << i << " ";
				}
				std::cout << std::endl;
#endif
			}
			else if(tmpstr == normalStr)
			{
				normals = sourceDataNode(child);
#ifdef HGECOLLADADEBUG
				HGEPRINTCODELINE
				std::cout << "Normals: ";
				for(auto i : normals)
				{
					std::cout << i << " ";
				}
				std::cout << std::endl;
#endif
			}
			tempatts->release();
		}
	}
	for(auto child = node->firstChild(); child; child = child->nextSibling())
	{
		if(child->nodeName() == "polylist")
		{
			polylist = sourcePolyListNode(child);
#ifdef HGECOLLADADEBUG
				HGEPRINTCODELINE
				std::cout << "polylist: ";
				for(auto i : polylist)
				{
					std::cout << i << " ";
				}
				std::cout << std::endl;
#endif
		}
	}
	unsigned int j = 0;
	for(unsigned int i = 0, tmpint = 0; i < polylist.size(); j++)
	{
		core::VertexData tmpv;
		tmpint = polylist[i++] * 3;
		tmpv.px = positions[tmpint++];
		tmpv.py = positions[tmpint++];
		tmpv.pz = positions[tmpint];
		tmpint = polylist[i++] * 3;
		tmpv.nx = normals[tmpint++];
		tmpv.ny = normals[tmpint++];
		tmpv.nz = normals[tmpint];
		i++;
		tmpv.ux = 0.0;
		tmpv.uy = 0.0;
		auto iter = vertexSet.find(tmpv);
		if(iter == vertexSet.end())
		{
			tmpv.indices.push_back(j);
			vertexSet.insert(tmpv);
		}
		else
		{
			const_cast<std::vector<unsigned int>*>(&(iter->indices))->push_back(j);
		}
	}
#ifdef HGECOLLADADEBUG
	std::cout << "Vertices size: " << vertexSet.size() << std::endl;
	std::cout << "Indices size: " << j << std::endl;
	for(auto i : vertexSet)
	{
		i.print();
	}
	HGEPRINTCODELINE
#endif
	GLuint *indices = new GLuint[j];
	GLfloat *vertices = new GLfloat[vertexSet.size() * 6];
	unsigned int tmpint = 0, realIndex = 0;
	for(auto iter: vertexSet)
	{
		vertices[tmpint++] = iter.px;
		vertices[tmpint++] = iter.py;
		vertices[tmpint++] = iter.pz;
		vertices[tmpint++] = iter.nx;
		vertices[tmpint++] = iter.ny;
		vertices[tmpint++] = iter.nz;
		for(auto index: iter.indices)
		{
			indices[index] = realIndex;
		}
		++realIndex;
	}
	std::shared_ptr<render::MeshUnit> mesh(
			new render::MeshUnit(vertices, indices, vertexSet.size() * 6 * sizeof(GLfloat),
			vertexSet.size(), j * sizeof(GLuint)));
	return mesh;
}
std::vector<GLfloat>
hge::utility::ColladaImporter::sourceDataNode(Poco::XML::Node* const& node)
{
	std::vector<GLfloat> result;
	for(auto child = node->firstChild(); child; child = child->nextSibling())
	{
		if(child->nodeName() == "float_array")
		{
			Poco::XML::NamedNodeMap *tempatts = child->attributes();
			Poco::XML::Node *tmpnode = tempatts->getNamedItem("count");
			unsigned long numVertices = std::stoul(tmpnode->nodeValue());
			std::string tmpstr = child->innerText();
			std::stringstream ssin(tmpstr);
			for(unsigned long i = 0; i < numVertices; i++)
			{
				ssin >> tmpstr;
				result.push_back(std::stof(tmpstr));
			}
			tempatts->release();
		}
	}
	return result;
}
std::vector<GLuint>
hge::utility::ColladaImporter::sourcePolyListNode(Poco::XML::Node* const& node)
{
#ifdef HGECOLLADADEBUG
	HGEPRINTCODELINE
#endif
	std::vector<GLuint> result;
	Poco::XML::NamedNodeMap *tempatts;
	Poco::XML::Node *tempnode;
	std::string tempstr;
	tempatts = node->attributes();
	tempstr = std::string("count");
	tempnode = tempatts->getNamedItem(tempstr);
#ifdef HGECOLLADADEBUG
	HGEPRINTCODELINE
#endif
	unsigned int numberOfFaces = std::stoul(tempnode->nodeValue());
	tempatts->release();
	for(auto child = node->firstChild(); child; child = child->nextSibling())
	{
		if(child->nodeName() == "vcount")
		{
			tempstr = child->innerText();
			std::stringstream ssin(tempstr);
			for(unsigned int i = 0; i < numberOfFaces; ++i)
			{
				ssin >> tempstr;
				if(std::stoi(tempstr) != 3)
				{
					std::cerr << "Error: Critical. Line: " << __LINE__;
					std::cerr << ", File: " << __FILE__ << std::endl;
					std::cerr << "Object must be triangular!" << std::endl;
					std::terminate();
				}
			}
		}
		else if(child->nodeName() == "p")
		{
			tempstr = child->innerText();
			std::stringstream ssin(tempstr);
			for(unsigned int i = 0; i < numberOfFaces * 9; ++i)
			{
				ssin >> tempstr;
				result.push_back(std::stoi(tempstr));
			}
		}
	}
	return result;
}
