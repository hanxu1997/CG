#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
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
	Point(Point & b) {
		*this = b;
	}
	void set(Point* s1, Point* s2) {
		s1->x = s2->x;
		s1->y = s2->y;
	}
	Point& operator=(const Point& s)//���������  
	{
		set(this, (Point*)&s);
	}
};

bool nonmem_cmp(const Point&t1, const Point&t2)
{
	if (t1.y > t2.y)
		return true;
	return false;
}


// ������ɫ��Դ��
const char *vertexShaderSource = "#version 440 core\n"
			"layout (location = 0) in vec3 Position;\n"
			"out vec4 vetexColor;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(Position, 1.0);\n"
			"   vetexColor = vec4(0.45, 0.45, 0.45, 1.0);\n"
			"}\0";
// Ƭ����ɫ��Դ��
const char *fragmentShaderSource = "#version 440 core\n"
								"out vec4 FragColor;\n"
								"in vec4 vetexColor;\n"
								"void main()\n"
								"{\n"
								"   FragColor = vetexColor;\n"
								"}\n\0";

void processInput(GLFWwindow *);
void framebuffer_size_callback(GLFWwindow*, int, int);
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
vector<int> BresenhamCircle(int xc, int yc, int r) {
	vector<int> Circle;
	int x = 0;
	int y = r;
	int d = 3 - 2 * r;
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
			d = d + 4 * x + 6;
		} else {
			d = d + 4*(x - y) + 10;
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

int main() {
	// ��ʼ��GLFW
	glfwInit();
	// ����GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// �������ڶ��󣬴�����кʹ�����ص����ݣ�
	// ���һᱻGLFW����������Ƶ�����õ�
	GLFWwindow* window = glfwCreateWindow(1200, 800, "HellloTriangle", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	// ֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	// ע���������������GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// GLAD: �����OpenGL����ָ��
	// �����κ�OpenGL����֮ǰ��Ҫ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// Setup ImGui binding
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(window, true);

	// Setup style
	// ImGui::StyleColorsDark();
	ImVec4 clear_color = ImVec4(0.92f, 0.92f, 0.92f, 1.0f);

	// ������������ɫ������
	// 1. ������ɫ��
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// ��鶥����ɫ���Ƿ����ɹ�
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}
	// 2. Ƭ����ɫ��
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// ���Ƭ����ɫ���Ƿ����ɹ�
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}
	// ������ɫ��
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// ����Ƿ����ӳɹ�
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
	// ������ɺ�ɾ����ɫ������
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	// ������ɫ���������
	glUseProgram(shaderProgram);

	// ���㻺����󣬶����������
	unsigned int VBO;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// ��
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ���Ӷ�������
	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	vector<float> p1 = normalize(BresenhamLine(-200, -100, 0, 200), 1200, 800);
	int length1 = p1.size();
	float* line1 = getRealCoordinate(p1, length1);
	vector<float> p2 = normalize(BresenhamLine(200, -100, 0, 200), 1200, 800);
	int length2 = p2.size();
	float* line2 = getRealCoordinate(p2, length2);
	vector<float> p3 = normalize(BresenhamLine(-200, -100, 200, -100), 1200, 800);
	int length3 = p3.size();
	float* line3 = getRealCoordinate(p3, length3);



	int r = 100;

	ImGuiWindowFlags window_flags = 0;
	bool show_circle_window = false;
	bool show_line_window = true;
	bool show_rasterization_window = false;

	int flag = 0;
	// ��Ⱦѭ�� render loop
	while (!glfwWindowShouldClose(window))
	{
		flag++;
		processInput(window);
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();
		// ����ɫ
		glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		bool* p_open = NULL;
		// ������-----------------------------------------------------------------------------------
		ImGui::Begin("main", p_open, window_flags);
		window_flags |= ImGuiWindowFlags_MenuBar;
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("Windows"))
			{
				ImGui::MenuItem("Line Window", NULL, &show_line_window);
				if (show_line_window == true)
				{
					show_rasterization_window = false;
					show_circle_window = false;
				}
				ImGui::MenuItem("Circle Window", NULL, &show_circle_window);
				if (show_circle_window == true)
				{
					show_rasterization_window = false;
					show_line_window = false;
				}
				ImGui::MenuItem("Rasterization Window", NULL, &show_rasterization_window);
				if (show_rasterization_window == true)
				{
					show_circle_window = false;
					show_line_window = false;
				}

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		if (ImGui::CollapsingHeader("Help"))
		{
			ImGui::TextWrapped("Please click 'Windows' to choose different functions. \n\n");
		}

		ImGui::Spacing();
		ImGui::Text("Hello!");
		ImGui::End();
		// �����ڻ������--------------------------------------------------------------------------
		
		// rendering lines
		if (show_line_window)
		{
			glBufferData(GL_ARRAY_BUFFER, 3 * length1 * sizeof(float), line1, GL_STATIC_DRAW);
			glPointSize(5.0f);
			glDrawArrays(GL_POINTS, 0, length1 / 2);
			glBufferData(GL_ARRAY_BUFFER, 3 * length2 * sizeof(float), line2, GL_STATIC_DRAW);
			glPointSize(5.0f);
			glDrawArrays(GL_POINTS, 0, length2 / 2);
			glBufferData(GL_ARRAY_BUFFER, 3 * length3 * sizeof(float), line3, GL_STATIC_DRAW);
			glPointSize(5.0f);
			glDrawArrays(GL_POINTS, 0, length3 / 2);
		}
		// rendering points
		if (show_circle_window)
		{
			ImGui::Begin("Circle Window", &show_circle_window);
			ImGui::SliderInt("Radius", &r, 0, 400);
			vector<float> circleVector = normalize(BresenhamCircle(0, 0, r), 1200, 800);
			int circleLength = circleVector.size();
			float* circle = getRealCoordinate(circleVector, circleLength);
			glBufferData(GL_ARRAY_BUFFER, 3 * circleLength * sizeof(float), circle, GL_STATIC_DRAW);
			glPointSize(5.0f);
			glDrawArrays(GL_POINTS, 0, circleLength/2);
			ImGui::End();
		}
		if (show_rasterization_window) {
			Point v1(-200, -100);
			Point v2(0, 200);
			Point v3(200, -100);
			vector<Point> points;
			points.push_back(v1);
			points.push_back(v2);
			points.push_back(v3);
			sort(points.begin(), points.end(), nonmem_cmp);
			cout << v2.x << endl;
			

		}
		// Rendering
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	delete[] line1;
	// �ͷ�/ɾ��֮ǰ�����������Դ
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}



// �������
void processInput(GLFWwindow *window)
{
	// glfwGetKey
	// ���룺һ�������Լ�һ������(�������û��Ƿ����˷��ؼ�Esc)
	// ���أ���������Ƿ����ڱ�����
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

// �Դ���ע��һ���ص�������������ÿ�δ��ڴ�С��������ʱ�򱻵���
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// ���ô��ڵ�ά��
	glViewport(0, 0, width, height);
}

// �����õ�y����
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


// ��ֵ����
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

// ��һ����[-1,1]
vector<float> normalize(vector<int>p, int width, int height) {
	vector<float> q;
	int length = p.size();
	for (int i = 0; i < length; i = i + 2) {
		q.push_back(float(p[i]) / float(width / 2));
		q.push_back(float(p[i + 1]) / float(height / 2));
	}
	return q;
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

// �Ѻ���x,y�����vectorת����float*
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
