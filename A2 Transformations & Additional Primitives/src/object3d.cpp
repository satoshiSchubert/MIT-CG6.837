#include "object3d.h"
#include <fstream>
#include <algorithm>

//copy from Matrix.C

float det2(float a, float b,
	float c, float d) {
	return a * d - b * c;
}

float det3(float a1, float a2, float a3,
	float b1, float b2, float b3,
	float c1, float c2, float c3) {
	return
		a1 * det2(b2, b3, c2, c3)
		- b1 * det2(a2, a3, c2, c3)
		+ c1 * det2(a2, a3, b2, b3);
}

//Sphere
//Algebraic
bool Sphere::intersect(const Ray& r, Hit& h, float tmin) {
	Vec3f ro = r.getOrigin() - center;
	Vec3f rd = r.getDirection();
	float a = rd.Dot3(rd);
	float b = 2 * ro.Dot3(rd);
	float c = ro.Dot3(ro) - radius * radius;
	float delta = b * b - 4 * a * c;
	float t = INFINITY;
	bool flag = false;
	if (delta>=0) {
		float d = sqrt(delta);
		float t1 = (-b - d) / (2 * a);
		float t2 = (-b + d) / (2 * a);
		if (t1>=tmin){
			t = t1;
			flag = true;
		}
		if (t2 >= tmin) {
			if (flag) {
				t = min(t1, t2);
			}
			else {
				t = t2;
			}
		}
		if (t<h.getT()) {
			Vec3f normal = ro + t * rd;//将射线方程作为法向？？？
			normal.Normalize();
			h.set(t, material, normal, r);
			return true;
		}
	}
	return false;
}



//Plane
bool Plane::intersect(const Ray& r, Hit& h, float tmin) {
	Vec3f ro = r.getOrigin();
	Vec3f rd = r.getDirection();
	float denom = normal.Dot3(rd);//计算分母项
	if (denom == 0) return false;//分母不能为0
	float t = (distance - normal.Dot3(ro)) / denom;
	if (t > tmin&& t < h.getT()) {
		h.set(t, material, normal, r);
		return true;
	}
	return false;
}

//Triangle
//实现原理，参见PPT-Ray Casting||
bool Triangle::intersect(const Ray& r, Hit& h, float tmin) {
	Vec3f ro = r.getOrigin();//射线起点
	Vec3f rd = r.getDirection();//射线方向
	float abx = a.x() - b.x();
	float aby = a.y() - b.y();
	float abz = a.z() - b.z();
	float acx = a.x() - c.x();
	float acy = a.y() - c.y();
	float acz = a.z() - c.z();
	float aox = a.x() - ro.x();
	float aoy = a.y() - ro.y();
	float aoz = a.z() - ro.z();

	float A = det3(abx, acx, rd.x(), aby, acy, rd.y(), abz, acz, rd.z());//|A|
	float beta = det3(aox, acx, rd.x(), aoy, acy, rd.y(), aoz, acz, rd.z()) / A;
	float gamma = det3(abx, aox, rd.x(), aby, aoy, rd.y(), abz, aoz, rd.z()) / A;
	if (beta > 0 && gamma > 0 && (beta + gamma) < 1) {
		float t = det3(abx, acx, aox, aby, acy, aoy, abz, acz, aoz) / A;
		if (t > tmin&& t < h.getT()) {
			h.set(t, material, normal, r);
			return true;
		}
	}
	return false;
}

//Transform
//下面的很多细节不是很懂???
bool Transform::intersect(const Ray& r, Hit& h, float tmin) {
	Vec3f ro = r.getOrigin();
	Vec3f rd = r.getDirection();
	Matrix invM = matrix;
	if (invM.Inverse()) {
		invM.Transform(ro);//射线起点变换  为什么变换的是射线起点和方向呢？
		invM.TransformDirection(rd);//射线方向变换
		Ray invR(ro, rd);//生成新的射线，再将新的射线和对象求交点
		if (object->intersect(invR, h, tmin)) {
			Vec3f normal = h.getNormal();
			Matrix invMT = invM;
			invMT.Transpose();//转置
			invMT.TransformDirection(normal);//trans normal to world space
			normal.Normalize();
			h.set(h.getT(), h.getMaterial(), normal, r);
			return true;
		}
	}
	return false;
}

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






