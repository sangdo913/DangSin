#include"Headers.h"
#include"state.h"

extern CIRCLE r3;
extern CIRCLE r2;

void ProcessHits(unsigned int uiHits, unsigned int *pBuffer);
void DrawSelector(int x, int y);

void DrawAxis()
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(2, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 2, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 2);

	glEnd();
}

void SetLight()
{
	//directional light
	GLfloat Direction[4] = { 1,1,1,2 };
	GLfloat Direction2[4] = { 0,100,1,0 };
	GLfloat Ambient1[4] = { 0.2f,0.2f,0.2f,0.2f };
	GLfloat	Diffuse1[4] = { 0.4f,0.4f,0.4f,0.4f };
	GLfloat Specular1[4] = { 0.9f ,0.9f,0.9f,0.9f };

	glEnable(GL_LIGHTING);

	//directional light
	glLightfv(GL_LIGHT1, GL_POSITION, Direction2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Specular1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Ambient1);

	//directional light attenuation
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.1);

	//glLightfv(GL_LIGHT2, GL_POSITION, Direction);
	//glLightfv(GL_LIGHT2, GL_DIFFUSE, Diffuse1);
	//glLightfv(GL_LIGHT2, GL_SPECULAR, Specular1);
	//glLightfv(GL_LIGHT2, GL_AMBIENT, Ambient1);

	////directional light attenuation
	//glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.01);
	//glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.001);
	//glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0);

	glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT2);
	/*
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.01);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.2);

	glLightfv(GL_LIGHT2, GL_POSITION, Direction2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Diffuse1);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Specular1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, Ambient1);

	glEnable(GL_LIGHT2);*/
}

void setPosition(point3 &point, const point3 vector, float theta)
{
	point3 temp;
	memcpy(temp, vector, sizeof(point3));

	YRotate(temp, theta);
	for (int i = 0; i < 3; i++)
		point[i] += temp[i];
}


void ChangeSize(int w, int h)
{
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	(System.screen).setScreen((float)w, (float)h);
	if (w <= h)
		gluPerspective(60.0f, (float)h / w, 1.0, 2000.0);
	else
		gluPerspective(60.0f, (float)w / h, 1.0, 2000.0);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}




void mouseButton(int button, int state, int x, int y)
{
	Input.setMousePosition(x, y);
	switch (button)
	{

	case GLUT_LEFT_BUTTON:;
		if (state == GLUT_DOWN)
		{
			Input.LeftDown();
			if(System.pickedCheck)DrawSelector(x, y);
		/*	if (System.picked)
			{
				System.getState()->setState(new MouseLeft(x,y));
			}


			else
			{
				System.getState()->setState(new Default());
			}*/
		}

		else if (state == GLUT_UP)
		{
			//System.getState()-> end();
			//System.picked = NULL;
			//System.getState()->setState(new Default());
			Input.LeftUp();

			glutPostRedisplay();
		}
			//System.getState()->setState(new Default());
		break;

	case GLUT_RIGHT_BUTTON:
	//	STATE *State = System.getState();
		if (state == GLUT_DOWN)
		{
			Input.RightDown();
			//State->setState(new MouseInput(x, y));
		}

		else if(state == GLUT_UP)
		{
			Input.RightUp();/*
			System.getState()->end();
			State->setState(new Default());*/
		}
		break;

	}

}

void mouseMove(int x, int y)
{
	
//	STATE* State = System.getState();
//	State->action(x, y);
	Input.setMousePosition(x, y);
	glutPostRedisplay();
}


void DrawSelector(int x, int y)
{
	static unsigned int aSelectBuffer[SELECT_BUF_SIZE];
	static unsigned int uiHits;
	static int aViewport[4];

	glGetIntegerv(GL_VIEWPORT, aViewport);

	glSelectBuffer(SELECT_BUF_SIZE, aSelectBuffer);
	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	float w = System.screen.width;
	float h = System.screen.height;
	// 5x5 Region
	gluPickMatrix((double)x, (double)(aViewport[3] - y), 5.0, 5.0, aViewport);

	// Same Clipping Window as in Reshape()
	//glOrtho(-1.15, 1.15, -1.15, 1.15, -5, 5);

	if (w <= h)
		gluPerspective(60.0f, (float)h / w, 1.0, 2000.0);
	else
		gluPerspective(60.0f, (float)w / h, 1.0, 2000.0);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	ObjManager.Selector();

	/*point3 edge1 = { -122.4 ,0,  -61.2 };
	point3 edge2 = { -122.4 ,0,  61.2 };
	point3 edge3 = { 122.4 ,0,  -61.2 };
	point3 edge4 = { 122.4 ,0,  61.2 };
	point3 up = { 0,1,0 };*/
	/*glLoadName(GREEN);
	glBegin(GL_QUAD_STRIP);
	glNormal3fv(up);
	glTexCoord2f(0, 0);
	glVertex3fv(edge1);

	glNormal3fv(up);
	glTexCoord2f(0, 0);
	glVertex3fv(edge2);

	glNormal3fv(up);
	glTexCoord2f(0, 0);
	glVertex3fv(edge3);

	glNormal3fv(up);
	glTexCoord2f(0, 0);
	glVertex3fv(edge4);
	glEnd();*/

	//glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	uiHits = glRenderMode(GL_RENDER);
	ProcessHits(uiHits, aSelectBuffer);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}


void ProcessHits(unsigned int uiHits, unsigned int *pBuffer)
{
	static unsigned int i, j;
	static unsigned int uiName, *ptr;

	ptr = pBuffer; // 히트된 개수

	if (uiHits == 0)
	{
		System.picked = nullptr;
		return;
	}
		uiName = *ptr;
		ptr += 3;

		for (j = 0; j < 1; j++)		// for each name
		{
			ObjManager.Selector(*ptr);
			ptr++;
		}
}