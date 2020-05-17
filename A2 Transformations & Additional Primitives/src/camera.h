#pragma once
#include "ray.h"
class Camera {
public:
	Camera() {}
	virtual ~Camera() {}
	virtual Ray generateRay(Vec2f point) = 0;
	virtual float getTMin() const = 0;
};

//OrthographicCamera
class OrthographicCamera : public Camera {
public:
	OrthographicCamera(Vec3f c, Vec3f d, Vec3f u, float s) :center(c), direction(d), up(u), size(s) {
		direction.Normalize();
		Vec3f::Cross3(horizontal, direction, up);
		Vec3f::Cross3(up, horizontal, direction);
		horizontal.Normalize();
		up.Normalize();
	}
	~OrthographicCamera() override{}
	Ray generateRay(Vec2f point) override;
	float getTMin() const override;


	Vec3f center;
	Vec3f direction;
	Vec3f up;
	Vec3f horizontal;
	float size;
};

//PerspectiveCamera
class PerspectiveCamera :public Camera {
public:
	Vec3f center;//相机位置
	Vec3f direction;//方向向量
	Vec3f up;//上向量
	Vec3f horizontal;//水平向量
	float angle;//角度
	PerspectiveCamera(Vec3f& c, Vec3f& d, Vec3f& u, float a) :center(c), direction(d), up(u), angle(a) {
		direction.Normalize();
		Vec3f::Cross3(horizontal, direction, up);
		Vec3f::Cross3(up, horizontal, direction);
		horizontal.Normalize();
		up.Normalize();
	}
	~PerspectiveCamera() override{}
	Ray generateRay(Vec2f point) override;
	float getTMin() const override;
};