#include"Headers.h"

using namespace std;



typedef GLfloat point3[3];

void BuildFont()
{
	HFONT font;
	HFONT oldfont;

	font = CreateFontA(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		FF_DONTCARE | DEFAULT_PITCH, "Courier New");

	oldfont = (HFONT)SelectObject(Text::hDC, font);
	wglUseFontBitmaps(Text::hDC, 32, 96, Text::base);
	SelectObject(Text::hDC, oldfont);
	DeleteObject(font);
}

void killfont(GLvoid)
{
	glDeleteLists(Text::base, 96);
}

void glPrint(const char *fmt, ...)
{
	char text[256];
	va_list ap;
	if (fmt == NULL) return;
	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);

	glPushAttrib(GL_LIST_BIT);
	glListBase(Text::base - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}












////////////////////////////////////////

static MainCamera* mainCamera = MainCamera::getInstance();

void init();
void LoadImage();
void DrawAxis();
void LoadTexture();
void SetLight();
void setPosition(point3 &point, const point3 vector, float theta);
void ChangeSize(int w, int h);
void mouseMove(int x, int y); 
void mouseButton(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void RenderScene();
void ProcessHits(unsigned int uiHits, unsigned int *pBuffer);
void timer(int value);

////////////////////////////////////////
void PassiveMouse(int x, int y);
void main(int argc, char* argv[])

{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL HW 4");
	// 마우스 이벤트
	
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(PassiveMouse);
	glutMotionFunc(mouseMove);
	glutTimerFunc(3, timer, 1);
	init();
	SetupRC();

	glutMainLoop();
}

void init()
{
	BuildFont();
	MainCamera::getInstance()->transform->position = Vector3(0, 270, 0);
	MainCamera::getInstance()->transform->rotate(90, -0, -90);
}

////


void RenderScene(void)
{
	//set mainCamera

	//Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//forwarVector를 받아서 카메라를 돌립니다.

	Vector3 cameraPosition = mainCamera->transform->position;
	Vector3 forward = *(mainCamera->transform->Getforward());
	Vector3 upVector = *(mainCamera->transform->GetUp());
	gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, forward.x + cameraPosition.x,
		forward.y + cameraPosition.y, (forward.z + cameraPosition.z), upVector.x, upVector.y, upVector.z);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	SetLight();
	ObjManager.draw();






	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);







	glutSwapBuffers();

	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	Input.KeyButton(key);

	switch (key)
	{
	case VK_ESCAPE:
		Input.KeyButton(VK_ESCAPE);
	//	exit(0); 
		break;
	case 'S':
	case 's':
		Input.KeyButton('s');
		break;
	case 'T':
	case 't':
		break;
	case 'U':
	case 'u':
		break;
	case 'V':
	case 'v':
		break;
	case 'W':
	case 'w':
		Input.KeyButton('w');
		break;
	case 'X':
	case 'x':
		break;
	case'r':
	case'R':
		break;
	case'A':
	case'a':
		Input.KeyButton('a');
		break;
	case'D':
	case'd':
		Input.KeyButton('d');
		break;
	case '+':
	case'=':
		Input.KeyButton('+');
		break;
	case'-':
		Input.KeyButton('-');
		break;
	case ' ':

	default:
		break;
	}

	glutPostRedisplay();
}

void PassiveMouse(int x, int y)
{
	Input.setMousePosition(x, y);
}

//

void timer(int value)
{
	MainCamera* cam = MainCamera::getInstance();
	double projection[16];
	double modelView[16];

	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	cam->setProjection(projection);
	cam->setmodelView(modelView);

	ObjManager.Loop();
	glutTimerFunc(3, timer, 1);
	glutPostRedisplay();

	if (Input.isRightUp()) Input.RightUpEnd();
	if (Input.isLeftUp()) Input.LeftUpEnd();
	if (Input.isLeftDown()) Input.LeftDownEnd();
	if (Input.isRightDown()) Input.RightDownEnd();
}