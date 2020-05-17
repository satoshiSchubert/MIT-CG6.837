#include "camera.h"
//OrthographicCamera
Ray OrthographicCamera::generateRay(Vec2f point) {
	Vec3f ro = center + (point.x() - 0.5) * horizontal * size + (point.y() - 0.5) * up * size;//射线初始位置
	return Ray(ro, direction);
}
float OrthographicCamera::getTMin() const {
	return -INFINITY;//对于正交相机，任何交点都将在视点之前，因此为该值
}

//PerspectiveCamera
Ray PerspectiveCamera::generateRay(Vec2f point) {
	float d = 0.5 / tan(angle / 2);	//angle已在 scene_parser.C中处理为弧度值
	Vec3f v = d * direction + (point.x() - 0.5) * horizontal + (point.y() - 0.5) * up;
	v.Normalize();
	return Ray(center, v);
}
float PerspectiveCamera::getTMin() const {
	return 0;//对于透视相机，tmin最小值应有一个初值，这里设为0
}