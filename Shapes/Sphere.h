#pragma once

#include "Hitable.h"
#include "Materials/Material.h"

namespace ch
{

class Sphere : public Hitable
{
	Vec3<> center;
	float radius;
	std::unique_ptr<Material> mat_ptr;

  public:
	Sphere() = delete;
	Sphere(const Sphere &) = delete;
	Sphere(Vec3<> cen, float r, std::unique_ptr<Material> mat);

	// Inherited via Hitable
	std::pair<bool, hit_record> hit_2(const Ray &r, float t_min, float t_max) const override;
	bool hit(const Ray &r, float t_min, float t_max, hit_record &rec) const override;
};

} // namespace ch
