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
	Vec3f center;
	Vec3f direction;
	Vec3f up;
	Vec3f horizontal;
	float size;
	OrthographicCamera(Vec3f c, Vec3f d, Vec3f u, float s) :center(c), direction(d), up(u), size(s) {
		direction.Normalize();//标准化
		//the horizontal vector of the image plane, is deduced from the direction and the up vector 
		Vec3f::Cross3(horizontal, direction, up);//叉乘
		//The input up vector might not be a unit vector or perpendicular to the direction. It must be modified to be orthonormal to the direction.
		Vec3f::Cross3(up, horizontal, direction);//叉乘
		horizontal.Normalize();//标准化
		up.Normalize();//标准化
	}
	~OrthographicCamera() override{}

	//The generateRay() method is used to generate rays for each screen-space coordinate, described as a Vec2f
	Ray generateRay(Vec2f point) override;

	//The getTMin() method will be useful when tracing rays through the scene
	float getTMin() const override;
};