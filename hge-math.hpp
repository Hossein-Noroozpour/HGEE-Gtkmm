#ifndef HGEMATH_HPP
#define HGEMATH_HPP
//GLM////////////////////////////////////////////////
//#define GLM_FORCE_CXX11             // C++ 11
//#define GLM_PRECISION_MEDIUMP_INT
//#define GLM_PRECISION_HIGHP_FLOAT
#define GLM_SWIZZLE
//#define GLM_MESSAGES
//#define GLM_FORCE_INLINE
#define GLM_FORCE_SSE2
//#define GLM_FORCE_AVX
#define GLM_FORCE_RADIANS           // Using radians
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
//GLM///////////////////////////////////////////////
namespace hge
{
	namespace math
	{
		class Math
		{
		public:
			const static glm::mat4 mat4Idn;
			const static glm::vec3 globalX;
			const static glm::vec3 globalY;
			const static glm::vec3 globalZ;
			const static glm::vec3 worldOrigin;
		};
	}
}
#endif // MATH_H
