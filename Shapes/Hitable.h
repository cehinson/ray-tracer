#pragma once

#include "Core/Vec3.h"
#include "Core/Ray.h"

namespace ch
{

class Material; // forward declaration

struct hit_record
{
	float t = 0.0f; // parameter t at which Ray A + tB hit
	Vec3<> p;		// p = A + tB
	Vec3<> normal;  // nommal to the surface p is on for shading
	Material *material_ptr = nullptr;
};

class Hitable
{
  public:
	virtual std::pair<bool, hit_record> hit_2(const Ray&r, float t_min, float t_max) const = 0; // replacement for hit
	virtual bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const = 0;
	virtual ~Hitable() noexcept {}
};

} // namespace ch
