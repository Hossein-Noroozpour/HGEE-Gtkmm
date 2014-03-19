#include "hge-vertex-data.hpp"
#include <iostream>
bool
hge::core::VertexData::Compare::operator()
(const VertexData& v1, const VertexData& v2)
{
	if(v1.px > v2.px)
	{
		return true;
	}
	if(v1.px < v2.px)
	{
		return false;
	}
	if(v1.py > v2.py)
	{
		return true;
	}
	if(v1.py < v2.py)
	{
		return false;
	}
	if(v1.pz > v2.pz)
	{
		return true;
	}
	if(v1.pz < v2.pz)
	{
		return false;
	}
	if(v1.nx > v2.nx)
	{
		return true;
	}
	if(v1.nx < v2.nx)
	{
		return false;
	}
	if(v1.ny > v2.ny)
	{
		return true;
	}
	if(v1.ny < v2.ny)
	{
		return false;
	}
	if(v1.nz > v2.nz)
	{
		return true;
	}
	if(v1.nz < v2.nz)
	{
		return false;
	}
	if(v1.ux > v2.ux)
	{
		return true;
	}
	if(v1.ux < v2.ux)
	{
		return false;
	}
	if(v1.uy > v2.uy)
	{
		return true;
	}
	return false;
}
void hge::core::VertexData::print()
{
	std::cout << "Position:(" << this->px << " , " << this->py << " , " << this->pz << ")  Normal:("
			<< this->nx << " , " << this->ny << " , " << this->nz << ")  UV:("
			<< this->ux << " , " << this->uy << ")  Indices: ";
	for(auto i: this->indices)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}
bool hge::core::VertexData::isEqual(const VertexData& v)
{
	return (this->px == v.px) &&
			(this->py == v.py) &&
			(this->pz == v.pz) &&
			(this->nx == v.nx) &&
			(this->ny == v.ny) &&
			(this->nz == v.nz) &&
			(this->ux == v.ux) &&
			(this->uy == v.uy);
}