#pragma once
#include "ray.h"
class Camera {
public:
	Camera() {}
	virtual ~Camera() {}
	virtual Ray generateRay(const Vec2f& point) const = 0;//常纯虚函数
	virtual float getTMin() const = 0;
	virtual void glInit(int w, int h) = 0;//纯虚函数
	virtual void glPlaceCamera(void) = 0;
	virtual void dollyCamera(float dist) = 0;
	virtual void truckCamera(float dx, float dy) = 0;
	virtual void rotateCamera(float rx, float ry) = 0;
};

//OrthographicCamera
class OrthographicCamera :public Camera {
public:
	Vec3f center;
	Vec3f direction;
	Vec3f up;
	Vec3f horizontal;
	Vec3f screenUp;
	float size;
	OrthographicCamera(const Vec3f& c, const  Vec3f& d, const Vec3f& u, float s) :center(c), direction(d), up(u), size(s) {//常引用，通过这种方式，能够达到对引用的目标的值不能修改，从而使引用的目标成为const
		direction.Normalize();
		Vec3f::Cross3(horizontal, direction, up);
		Vec3f::Cross3(screenUp, horizontal, direction);
		horizontal.Normalize();
		screenUp.Normalize();
	}
	virtual Ray generateRay(const Vec2f& point) const;
	virtual float getTMin() const;
	virtual void glInit(int w, int h);
	virtual void glPlaceCamera(void);
	virtual void dollyCamera(float dist);
	virtual void truckCamera(float dx, float dy);
	virtual void rotateCamera(float rx, float ry);
};

//PerspectiveCamera
class PerspectiveCamera :public Camera {
public:
	Vec3f center;
	Vec3f direction;
	Vec3f up;
	Vec3f horizontal;
	Vec3f screenUp;
	float angle;
	PerspectiveCamera(const Vec3f& c, const Vec3f& d, const Vec3f& u, float a) :center(c), direction(d), up(u), angle(a) {
		direction.Normalize();
		Vec3f::Cross3(horizontal, direction, up);
		Vec3f::Cross3(screenUp, horizontal, direction);
		horizontal.Normalize();
		screenUp.Normalize();
	}
	virtual Ray generateRay(const Vec2f& point) const;
	virtual float getTMin() const;
	virtual void glInit(int w, int h);
	virtual void glPlaceCamera();
	virtual void dollyCamera(float dist);
	virtual void truckCamera(float dx, float dy);
	virtual void rotateCamera(float rx, float ry);
};