#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

void processInput(GLFWwindow *);
void framebuffer_size_callback(GLFWwindow*, int, int);

void getYcoordinate(int* Ycoordinate, int pi, int dx, int dy, int length);
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

vector<int> Breseham(int x0, int y0, int x1, int y1) {
	int dx = x1 - x0;
	int dy = y1 - y0;
	int length = 0;
	int p0 = 0;
	int Xcoordinate[1200] = { 0 };
	int Ycoordinate[800] = { 0 };
	// 斜率不存在
	if (x0 == x1) {
		length = fabs(y1 - y0) + 1;
		if (y0 > y1) {
			swap(y0, y1);
		}
		for (int i = 0; i < length; i++) {
			Xcoordinate[i] = x0;
			Ycoordinate[i] = y0 + i;
		}
	} // 斜率存在
	else {
		// |m|<=`1,point0左，point1右
		// |m|>1，point0下， point1上
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
				// 关于x轴对称使point1'在point0右上
				Ycoordinate[length - 1] = -y1;
				p0 = 2 * (-dy) - dx;
				getYcoordinate(Ycoordinate, p0, dx, -dy, length);
				// point1'返回point1
				for (int i = 0; i < length; i++) {
					Ycoordinate[i] = -Ycoordinate[i];
				}
			} else { // [0,1] 
				Ycoordinate[0] = y0;
				Ycoordinate[length - 1] = y1;
				p0 = 2 * dy - dx;
				getYcoordinate(Ycoordinate, p0, dx, dy, length);
			}
		} else { // m < -1 || m > 1
			length = y1 - y0 + 1;
			for (int i = 0; i < length; i++) {
				Ycoordinate[i] = y0 + i;
			}
			if (dx < 0) { // m < -1
				Xcoordinate[0] = -x0;
				Xcoordinate[length - 1] = -x1;
				p0 = 2 * (-dx) - dy;
				getYcoordinate(Xcoordinate, p0,dy, -dx, length);
				for (int i = 0; i < length; i++) {
					Xcoordinate[i] = -Xcoordinate[i];
				}
			} else {
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


int main() {
	vector<int> p = Breseham(-5, -5, 5, 5);
	int length = p.size();
	cout << length << endl;
	for (int i = 0; i < length; i = i+2) {
		cout << p[i] << " " << p[i + 1] << endl;
	}
	system("pause");
	return 0;
}



// 输入控制
void processInput(GLFWwindow *window)
{
	// glfwGetKey
	// 输入：一个窗口以及一个按键(这里检查用户是否按下了返回键Esc)
	// 返回：这个按键是否正在被按下
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

// 对窗口注册一个回调函数，它会在每次窗口大小被调整的时候被调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// 设置窗口的维度
	glViewport(0, 0, width, height);
}

// 得到y坐标
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