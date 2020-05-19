#pragma once

#include "ray.h"
#include "hit.h"
#include "material.h"
#include "matrix.h"


//Object3D
class Object3D {
public:
	Material* material;
	Object3D(): material(nullptr){}
	virtual ~Object3D(){}
	virtual bool intersect(const Ray& r, Hit& h, float tmin) = 0;
	virtual void paint() const = 0;//»æÖÆº¯Êý,A3Ìí¼Ó
};

//Sphere
class Sphere :public Object3D {
public:
	Vec3f center;
	float radius;
	Sphere(const Vec3f c, float r, Material* m) :center(c), radius(r) {
		material = m;
	}
	~Sphere() override {}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
	virtual void paint() const;
};

//Plane
class Plane :public Object3D {
public:
	Vec3f normal;
	float distance;
	Plane(const Vec3f& n, float d, Material* m) :normal(n), distance(d) {
		material = m;
		normal.Normalize();
	}
	~Plane() override {}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
	virtual void paint() const;
};

//Triangle
class Triangle :public Object3D {
public:
	Vec3f a, b, c;
	Vec3f normal;
	Triangle(const Vec3f& a, const Vec3f& b, const Vec3f& c, Material* m) :a(a), b(b), c(c) {
		material = m;
		Vec3f::Cross3(normal, b - a, c - a);
		normal.Normalize();
	}
	~Triangle() override {}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
	virtual void paint() const;
};

//Transform
class Transform :public Object3D {
public:
	Matrix matrix;
	Object3D* object;
	Transform(const Matrix &m,Object3D *o):matrix(m),object(o){}
	~Transform() override {}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
	virtual void paint() const;
};

//Group
class Group :public Object3D {
public:
	int num_objects;
	Object3D** objects;
	Group(int n) :num_objects(n){
		objects = new Object3D * [num_objects];
	}
	~Group() override {
		for (int i = 0; i < num_objects; ++i) {
			delete objects[i];
		}
		delete[] objects;
	}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
	void addObject(int index, Object3D* obj);
	virtual void paint() const;
};










