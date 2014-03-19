#include "hge-perspective-matrix.hpp"
hge::math::PerspectiveMatrix::PerspectiveMatrix():
	persM(glm::perspective(50.0f, 1.778645833f, 0.5f, 9000000000000000000000.0f))
{
}
hge::math::PerspectiveMatrix::~PerspectiveMatrix()
{
}
const glm::mat4 &hge::math::PerspectiveMatrix::getMatrix()
{
	return persM;
}
