#include "object3d.h"

//Sphere
//Algebraic——该方法常用
bool Sphere::intersect(const Ray& r, Hit& h, float tmin) {
	bool flag = false;//有交点返回true
	Vec3f ro = r.getOrigin() - center;//ro:射线到球中心的向量
	Vec3f rd = r.getDirection();//射线方向
	float a = rd.Dot3(rd);//rd与rd点积
	float b = 2 * ro.Dot3(rd);//ro与rd点积,可能为负
	float c = ro.Dot3(ro) - radius * radius;
	float delta = b * b - 4 * a * c;
	
	//float t;//当前距离,此处可以不用
	//获取最近的交点
	if (delta >= 0) {
		float d = sqrt(delta);//一定为正
		float t1 = (-b - d) / (2 * a);//通常t1更小
		float t2 = (-b + d) / (2 * a);
		// For an orthographic camera, rays always start at infinity, so tmin will be a large negative value
		//由于本节作业是正交相机，正交相机的tmin为无穷大，因此下面这块代码可以不用
		//if (t1 >= tmin) {//在origin之前
		//	t = t1;
		//}
		//else if (t2 >= tmin) {
		//	t = t2;
		//}
		if (t1 < h.getT()) {//closer当前交点，更新
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






















