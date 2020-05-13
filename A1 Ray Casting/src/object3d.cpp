#include "object3d.h"

//Sphere
//Algebraic�����÷�������
bool Sphere::intersect(const Ray& r, Hit& h, float tmin) {
	bool flag = false;//�н��㷵��true
	Vec3f ro = r.getOrigin() - center;//ro:���ߵ������ĵ�����
	Vec3f rd = r.getDirection();//���߷���
	float a = rd.Dot3(rd);//rd��rd���
	float b = 2 * ro.Dot3(rd);//ro��rd���,����Ϊ��
	float c = ro.Dot3(ro) - radius * radius;
	float delta = b * b - 4 * a * c;
	
	//float t;//��ǰ����,�˴����Բ���
	//��ȡ����Ľ���
	if (delta >= 0) {
		float d = sqrt(delta);//һ��Ϊ��
		float t1 = (-b - d) / (2 * a);//ͨ��t1��С
		float t2 = (-b + d) / (2 * a);
		// For an orthographic camera, rays always start at infinity, so tmin will be a large negative value
		//���ڱ�����ҵ��������������������tminΪ��������������������Բ���
		//if (t1 >= tmin) {//��origin֮ǰ
		//	t = t1;
		//}
		//else if (t2 >= tmin) {
		//	t = t2;
		//}
		if (t1 < h.getT()) {//closer��ǰ���㣬����
			h.set(t1, material, r);
			flag = true;
		}
	}
	return flag;
}

//Geometric
//bool Sphere::intersect(const Ray& r, Hit& h, float tmin) {
//	Vec3f ro = r.getOrigin() - center;
//	Vec3f rd = r.getDirection();
//	float tp = -ro.Dot3(rd);
//	float d2 = ro.Dot3(ro) - tp * tp;
//	if (d2 > radius* radius) {
//		return false;
//	}
//	float tt = sqrt(radius * radius - d2);
//	float t1 = tp - tt;//out
//	float t2 = tp + tt;//in
//	float t = t1;
//	if (t > tmin&& t < h.getT()) {
//		h.set(t, material, r);
//		return true;
//	}
//	return false;
//}

//Group
bool Group::intersect(const Ray& r, Hit& h, float tmin) {
	bool flag = false;
	for (int i = 0; i < num_objects; ++i) {
		if (objects[i]->intersect(r, h, tmin)) {
			flag = true;
		}
	}
	return flag;
}

void Group::addObject(int index, Object3D* obj) {
	objects[index] = obj;
}






















