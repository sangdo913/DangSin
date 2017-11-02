#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>

#include <math.h>
#include <iostream>

//#include "CollisionWall.h"
#include "Physics.h"
#include "Ball.h"

#define RADIUS 5
//#define WIDTH 400
//#define HEIGHT 400
//#define originX 50
//#define originY 50

using namespace std;

static bool	mouseLeftDown;
static float point[2][2];

//static float theta;


Vector3 yellowBallP(100, 200, 0);
Vector3 redBallP(200, 100, 0);
Vector3 whiteBallP(200, 300, 0);
//Vector3 yellowBallD(0, 0, 0);

Ball yellowBall(yellowBallP);
Ball redBall(redBallP);
Ball whiteBall(whiteBallP);

Wall wall;

//static float whiteBall[2][2];
//static float yellowBall[2][2];
//static float redBall[2][2];
//��ݷ�

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//coordinate
	//glColor3f(1, 0, 0);
	//glBegin(GL_LINES);
	//	glVertex3f(-10,0,0);
	//	glVertex3f(10,0,0);
	//glEnd();
	//glColor3f(0, 1, 0);
	//glBegin(GL_LINES);
	//	glVertex3f(0, -10, 0);
	//	glVertex3f(0, 10, 0);
	//glEnd();
	//glColor3f(0, 0, 0);
	//glBegin(GL_LINES);
	//	glVertex3f(0.5, -0.1, 0);
	//	glVertex3f(0.5, 0.1, 0);
	//glEnd();

	//Balls
	glPointSize(10);
	glBegin(GL_POINTS);
		glColor3f(1, 0.9, 0.1);
		yellowBall.Draw();
		glColor3f(1, 0, 0);
		redBall.Draw();
		glColor3f(0.9, 0.9, 0.9);
		whiteBall.Draw();
	glEnd();

	//mouse line
	if (mouseLeftDown) {
		glEnable(GL_LINE_STIPPLE);

		glLineStipple(3, 0xcccc);
		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
			glVertex2fv(point[0]);
			glVertex2fv(point[1]);
		glEnd();

		printf("points %f %f\n", point[1][0], point[1][1]);
		glDisable(GL_LINE_STIPPLE);
	}
	else;
		

	//boundary
	wall.Draw();


	glFlush();
}

void init(void)
{
	
	point[0][0] = 0;
	point[0][1] = 0;
	point[1][0] = 0;
	point[1][1] = 0;

}

void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//Rendering Buffer ���� ��.
}

void ChangeSize(int w, int h) {
	if (h == 0)	h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);//reset coordinate system
	glLoadIdentity();

	if (w <= h)
		gluOrtho2D(0, 500.0, 0, 500.0*(float)h / (float)w);
	else
		gluOrtho2D(0, 500.0*(float)w / (float)h, 0, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void timer(int value)
{
	if (!mouseLeftDown) {
		yellowBall.move();
		redBall.move();
		whiteBall.move();
	}

	yellowBall.BoundaryCollision();
	redBall.BoundaryCollision();
	whiteBall.BoundaryCollision();

	yellowBall.collise(redBall, whiteBall);
	redBall.collise(yellowBall, whiteBall);
	whiteBall.collise(yellowBall, redBall);

	glutTimerFunc(3, timer, 1);
	glutPostRedisplay();
}

void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		printf("%d %d \n", x, y);
		if (state == GLUT_DOWN)
		{
			if (!mouseLeftDown)
			{
				double viewport[4];
				glGetDoublev(GL_VIEWPORT, viewport);

				point[0][0] = x / (float)viewport[2] * 500;
				point[0][1] = (viewport[3] - y) / (float)viewport[3] * 500;
				point[1][0] = point[0][0];
				point[1][1] = point[0][1];
				cout << "glutdown," << endl;
				mouseLeftDown = true;
			}
		}
		else if (state == GLUT_UP)
		{
			if (mouseLeftDown)
				mouseLeftDown = false;
			cout << "glutup," << endl;
		}
	}
	glutPostRedisplay();//ȭ�� ���� �ʿ��� ��. display callback�Լ� �����.
}
void mouseMotion(int x, int y)
{
	if (mouseLeftDown)
	{
		double viewport[4];
		glGetDoublev(GL_VIEWPORT, viewport);
		//cout << "viewport : (" << viewport[0] << "," << viewport[1] << "," << viewport[2] << "," << viewport[3] << ")" << endl;

		point[1][0] = x / (float)viewport[2] * 500;
		point[1][1] = (viewport[3] - y) / (float)viewport[3] * 500;
		//cout << "point(" << point[1][0] << "," << point[1][1] << ")" << endl;
		////////����� ����////////
		if (sqrt((point[0][0]-yellowBall.transform->position.x)*(point[0][0] - yellowBall.transform->position.x)+
				(point[0][1]- yellowBall.transform->position.y)*(point[0][1] - yellowBall.transform->position.y))<=RADIUS) {
			yellowBall.transform->velocity.x = (point[1][0] - yellowBall.transform->position.x);
			yellowBall.transform->velocity.y = (point[1][1] - yellowBall.transform->position.y);
			//cout << "vector(" << yellowBall.transform->velocity.x << "," << yellowBall.transform->velocity.y << ")";
			yellowBall.transform->velocity.normalize();
			//cout << "unit : (" << yellowBall.transform->velocity.x << "," << yellowBall.transform->velocity.y << ")" << endl;
		}
		else if (sqrt((point[0][0] - redBall.transform->position.x)*(point[0][0] - redBall.transform->position.x) +
				(point[0][1] - redBall.transform->position.y)*(point[0][1] - redBall.transform->position.y)) <= RADIUS) { 
			redBall.transform->velocity.x = (point[1][0] - redBall.transform->position.x);
			redBall.transform->velocity.y = (point[1][1] - redBall.transform->position.y);
			redBall.transform->velocity.normalize();
		}
		else if (sqrt((point[0][0] - whiteBall.transform->position.x)*(point[0][0] - whiteBall.transform->position.x) +
				(point[0][1] - whiteBall.transform->position.y)*(point[0][1] - whiteBall.transform->position.y)) <= RADIUS) {
			whiteBall.transform->velocity.x = (point[1][0] - whiteBall.transform->position.x);
			whiteBall.transform->velocity.y = (point[1][1] - whiteBall.transform->position.y);
			whiteBall.transform->velocity.normalize();
		}

	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q'|'Q':
		exit(0); break;
	case VK_ESCAPE:
		exit(0); break;
	default:
		break;
	}
}

//void menu(int item)
//{
//	switch (item) {
//	case 1:
//		exit(0); break;
//	default:
//		break;
//	}
//}
void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Test_hyeon");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutTimerFunc(3, timer, 1);
	//glutKeyboardFunc(keyboard);

	//glutCreateMenu(menu);
	//glutAddMenuEntry("Exit", 1);
	//glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	SetupRC();

	glutMainLoop();
}