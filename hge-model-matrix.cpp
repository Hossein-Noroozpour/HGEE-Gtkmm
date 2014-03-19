#include "hge-model-matrix.hpp"
using namespace hge::math;
ModelMatrix::ModelMatrix
(const glm::vec3 &object_directionX,
 const glm::vec3 &object_directionY,
 const glm::vec3 &object_directionZ,
 const glm::vec3 &object_location):
	objDirX(object_directionX),
	objDirY(object_directionY),
	objDirZ(object_directionZ),
	objLoct(object_location),
	//transM(glm::translate(glm::mat4(1.0f), object_location)),
	rotscM(glm::mat4(1.0f)),
	//scaleM(glm::mat4(1.0f)),
	modelM(glm::translate(glm::mat4(1.0f), object_location))//,
	//transDF(false),
	//rotatDF(false),
	//scaleDF(false),
	//modelDF(false)
{
}
ModelMatrix::ModelMatrix
(const glm::vec3 &object_directionX,
 const glm::vec3 &object_directionY,
 const glm::vec3 &object_location):
	objDirX(object_directionX),
	objDirY(object_directionY),
	objDirZ(glm::cross(object_directionX, object_directionY)),
	objLoct(object_location),
	//transM(glm::translate(glm::mat4(1.0f), object_location)),
	rotscM(glm::mat4(1.0f)),
	//scaleM(glm::mat4(1.0f)),
	modelM(glm::translate(glm::mat4(1.0f), object_location))//,
	//transDF(false),
	//rotatDF(false),
	//scaleDF(false),
	//modelDF(false)
{
}
ModelMatrix::ModelMatrix
(const glm::vec3 &object_location):
	objDirX(glm::vec3(1.0f, 0.0f, 0.0f)),
	objDirY(glm::vec3(0.0f, 1.0f, 0.0f)),
	objDirZ(glm::vec3(0.0f, 0.0f, 1.0f)),
	objLoct(object_location),
	//transM(glm::translate(glm::mat4(1.0f), object_location)),
	rotscM(glm::mat4(1.0f)),
	//scaleM(glm::mat4(1.0f)),
	modelM(glm::translate(glm::mat4(1.0f), object_location))//,
	//transDF(false),
	//rotatDF(false),
	//scaleDF(false),
	//modelDF(false)
{
}
ModelMatrix::ModelMatrix ():
	objDirX(glm::vec3(1.0f, 0.0f, 0.0f)),
	objDirY(glm::vec3(0.0f, 1.0f, 0.0f)),
	objDirZ(glm::vec3(0.0f, 0.0f, 1.0f)),
	objLoct(glm::vec3(0.0f, 0.0f, 0.0f)),
	//transM(glm::mat4(1.0f)),
	rotscM(glm::mat4(1.0f)),
	//scaleM(glm::mat4(1.0f)),
	modelM(glm::mat4(1.0f))//,
	//transDF(false),
	//rotatDF(false),
	//scaleDF(false),
	//modelDF(false)
{
}
void
ModelMatrix::translate (const glm::vec3 &trn)
{
	objLoct += trn;
	modelM = glm::translate(modelM, trn);
}
float *ModelMatrix::getModelMatrixValue(void)
{
	return &(modelM[0][0]);
}
