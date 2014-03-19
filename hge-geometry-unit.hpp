#ifndef HGEGEOMETRYUNIT_HPP
#define	HGEGEOMETRYUNIT_HPP
#include <string>
#include "hge-mesh-unit.hpp"
#include "hge-model-matrix.hpp"
#include "hge-shader-unit.hpp"
#include "hge-texture-unit.hpp"
//#define HGEGEOMETRYDEBUGMVPVALUECHECK
#define HGEGEOMETRYNUMBEROFQUERIES 1
#define HGEGEOMETRYOCCLUSIONQUERYID 0
namespace hge
{
	namespace render
	{
		class GeometryUnit
		{
		public:
			GeometryUnit(
					const std::string& id,
					const std::string& name);
			~GeometryUnit();
			void setMesh(const std::shared_ptr<MeshUnit>& m);
			void setOcclusionQueryMesh(const std::shared_ptr<MeshUnit>& m);
			void draw();
			void occlusionQuery(const glm::mat4& vp);
			bool isThisYourID(const std::string& idstr);
			void setShader(const std::shared_ptr<shader::ShaderUnit>& shader);
			void setOcclusionQueryShader(const std::shared_ptr<shader::ShaderUnit>& shader);
			void setTexture(const std::shared_ptr<texture::TextureUnit>& texture);
			math::ModelMatrix* getModelMatrix();
			std::shared_ptr<MeshUnit> getMesh();
		private:
			GLuint queries[HGEGEOMETRYNUMBEROFQUERIES];
			std::string id;
			std::string name;
			glm::mat4 mvp;
			math::ModelMatrix modelMatrix;
			std::shared_ptr<MeshUnit> mesh;
			std::shared_ptr<MeshUnit> occlusionQueryMesh;
			std::shared_ptr<shader::ShaderUnit> shader;
			std::shared_ptr<shader::ShaderUnit> occlusionQueryShader;
			std::shared_ptr<texture::TextureUnit> texture;
		};
	}
}
#endif
