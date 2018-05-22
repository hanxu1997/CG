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
	void set(int x0, int y0) {
		x = x0;
		y = y0;
	}
	Point(int x0, int y0) {
		x = x0;
		y = y0;
	}
};

// ��ֵ�õ�tֵ��Ӧ����
Point getBezierPoint(Point A, Point B, Point C, Point D, float t);
vector<Point> BezierCurve(Point A, Point B, Point C, Point D);
// �Ѻ���x,y�����vectorת���ɴ���ɫ��float*
float* getRealCoordinate(vector<Point> p, int length, int width, int height);

