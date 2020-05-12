#pragma once
#include "matrix.h"
#include "image.h"
#include "vectors.h"
class IFS {
private:
	//����任�ĸ���
	int n;
	//����任��������
	Matrix* matrix;
	//ÿһ������任��ѡȡ��������
	float* prob;
public:
	//���캯����ʹ�÷���任������ʼ��
	IFS():n(0),matrix(nullptr),prob(nullptr){}
	//��������
	~IFS() {
		delete[] matrix;
		delete[] prob;
	}
	//��ȡIFS����
	void input(const char* file);
	//����IFSͼƬ
	void render(Image& image, int num_points, int num_iters);
};