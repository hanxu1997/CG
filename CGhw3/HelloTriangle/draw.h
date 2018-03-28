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


// ---------ֱ���㷨-------------------------------------------------------
// ��ֵ����
void swap(int *a, int *b);
// �����õ�y����
void getYcoordinate(int* Ycoordinate, int pi, int dx, int dy, int length);
// ��һ����[-1,1]
vector<float> normalize(vector<int>p, int width, int height);

// ������յ�����õ����������е��xy���꣺x0,y0,...xi,yi,...��x1,y1
vector<int> BresenhamLine(int x0, int y0, int x1, int y1);
// �Ѻ���x,y�����vectorת���ɴ���ɫ��float*
float* getRealCoordinate(vector<float> p, int length);
// -----------------------------------------------------------------------
// ---------��Բ�㷨-------------------------------------------------------
vector<int> BresenhamCircle(int xc, int yc, int r);

// ---------�����ι�դ���㷨-------------------------------------------------------
// p1p2�£� p3����
vector<int> drawPositive(Point p1, Point p2, Point p3);
// p1�£� p2p3����
vector<int> drawNegative(Point p1, Point p2, Point p3);
// ��������
vector<int> drawTriangle(Point p1, Point p2, Point p3);
