#include "ray.h"
#include "hit.h"
#include "material.h"
class Object3D {
public:
	Material* material;
	Object3D(): material(nullptr){}
	virtual ~Object3D(){}
	virtual bool intersect(const Ray& r, Hit& h, float tmin) = 0;
};

//Sphere
class Sphere : public Object3D {
public:
	Vec3f center;
	float radius;
	Sphere(Vec3f c, float r, Material* m) : center(c), radius(r) {
		material = m;
	}
	~Sphere() override{}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
};
//Group
class Group :public Object3D {
public:
	int num_objects;
	Object3D** objects;
	Group(int n) :num_objects(n) {
		objects = new Object3D * [num_objects];
	}
	~Group() override {
		for (int i = 0; i < num_objects;++i) {
			delete objects[i];
		}
		delete[] objects;
	}
	bool intersect(const Ray& r, Hit& h, float tmin) override;
	void addObject(int index, Object3D* obj);
};