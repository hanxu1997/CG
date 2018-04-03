#include "draw.h"

// ��Point��yֵ����
bool cpmpare(Point a, Point b) {
	return a.y < b.y;
}
// ---------����ͨ�ú���-------------------------------------------------------
// ��xy�����һ����[-1,1]
vector<float> normalize(vector<int>p, int width, int height) {
	vector<float> q;
	int length = p.size();
	for (int i = 0; i < length; i = i + 2) {
		q.push_back(float(p[i]) / float(width / 2));
		q.push_back(float(p[i + 1]) / float(height / 2));
	}
	return q;
}

// �Ѻ���x,y�����vectorת����float*��������(���zֵ0.0f)
float* getRealCoordinate(vector<float> p, int length) {
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

// ��ֵ����
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
// ---------ֱ���㷨-------------------------------------------------------
// ��֪x��������������õ�y����
void getYcoordinate(int* Ycoordinate, int pi, int dx, int dy, int length) {
	int parm1 = 2 * dy;
	int parm2 = 2 * dy - 2 * dx;
	for (int i = 0; i < length; i++) {
		if (i == length - 1) {
			// ������ɣ��˴�Ϊ�յ�����
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


// ������յ�����õ����������е��xy���꣺x0,y0,...xi,yi,...��x1,y1
vector<int> BresenhamLine(int x0, int y0, int x1, int y1) {
	int dx = x1 - x0;
	int dy = y1 - y0;
	int length = 0;
	int p0 = 0;
	int Xcoordinate[1201] = { 0 };
	int Ycoordinate[1201] = { 0 };
	// б�ʲ�����
	if (x0 == x1) {
		length = fabs(y1 - y0) + 1;
		if (y0 > y1) {
			swap(y0, y1);
		}
		for (int i = 0; i < length; i++) {
			Xcoordinate[i] = x0;
			Ycoordinate[i] = y0 + i;
		}
	} // б�ʴ���
	else {
		// |m|<=`1,point0��point1��
		// |m|>1��point0�£� point1��
		float m = float(y1 - y0) / float(x1 - x0);
		if (fabs(m) <= 1 && x0 > x1) {
			swap(x0, x1);
			swap(y0, y1);
		}
		if (fabs(m) > 1 && y0 > y1) {
			swap(x0, x1);
			swap(y0, y1);
		}
		m = float(y1 - y0) / float(x1 - x0);
		dx = x1 - x0;
		dy = y1 - y0;
		if (fabs(m) <= 1) { // [-1,1]
			length = x1 - x0 + 1;
			for (int i = 0; i < length; i++) {
				Xcoordinate[i] = x0 + i;
			}
			if (dy < 0) { // [-1,0)
				Ycoordinate[0] = -y0;
				// ����x��Գ�ʹpoint1'��point0����
				Ycoordinate[length - 1] = -y1;
				p0 = 2 * (-dy) - dx;
				getYcoordinate(Ycoordinate, p0, dx, -dy, length);
				// point1'����point1
				for (int i = 0; i < length; i++) {
					Ycoordinate[i] = -Ycoordinate[i];
				}
			}
			else { // [0,1] 
				Ycoordinate[0] = y0;
				Ycoordinate[length - 1] = y1;
				p0 = 2 * dy - dx;
				getYcoordinate(Ycoordinate, p0, dx, dy, length);
			}
		}
		else { // m < -1 || m > 1
			length = y1 - y0 + 1;
			for (int i = 0; i < length; i++) {
				Ycoordinate[i] = y0 + i;
			}
			if (dx < 0) { // m < -1
				Xcoordinate[0] = -x0;
				Xcoordinate[length - 1] = -x1;
				p0 = 2 * (-dx) - dy;
				getYcoordinate(Xcoordinate, p0, dy, -dx, length);
				for (int i = 0; i < length; i++) {
					Xcoordinate[i] = -Xcoordinate[i];
				}
			}
			else {
				Xcoordinate[0] = x0;
				Xcoordinate[length - 1] = x1;
				p0 = 2 * dx - dy;
				getYcoordinate(Xcoordinate, p0, dy, dx, length);
			}
		}
	}
	vector<int> p;
	int j = 0;
	for (int i = 0; i < length * 2; i = i + 2) {
		p.push_back(Xcoordinate[j]);
		p.push_back(Ycoordinate[j]);
		j++;
	}
	return p;
}



// ---------��Բ�㷨-------------------------------------------------------
vector<int> BresenhamCircle(int xc, int yc, int r) {
	vector<int> Circle;
	int x = 0;
	int y = r;
	int d = 3 - (r<<1);
	Circle.push_back(xc + x);
	Circle.push_back(xc + y);
	Circle.push_back(xc + x);
	Circle.push_back(xc - y);
	Circle.push_back(xc - x);
	Circle.push_back(xc + y);
	Circle.push_back(xc - x);
	Circle.push_back(xc - y);
	Circle.push_back(xc + y);
	Circle.push_back(xc + x);
	Circle.push_back(xc + y);
	Circle.push_back(xc - x);
	Circle.push_back(xc - y);
	Circle.push_back(xc + x);
	Circle.push_back(xc - y);
	Circle.push_back(xc - x);
	while (x < y) {
		if (d < 0) {
			d = d + (x<<2) + 6;
		}
		else {
			d = d + ((x - y)<<2) + 10;
			y--;
		}
		x++;
		Circle.push_back(xc + x);
		Circle.push_back(xc + y);
		Circle.push_back(xc + x);
		Circle.push_back(xc - y);
		Circle.push_back(xc - x);
		Circle.push_back(xc + y);
		Circle.push_back(xc - x);
		Circle.push_back(xc - y);
		Circle.push_back(xc + y);
		Circle.push_back(xc + x);
		Circle.push_back(xc + y);
		Circle.push_back(xc - x);
		Circle.push_back(xc - y);
		Circle.push_back(xc + x);
		Circle.push_back(xc - y);
		Circle.push_back(xc - x);
	}
	return Circle;
}

// ---------�����ι�դ���㷨-------------------------------------------------------
// p1p2�£� p3���ϣ����ŵ������Σ�
vector<int> drawPositive(Point p1, Point p2, Point p3) {
	float k1, k2;
	if (p1.x < p2.x) {
		k1 = -(float)(p1.x - p3.x) / (float)(p1.y - p3.y);
		k2 = -(float)(p2.x - p3.x) / (float)(p2.y - p3.y);
	}
	else {
		k1 = -(float)(p2.x - p3.x) / (float)(p2.y - p3.y);
		k2 = -(float)(p1.x - p3.x) / (float)(p1.y - p3.y);
	}

	float xL = p3.x;
	float xR = p3.x;
	vector<int> coordinate;
	for (int y = p3.y; y >= p1.y; y--) {
		for (int x = (int)xL; x <= (int)xR; x++) {
			coordinate.push_back(x);
			coordinate.push_back(y);
		}
		xL += k1;
		xR += k2;
	}
	return coordinate;
}

// p1�£� p2p3���ϣ����ŵ������Σ�
vector<int> drawNegative(Point p1, Point p2, Point p3) {
	float k1, k2;
	if (p2.x < p3.x) {
		k1 = (float)(p2.x - p1.x) / (float)(p2.y - p1.y);
		k2 = (float)(p3.x - p1.x) / (float)(p3.y - p1.y);
	}
	else {
		k1 = (float)(p3.x - p1.x) / (float)(p3.y - p1.y);
		k2 = (float)(p2.x - p1.x) / (float)(p2.y - p1.y);
	}

	float xL = p1.x;
	float xR = p1.x;
	vector<int> coordinate;
	for (int y = p1.y; y <= p2.y; y++) {
		for (int x = (int)xL; x <= (int)xR; x++) {
			coordinate.push_back(x);
			coordinate.push_back(y);
		}
		xL += k1;
		xR += k2;
	}
	return coordinate;
}


// ��������
vector<int> drawTriangle(Point p1, Point p2, Point p3) {
	vector<Point> points;
	vector<int> trianglePoints;
	vector<int> v1;
	vector<int> v2;
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	sort(points.begin(), points.end(), cpmpare);
	p1 = points[0];
	p2 = points[1];
	p3 = points[2];
	if (p1.y == p2.y) { // ����������
		trianglePoints = drawPositive(p1, p2, p3);
	}
	else if (p2.y == p3.y) { // ����������
		trianglePoints = drawNegative(p1, p2, p3);
	}
	else { // һ��һ��ƴ�Ӷ���
		int x4 = (int)((float)((p3.x - p1.x)*(p2.y - p1.y)) / (float)(p3.y - p1.y)) + p1.x;
		Point p4(x4, p2.y);
		v1 = drawPositive(p4, p2, p3);
		v2 = drawNegative(p1, p4, p2);
		int length1 = v1.size();
		int length2 = v2.size();
		for (int i = 0; i < length1 + length2; i++) {
			if (i < length1) {
				trianglePoints.push_back(v1[i]);
			}
			else {
				trianglePoints.push_back(v2[i - length1]);
			}

		}

	}
	return trianglePoints;
}
