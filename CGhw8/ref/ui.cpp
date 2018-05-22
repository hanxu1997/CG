#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
//#include <pair>

using namespace std;

//points保存四个点
vector<pair<GLfloat, GLfloat> > points;
//设置两个bool变量来记录是否已经画出四个点之间的直线，以及相关贝塞尔曲线
bool line = false;
bool curve = false;

//画直线
void drawLine() {
    glColor3f(1.0f, 0, 0);
    glPointSize(1.0);
    for (int i = 0; i <= 2; i ++) {
        glBegin(GL_LINES);
            glVertex2f(points[i].first, points[i].second);
            glVertex2f(points[i+1].first, points[i+1].second); 
        glEnd();
    }
}

//贝塞尔曲线
void drawCurve() {
    glColor3f(0, 1.0f, 0);
    glPointSize(1.0);
    for (GLfloat t = 0; t <= 1.0; t += 0.001) {
        GLfloat x = points[0].first*pow(1.0f-t, 3) + 3*points[1].first*t*pow(1.0f-t, 2) + 3*points[2].first*t*t*(1.0f-t) + points[3].first*pow(t, 3);
        GLfloat y =  points[0].second*pow(1.0f-t, 3) + 3*points[1].second*t*pow(1.0f-t, 2) + 3*points[2].second*t*t*(1.0f-t) + points[3].second*pow(t, 3);
        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
    }
}

//初始化函数
void myInit() {
    glClearColor(0, 0, 0, 0);
    glColor3f(1.0f, 0, 0);
    glPointSize(5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0.0, 500, 0.0, 500);
}

 void myDisplay() { 
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

//对于鼠标点击的响应函数
void myMouse(int button, int state, int x, int y)
{
    //按下鼠标左键
     if(state==GLUT_DOWN)
     {
        //画4个点
        if (points.size() < 4) {
            glBegin(GL_POINTS);
                glVertex2i(x, 500 - y);
            glEnd();
            points.push_back(make_pair(GLfloat(x), GLfloat(500 - y)));
        }
        //若已经画好四个点，则开始画点连成的线段\曲线
        else if (points.size() == 4) {
            //线段
            if (line == false) {
                drawLine();
                line = true;
            }
            //曲线
            else if (line == true && curve == false) {
                drawCurve();
                curve = true;
            }
            //清空
            else if (line == true && curve == true) {
                glClear(GL_COLOR_BUFFER_BIT);
                glColor3f(1.0f, 0, 0);
                glPointSize(5.0);
                line = false;
                curve = false;
                while(!points.empty()) {
                    points.pop_back();
                }
            }
        }
        glFlush();
     }
 }

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bezier-curve");

    myInit();
    glutDisplayFunc (myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}