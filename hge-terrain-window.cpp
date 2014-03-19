#include "hge-terrain-window.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <cmath>
#include "hge-terrain-unit.hpp"
#define NORMALCALCULATIONDEBUGMODE
//#define NORMALCALCULATIONDEBUGMOD2
#define NUMBEROFBUFFERCOMPONENTS 6
#define NUMBEROFLODS 4
#define TERRAINALGORITHMTHREADNUMBER 4
#define HGEPRINTCODELINE std::cout << "Debugging: file:" << __FILE__ << " line:" << __LINE__ << std::endl << std::flush;
#define PRINTVECTOR(v) std::cout << " x: " << v.x << " y: " << v.y << " z: " << v.z << std::endl;
#define NORMALCALCULATIONDEBUGPRINT \
if(tmpv.z < 0.0)\
{\
	std::cerr << "Error in normal calculation.";\
	HGEPRINTCODELINE\
	std::terminate();\
}
#define CHECKLENGTHZERO \
if(glm::length(tmpv1) == 0.0)\
{\
	std::cerr << "Error normal is zero." << std::endl;\
	PRINTVECTOR(tmpv2)\
	PRINTVECTOR(tmpv3)\
	HGEPRINTCODELINE \
	std::terminate();\
}
#define D1toD2(arr, row, col) arr[(row * width) + col]
hge::ui::TerrainWindow::TerrainWindow(const std::shared_ptr<core::Application> &application):
	application(application)
{
	set_title("Terrain Setting");
	set_position(Gtk::WindowPosition::WIN_POS_CENTER);
	set_border_width(5);

	grid = std::shared_ptr<Gtk::Grid>(new Gtk::Grid());
	grid->set_column_spacing(5);
	grid->set_row_spacing(5);
	grid->set_vexpand(true);
	grid->set_hexpand(true);
	add(*grid);

	imagePreviewSectionLabel = std::shared_ptr<Gtk::Label>(new Gtk::Label("Terrain Image Preview Section"));
	imagePreviewSectionLabel->set_vexpand(false);
	imagePreviewSectionLabel->set_hexpand(true);
	grid->attach(*imagePreviewSectionLabel, 0, 0, 2, 1);

	imageAddressLabel = std::shared_ptr<Gtk::Label>(new Gtk::Label("Terrain image address"));
	imageAddressLabel->set_hexpand(true);
	imageAddressLabel->set_vexpand(false);
	grid->attach(*imageAddressLabel, 0, 1, 1, 1);

	imagePreviewChooser = std::shared_ptr<Gtk::FileChooserButton>(new Gtk::FileChooserButton());
	imagePreviewChooser->set_hexpand(true);
	imagePreviewChooser->set_vexpand(false);
	imagePreviewChooser->signal_selection_changed().connect(sigc::mem_fun(*this,
		&hge::ui::TerrainWindow::onImageFileChanged));
	grid->attach(*imagePreviewChooser, 1, 1, 1, 1);

	imageViewport = std::shared_ptr<Gtk::ScrolledWindow>(new Gtk::ScrolledWindow());
	imageViewport->set_min_content_height(128);
	imageViewport->set_min_content_width(128);
	imageViewport->set_hexpand(true);
	imageViewport->set_vexpand(true);
	imagePreview = std::shared_ptr<Gtk::Image>(new Gtk::Image("default terrain.jpg"));
	imageViewport->add(*imagePreview);
	grid->attach(*imageViewport, 0, 2, 2, 1);

	loadTerrain = std::shared_ptr<Gtk::Button>(new Gtk::Button("Load Terrain"));
	loadTerrain->set_hexpand(true);
	loadTerrain->set_vexpand(false);
	loadTerrain->signal_clicked().connect(sigc::mem_fun(*this,
		&hge::ui::TerrainWindow::onLoadClicked));
	grid->attach(*loadTerrain, 0, 3, 2, 1);

	show_all();
}
void hge::ui::TerrainWindow::onImageFileChanged()
{
	auto fileName = imagePreviewChooser->get_filenames()[0];
	if(fileName.size() != 0)
	{
		imagePreview->set(fileName);
	}
}
void hge::ui::TerrainWindow::onLoadClicked()
{
	Glib::Mutex::Lock lock(loadTerrainButtonMutex);
	loadTerrain->set_sensitive(false);
	auto pixBuf = imagePreview->get_pixbuf();
#ifdef HGETERRAINWINDOWDEBUG
	std::cout << pixBuf->get_height() << std::endl;
	std::cout << pixBuf->get_width() << std::endl;
	std::cout << pixBuf->get_rowstride() << std::endl;
#endif
	height = pixBuf->get_height();
	width = pixBuf->get_width();
	rowStrid = pixBuf->get_rowstride();
	componentBytes = rowStrid / width;
	pixels = pixBuf->get_pixels();
	Glib::Thread *threads[TERRAINALGORITHMTHREADNUMBER];
	buffer = new GLfloat**[height];
	for(unsigned int i = 0, y = height, pixelIndex = 0; i < height; i++, y--)
	{
		buffer[i] = new GLfloat*[width];
		for(unsigned int j = 0; j < width; j++)
		{
			buffer[i][j] = new GLfloat[NUMBEROFBUFFERCOMPONENTS];
			unsigned int tmpui = 0;
			for(unsigned int k = 0; k < componentBytes; k++, pixelIndex++)
			{
				tmpui <<= 8;
				tmpui += pixels[pixelIndex];
			}
			buffer[i][j][0] = (float)j - (width/2.0);
			buffer[i][j][1] = (float)y - (height/2.0);
			buffer[i][j][2] = 50.0f ;//* (float(tmpui - 200) / float(1 << (componentBytes * 8)));
		}
	}
	for(int i = 0; i < TERRAINALGORITHMTHREADNUMBER; i++)
	{
		threads[i] = Glib::Thread::create(std::bind(&TerrainWindow::calculateNormals, this, i));
	}
	auto terrain = std::shared_ptr<render::TerrainUnit>(new render::TerrainUnit());
	auto ibo = new GLuint[(height-1)*(width-1)*6];
	for(unsigned int l = 0, iboIndex = 0; l < NUMBEROFLODS; l++, iboIndex = 0)
	{
		for(unsigned int i = 0, lStride = 1 << l; i < height - lStride; i += lStride)
		{
			for(unsigned int j = 0; j < width - lStride; j += lStride)
			{
				ibo[iboIndex++] = ( i            * width) + j;
				ibo[iboIndex++] = ((i + lStride) * width) + j;
				ibo[iboIndex++] = ((i + lStride) * width) + j + lStride;
				ibo[iboIndex++] = ( i            * width) + j;
				ibo[iboIndex++] = ((i + lStride) * width) + j + lStride;
				ibo[iboIndex++] = ( i            * width) + j + lStride;
			}
		}
		terrain->addIBO(ibo, ((height >> l) - 1) * ((width >> l) - 1) * 6 * sizeof(GLuint));
	}
	for(int i = 0; i < TERRAINALGORITHMTHREADNUMBER; i++)
	{
		threads[i]->join();
	}
	auto vbo = new GLfloat[height * width * 6];
	for(unsigned int i = 0, vboIndex = 0; i < height; i++)
	{
		for(unsigned int j = 0; j < width; j++)
		{
			for(unsigned int k = 0; k < 6; k++, vboIndex++)
			{
				vbo[vboIndex] = buffer[i][j][k];
			}
			delete [] buffer[i][j];
		}
		delete [] buffer[i];
	}
	terrain->setVBO(vbo, height * width * 6 * sizeof(GLfloat));
	application->addTerrain(terrain);
	delete [] ibo;
	delete [] vbo;
	delete [] buffer;
	loadTerrain->set_sensitive(true);
}
void hge::ui::TerrainWindow::calculateNormals(unsigned int threadIndex)
{
	for(unsigned int i = (unsigned int)ceil(((float)(height * threadIndex))/TERRAINALGORITHMTHREADNUMBER),
			endRow = ((height * (threadIndex+1))/TERRAINALGORITHMTHREADNUMBER); i < endRow; i++)
	{
		for(unsigned int j = 0; j < width; j++)
		{
			glm::vec3 nv(0.0f, 0.0f, 0.0f);
			if(i > 0)
			{
				if(j > 0)
				{
					auto tmpv2 = glm::vec3(-1.0f, 1.0f, buffer[i-1][j-1][2] - buffer[i][j][2]);
					auto tmpv3 = glm::vec3(-1.0f, 0.0f, buffer[i  ][j-1][2] - buffer[i][j][2]);
					auto tmpv1 = glm::cross(tmpv2, tmpv3);
#ifdef NORMALCALCULATIONDEBUGMODE
					CHECKLENGTHZERO
#endif
					auto tmpv  = glm::normalize(tmpv1);
#ifdef NORMALCALCULATIONDEBUGMODE
					NORMALCALCULATIONDEBUGPRINT
#endif
					nv += tmpv;
					tmpv3 = tmpv2;
					tmpv2 = glm::vec3(0.0f, 1.0f, buffer[i-1][j][2] - buffer[i][j][2]);
					tmpv1 = glm::cross(tmpv2, tmpv3);
#ifdef NORMALCALCULATIONDEBUGMODE
					CHECKLENGTHZERO
#endif
					tmpv = glm::normalize(tmpv1);
#ifdef NORMALCALCULATIONDEBUGMODE
					NORMALCALCULATIONDEBUGPRINT
#endif
					nv += tmpv;
				}
				if(j < width - 1)
				{
					auto tmpv2 = glm::vec3(1.0f, 1.0f, buffer[i-1][j+1][2] - buffer[i][j][2]);
					auto tmpv3 = glm::vec3(0.0f, 1.0f, buffer[i-1][j  ][2] - buffer[i][j][2]);
					auto tmpv1 = glm::cross(tmpv2, tmpv3);
#ifdef NORMALCALCULATIONDEBUGMODE
					CHECKLENGTHZERO
#endif
					auto tmpv = glm::normalize(tmpv1);
#ifdef NORMALCALCULATIONDEBUGMODE
					NORMALCALCULATIONDEBUGPRINT
#endif
					nv += tmpv;
					tmpv3 = tmpv2;
					tmpv2 = glm::vec3(1.0f, 0.0f, buffer[i  ][j+1][2] - buffer[i][j][2]);
					tmpv1 = glm::cross(tmpv2, tmpv3);
#ifdef NORMALCALCULATIONDEBUGMODE
					CHECKLENGTHZERO
#endif
					tmpv = glm::normalize(tmpv1);
#ifdef NORMALCALCULATIONDEBUGMODE
				NORMALCALCULATIONDEBUGPRINT
#endif
					nv += tmpv;
				}
			}
			if(i < endRow - 1)
			{
				if(j < width - 1)
				{
					auto tmpv2 = glm::vec3(1.0f,-1.0f, buffer[i+1][j+1][2] - buffer[i][j][2]);
					auto tmpv3 = glm::vec3(1.0f, 0.0f, buffer[i  ][j+1][2] - buffer[i][j][2]);
					auto tmpv1 = glm::cross(tmpv2, tmpv3);
#ifdef NORMALCALCULATIONDEBUGMODE
					CHECKLENGTHZERO
#endif
					auto tmpv = glm::normalize(tmpv1);
#ifdef NORMALCALCULATIONDEBUGMODE
					NORMALCALCULATIONDEBUGPRINT
#endif
					nv += tmpv;
					tmpv3 = tmpv2;
					tmpv2 = glm::vec3(0.0f,-1.0f, buffer[i+1][j][2] - buffer[i][j][2]);
					tmpv1 = glm::cross(tmpv2, tmpv3);
#ifdef NORMALCALCULATIONDEBUGMODE
					CHECKLENGTHZERO
#endif
					tmpv = glm::normalize(tmpv1);
#ifdef NORMALCALCULATIONDEBUGMODE
					NORMALCALCULATIONDEBUGPRINT
#endif
					nv += tmpv;
				}
				if(j > 0)
				{
					auto tmpv2 = glm::vec3(-1.0f,-1.0f, buffer[i+1][j-1][2] - buffer[i][j][2]);
					auto tmpv3 = glm::vec3( 0.0f,-1.0f, buffer[i+1][j  ][2] - buffer[i][j][2]);
					auto tmpv1 = glm::cross(tmpv2, tmpv3);
#ifdef NORMALCALCULATIONDEBUGMODE
					CHECKLENGTHZERO
#endif
					auto tmpv = glm::normalize(tmpv1);
#ifdef NORMALCALCULATIONDEBUGMODE
					NORMALCALCULATIONDEBUGPRINT
#endif
					nv += tmpv;
					tmpv3 = tmpv2;
					tmpv2 = glm::vec3(-1.0f, 0.0f, buffer[i][j-1][2] - buffer[i][j][2]);
					tmpv1 = glm::cross(tmpv2, tmpv3);
#ifdef NORMALCALCULATIONDEBUGMODE
					CHECKLENGTHZERO
#endif
					tmpv = glm::normalize(tmpv1);
#ifdef NORMALCALCULATIONDEBUGMODE
					NORMALCALCULATIONDEBUGPRINT
#endif
					nv += tmpv;
				}
			}
			nv = glm::normalize(nv);
			buffer[i][j][3] = nv.x;
			buffer[i][j][4] = nv.y;
			buffer[i][j][5] = nv.z;
		}
	}
}
