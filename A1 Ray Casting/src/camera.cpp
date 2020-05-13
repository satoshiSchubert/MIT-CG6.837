#include "camera.h"
//OrthographicCamera
Ray OrthographicCamera::generateRay(Vec2f point) {
	Vec3f ro = center + (point.x() - 0.5) * horizontal * size + (point.y() - 0.5) * up * size;//…‰œﬂ∑ΩœÚ
	return Ray(ro, direction);
}

//For an orthographic camera, rays always start at infinity, so tmin will be a large negative value
float OrthographicCamera::getTMin() const {
	return -INFINITY;
}