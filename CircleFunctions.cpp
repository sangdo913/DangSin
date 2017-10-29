#include"Headers.h"

static point3 vectors[36][18];
typedef float pos[2];


void prepareVertex(Circle circle)
{
	point3 first = { 3.075f,0.0f,0.0f };

	float theta = 0;

	memcpy(circle[0][0], first, sizeof(point3));

	//set row 0 vertex
	for (int i = 0; i < 18; i++)
	{
		ZRotate(first, theta);
		memcpy(circle[0][i], first, sizeof(point3));
		theta += 20.0f;
	}

	theta = -360.0f / 36.0f;

	//set Normal Vecetor of Donut
	for (int i = 1; i < 36; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			memcpy(circle[i][j], circle[i - 1][j], sizeof(point3));
			YRotate(circle[i][j], theta);
		}
		// 90 < theta <270
		for (int j = 5; j < 14; j++)
		{
			memcpy(circle[i][j], circle[i - 1][j], sizeof(point3));
			YRotate(circle[i][j], -180.0f + theta);
		}
		for (int j = 14; j < 18; j++)
		{
			memcpy(circle[i][j], circle[i - 1][j], sizeof(point3));
			YRotate(circle[i][j], theta);
		}
		theta -= 10.0f;
	}
}

void prepareVertex(Circle x, point3 origin)
{
	prepareVertex(x);

	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				x[i][j][k] += origin[k];
			}
		}
	}
}

void DrawVertex(Circle circle)
{
	for (int i = 0; i < 36; i++)
	{
		glBegin(GL_QUAD_STRIP);
		//1,0,0 벡터를 10도씩 회전시키면서 normal Vector들을 이동시킵니다.
		for (int j = 0; j < 18 + 1; j++)
		{
			/*point3 temp;
			memcpy(temp, vectors[i][j%18], sizeof(point3));
			setPosition(temp, vector, theta);

			glNormal3fv(vectors[i][j%18]);
			glTexCoord2f((float)i/36.0f, (float)j / 18.0f );
			glVertex3fv(temp);

			memcpy(temp, vectors[(i + 1) % 36][j%18], sizeof(point3));
			setPosition(temp, vector, theta-10.0f);

			glNormal3fv(vectors[(i + 1) % 36][j%18]);
			glTexCoord2f((float)(i+1) / 36.0f,  (float)j / 18.0f);
			glVertex3fv(temp);*/

			glNormal3fv(circle[i][j % 18]);
			glTexCoord2f((float)i / 36.0f, (float)j / 18.0f);
			glVertex3fv(circle[i][j % 18]);

			glNormal3fv(circle[(i + 1) % 36][j % 18]);
			glTexCoord2f((float)(i + 1) / 36.0f, (float)j / 18.0f);
			glVertex3fv(circle[(i + 1) % 36][j % 18]);
		}
		glEnd();
	}
}
