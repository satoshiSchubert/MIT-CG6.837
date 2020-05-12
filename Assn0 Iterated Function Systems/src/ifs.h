#pragma once
#include "matrix.h"
#include "image.h"
#include "vectors.h"
class IFS {
private:
	//仿射变换的个数
	int n;
	//仿射变换矩阵数组
	Matrix* matrix;
	//每一个仿射变换的选取概率数组
	float* prob;
public:
	//构造函数，使用仿射变换个数初始化
	IFS():n(0),matrix(nullptr),prob(nullptr){}
	//析构函数
	~IFS() {
		delete[] matrix;
		delete[] prob;
	}
	//读取IFS输入
	void input(const char* file);
	//绘制IFS图片
	void render(Image& image, int num_points, int num_iters);
};