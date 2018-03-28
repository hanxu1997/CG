#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Point {
	int x;
	int y;
	Point() {
		x = 0;
		y = 0;
	}
	Point(int x0, int y0) {
		x = x0;
		y = y0;
	}
};


// ---------直线算法-------------------------------------------------------
// 两值交换
void swap(int *a, int *b);
// 迭代得到y坐标
void getYcoordinate(int* Ycoordinate, int pi, int dx, int dy, int length);
// 归一化到[-1,1]
vector<float> normalize(vector<int>p, int width, int height);

// 由起点终点坐标得到连线上所有点的xy坐标：x0,y0,...xi,yi,...，x1,y1
vector<int> BresenhamLine(int x0, int y0, int x1, int y1);
// 把含有x,y坐标的vector转换成带颜色的float*
float* getRealCoordinate(vector<float> p, int length);
// -----------------------------------------------------------------------
// ---------画圆算法-------------------------------------------------------
vector<int> BresenhamCircle(int xc, int yc, int r);

// ---------三角形光栅化算法-------------------------------------------------------
// p1p2下， p3在上
vector<int> drawPositive(Point p1, Point p2, Point p3);
// p1下， p2p3在上
vector<int> drawNegative(Point p1, Point p2, Point p3);
// 画三角形
vector<int> drawTriangle(Point p1, Point p2, Point p3);
