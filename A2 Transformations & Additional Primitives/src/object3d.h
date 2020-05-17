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
	virtual ~Object3D() {}//����������
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
	Plane(Vec3f& n, float d, Material* m) :normal(n), distance(d) {//��ʼ������
		material = m;
		normal.Normalize();
	}
	~Plane() override{}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
};

//Triangle
class Triangle :public Object3D {
public:
	Vec3f a;//����������
	Vec3f b;
	Vec3f c;
	Vec3f normal;
	Triangle(Vec3f& a, Vec3f& b, Vec3f& c, Material* m) :a(a), b(b), c(c) {
		material = m;
		Vec3f::Cross3(normal, b - a, c - a);//b-a���ab������c-a���ac����
		normal.Normalize();
	}
	~Triangle() override{}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
};

//Transform
class Transform :public Object3D {
public:
	Matrix matrix;//�任����-ƽ�ơ���������ת
	Object3D* object;//�任����
	Transform(Matrix &m,Object3D *o):matrix(m),object(o){}
	~Transform() override {}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
};

//Group
class Group :public Object3D {
public:
	int num_objects;
	Object3D** objects;//ָ��һ��ָ������
	Group(int n) :num_objects(n) {
		objects = new Object3D * [num_objects];//����Object3D��ָ������
	}
	~Group() override {//��д�������ͷ�ָ������
		for (int i=0;i<num_objects;++i){
			delete objects[i];
		}
		delete[] objects;
	}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
	void addObject(int index, Object3D* obj);
};