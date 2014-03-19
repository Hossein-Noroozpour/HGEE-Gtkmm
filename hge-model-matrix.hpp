#ifndef HGEMODELMATRIX_HPP
#define HGEMODELMATRIX_HPP
#include "./hge-math.hpp"
namespace hge
{
	namespace math
	{
		class ModelMatrix
		{
		public:
			//vectors
			glm::vec3 objDirX;//object local directionX
			glm::vec3 objDirY;//object local directionY
			glm::vec3 objDirZ;//object local directionZ
			glm::vec3 objLoct;//object location
			//matrices
			glm::mat4 modelM;//model       matrix
			//glm::mat4 transM;//translation matrix
			glm::mat4 rotscM;//rotation    matrix
			//glm::mat4 scaleM;scalation   matrix
			//dirty flags false means do not update
			//bool modelDF;
			//bool transDF;
			//bool rotatDF;
			//bool scaleDF;
		public:
			ModelMatrix(const glm::vec3 &object_directionX,
					const glm::vec3 &object_directionY,
					const glm::vec3 &object_directionZ,
					const glm::vec3 &object_location);
			ModelMatrix(const glm::vec3 &object_directionX,
					const glm::vec3 &object_directionY,
					const glm::vec3 &object_location);
			ModelMatrix(const glm::vec3 &object_location);
			ModelMatrix();
			void translate(const glm::vec3 &trn);
			float *getModelMatrixValue(void);
		};
	}
}
#endif // HGEMODELMATRIX_HPP
