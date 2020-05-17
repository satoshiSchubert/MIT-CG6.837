#pragma once
#include "ray.h"
#include "hit.h"
#include "material.h"
#include "matrix.h"

//Object3D
class Object3D {
public:
	Material* material;
	Object3D() : material(nullptr) {}
	virtual ~Object3D() {}//虚析构函数
	virtual bool intersect(const Ray& r, Hit& h, float tmin) = 0;
};

//Sphere
class Sphere :public Object3D {
public:
	Vec3f center;
	float radius;
	Sphere(Vec3f c, float r, Material* m) :center(c), radius(r) {
		material = m;
	}
	~Sphere() override {}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
};

//Plane
class Plane :public Object3D {
public:
	Vec3f normal;
	float distance;
	Plane(Vec3f& n, float d, Material* m) :normal(n), distance(d) {//初始化法向
		material = m;
		normal.Normalize();
	}
	~Plane() override{}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
};

//Triangle
class Triangle :public Object3D {
public:
	Vec3f a;//三角形三点
	Vec3f b;
	Vec3f c;
	Vec3f normal;
	Triangle(Vec3f& a, Vec3f& b, Vec3f& c, Material* m) :a(a), b(b), c(c) {
		material = m;
		Vec3f::Cross3(normal, b - a, c - a);//b-a获得ab向量，c-a获得ac向量
		normal.Normalize();
	}
	~Triangle() override{}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
};

//Transform
class Transform :public Object3D {
public:
	Matrix matrix;//变换矩阵-平移、放缩、旋转
	Object3D* object;//变换对象
	Transform(Matrix &m,Object3D *o):matrix(m),object(o){}
	~Transform() override {}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
};

//Group
class Group :public Object3D {
public:
	int num_objects;
	Object3D** objects;//指向一个指针数组
	Group(int n) :num_objects(n) {
		objects = new Object3D * [num_objects];//创建Object3D的指针数组
	}
	~Group() override {//重写析构，释放指针数组
		for (int i=0;i<num_objects;++i){
			delete objects[i];
		}
		delete[] objects;
	}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
	void addObject(int index, Object3D* obj);
};