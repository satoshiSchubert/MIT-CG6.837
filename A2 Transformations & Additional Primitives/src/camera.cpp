#include "camera.h"
//OrthographicCamera
Ray OrthographicCamera::generateRay(Vec2f point) {
	Vec3f ro = center + (point.x() - 0.5) * horizontal * size + (point.y() - 0.5) * up * size;//���߳�ʼλ��
	return Ray(ro, direction);
}
float OrthographicCamera::getTMin() const {
	return -INFINITY;//��������������κν��㶼�����ӵ�֮ǰ�����Ϊ��ֵ
}

//PerspectiveCamera
Ray PerspectiveCamera::generateRay(Vec2f point) {
	float d = 0.5 / tan(angle / 2);	//angle���� scene_parser.C�д���Ϊ����ֵ
	Vec3f v = d * direction + (point.x() - 0.5) * horizontal + (point.y() - 0.5) * up;
	v.Normalize();
	return Ray(center, v);
}
float PerspectiveCamera::getTMin() const {
	return 0;//����͸�������tmin��СֵӦ��һ����ֵ��������Ϊ0
}