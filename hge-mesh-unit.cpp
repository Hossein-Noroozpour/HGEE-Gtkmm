#include "hge-mesh-unit.hpp"
#include <iostream>
#define HGEPRINTCODELINE std::cout << "Debugging: file:" << __FILE__ << " line:" << __LINE__ << std::endl << std::flush;
hge::render::MeshUnit::MeshUnit()
{}
hge::render::MeshUnit::MeshUnit(
		const GLfloat* const& vertices,
		const GLuint* const& indices,
		const GLuint& verticesByteSize,
		const GLuint& verticesNumber,
		const GLuint& indicesByteSize):
		vboSize(verticesByteSize),
		vboElementsNumber(verticesNumber),
		iboSize(indicesByteSize),
		numberOfIndices((iboSize)/(sizeof(GLuint)))
{
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
	glGenBuffers(1, &vbo);
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
	glBufferData(GL_ARRAY_BUFFER, verticesByteSize, vertices, GL_STATIC_DRAW);
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
	glGenBuffers(1, &ibo);
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, indices, GL_STATIC_DRAW);
#ifdef HGEMESHDEBUG
	for(unsigned int i = 0; i < verticesByteSize / sizeof(GLfloat); i++)
		std::cout << i << ":" << vertices[i] << "  ";
	std::cout << "vbo: " << vbo << "  ibo: " << ibo << "  vboSize: " << vboSize
			<< "  vboElementsNumber: " << vboElementsNumber << " iboSize: "
			<< iboSize << " numberOfIndices: " << numberOfIndices << std::endl << std::endl << std::flush;
#endif
	delete [] vertices;
	delete [] indices;
}
hge::render::MeshUnit::~MeshUnit()
{///\todo There is some problem in here, solve it as soon as possible.
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo);
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ibo);
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif

}
void
hge::render::MeshUnit::bindVBO()
{
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
}
void
hge::render::MeshUnit::bindIBO()
{
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
}
void
hge::render::MeshUnit::bindTotal()
{
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
}
void
hge::render::MeshUnit::draw()
{
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
	glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, 0);
#ifdef HGEOPENGLDEBUGMESH
	hge::ui::HGEGLFWWindow::printOpenGLErrorAndTerminate();
#endif
}
GLuint
hge::render::MeshUnit::getVBO()
{
	return vbo;
}
GLuint
hge::render::MeshUnit::getIBO()
{
	return ibo;
}
