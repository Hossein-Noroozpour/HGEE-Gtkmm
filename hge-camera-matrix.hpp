#ifndef HGECAMERAMATRIX_HPP
#define HGECAMERAMATRIX_HPP
#include "hge-math.hpp"
namespace hge
{
	namespace math
	{
		class CameraMatrix
		{
		private:
			glm::vec3 cmrX;
			glm::vec3 cmrY;
			glm::vec3 cmrZ;

			glm::vec3 cmrLoc;//Location

			glm::mat4 viewM;
			glm::mat4 rotsclM;
		public:
			CameraMatrix();
			~CameraMatrix();
			void translate(const glm::vec3 &vec);
			void move(const glm::vec3 &vec);
			void rotateLocalX(const float &rad);
			void rotateLocalY(const float &rad);
			void rotateLocalZ(const float &rad);
			void rotateLocal(const float &rad, const glm::vec3 &vec);
			void rotateGlobalX(const float &rad);
			void rotateGlobalY(const float &rad);
			void rotateGlobalZ(const float &rad);
			void rotateTotal(const float &rad, const glm::vec3 &vec);
			void rotate(const float &rad, const glm::vec3 &vec);
			void scaleX(const float &x);
			void scaleY(const float &y);
			void scaleZ(const float &z);
			void scale(const float &x, const float &y, const float &z);
			const glm::mat4 &getMatrix();
			void moveForward (const float &spd);
			void moveSideward(const float &spd);
		};
	}
}
#endif
