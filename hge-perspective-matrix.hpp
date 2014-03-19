#ifndef HGEPERSPECTIVEMATRIX_HPP
#define	HGEPERSPECTIVEMATRIX_HPP
#include "hge-math.hpp"
namespace hge
{
	namespace math
	{
		class PerspectiveMatrix
		{
		private:
			glm::mat4 persM;
		public:
			PerspectiveMatrix();
			~PerspectiveMatrix();
			const glm::mat4 &getMatrix();
		};
	}
}
#endif
