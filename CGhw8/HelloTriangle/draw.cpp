#include "draw.h"

// 按Point中y值排序
bool cpmpare(Point a, Point b) {
	return a.y < b.y;
}


// 把含有x,y坐标的vector转换成float*顶点数组(填充z值0.0f)
// 把含有x,y坐标的vector转换成float*顶点数组(填充z值0.0f)
float* getRealCoordinate1(vector<float> p, int length) {
	int length1 = length * 3;
	float* line = new float[length1];
	int index = 0;
	for (int i = 0; i < length; i = i + 2) {
		line[index] = p[i];
		line[index + 1] = p[i + 1];
		line[index + 2] = 0.0f;
		index = index + 3;
	}
	return line;
}

float* getRealCoordinate(vector<Point> p, int length, int width, int height) {
	int length1 = length * 3;
	float* line = new float[length1];
	int index = 0;
	for (int i = 0; i < length; i = i + 1) {
		line[index] = float(p[i].x) / float(width / 2);
		line[index + 1] = float(p[i].y) / float(height / 2);
		line[index + 2] = 0.0f;
		index = index + 3;
	}
	return line;
}



// 两值交换
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

// 
// 插值得到t值对应坐标
Point getBezierPoint(Point A, Point B, Point C, Point D, float t) {
	Point P;
	float a1 = pow((1 - t), 3);
	float a2 = pow((1 - t), 2) * 3 * t;
	float a3 = 3 * t*t*(1 - t);
	float a4 = t*t*t;
	P.x = a1*A.x + a2*B.x + a3*C.x + a4*D.x;
	P.y = a1*A.y + a2*B.y + a3*C.y + a4*D.y;
	return P;
}

vector<Point> BezierCurve(Point A, Point B, Point C, Point D) {
	vector<Point> BezierPoints;
	for (float t = 0.0f; t <= 1.0f; t += 0.002f) {
		BezierPoints.push_back(getBezierPoint(A, B, C, D, t));
	}
	return BezierPoints;
}


// ---------直线算法-------------------------------------------------------
// 已知x方向递增，迭代得到y坐标
void getYcoordinate(int* Ycoordinate, int pi, int dx, int dy, int length) {
	int parm1 = 2 * dy;
	int parm2 = 2 * dy - 2 * dx;
	for (int i = 0; i < length; i++) {
		if (i == length - 1) {
			// 计算完成，此处为终点坐标
			return;
		}
		if (pi <= 0) {
			Ycoordinate[i + 1] = Ycoordinate[i];
			pi += parm1;
		}
		else {
			Ycoordinate[i + 1] = Ycoordinate[i] + 1;
			pi += parm2;
		}
	}
}
