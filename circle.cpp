#include"Headers.h"
#include"Object.h"
#include"Circle.h"
#include<string>

using namespace std;


void CIRCLE::Draw()
{
	Circle vectors;
	//vector 세팅
	//prepareVertex(vectors, origin);
	prepareVertex(vectors);
	DrawVertex(vectors);
}

point3* CIRCLE::GetOrigin()
{
	return &origin;
}

point3* CIRCLE::GetVector()
{
	return &vector;
}

void CIRCLE::SetOrigin(point3 point)
{
	memcpy((*this).origin, point, sizeof(point3));
}

void CIRCLE::SetVector(point3 vector)
{
	memcpy((*this).vector, vector, sizeof(point3));
}

CIRCLE::CIRCLE()
{
	Draw();
	DrawFactory(FaceType::Rectangular);
	transform->position = Vector3(0,0,0);
	SetCollider(ColliderType::BALL, 3.075, 0);
	this->collider->setE(0.f);
	//test = new Test; //doing::start, doing::action, circle 멤버변수, 생성자, 소멸자 collide도 함께 가기 
}

CIRCLE::CIRCLE(point3 point)
{
	Draw();
	DrawFactory(FaceType::Rectangular);
	memcpy(origin, point, sizeof(point3));
	transform->position = Vector3(point);
	SetCollider(ColliderType::BALL, 3.075, 0);
	this->collider->setE(0.f);
	//test = new Test;
}

CIRCLE::CIRCLE(point3 point, Rotation rotation)
{
	memcpy((*this).origin, point, sizeof(point3));
	memcpy((*this).rotation, rotation, sizeof(point3));

	//test = new Test;
}

CIRCLE::~CIRCLE()
{
	//delete(test);
}

void CIRCLE::collide(Collider *collider)
{
	string name = collider->obj->getName();

	if (name.compare("CIRCLE") == 0)
	{
		Object* object = collider->obj;
		Transform* t = this->transform;
		Transform* colliderT = object->transform;

		float vecToForce = System.frame * transform->weight;
		Vector3 colliderVelocity = colliderT->getVelocity();
		Vector3 thisVelocity = t->getVelocity();
		
		Vector3 thisPos = t->position;
		Vector3 colPos = colliderT->position;
		//현재 공의 속도성분
		//tempdir : 충돌방향 벡터
		Vector3 tempdir;

		//tempdir.normalize();
		//if (Vector3::length(tempdir) < 3.075f * 2.f)
		//{
		//	colliderT->position = t->position - (tempdir.normalize()*3.075f);
		//	t->position = t->position + (tempdir*3.075f);
		//}



		

		////////////////////

		tempdir = t->position - colliderT->position;

		tempdir.normalize();
		//if (Vector3::length(tempdir) < 3.075f*2.f)
		//{				
				//Vector3 center = (thisPos + colPos) / 2.f;
			//	colliderT->position = center - tempdir*3.075f;
				//t->position = center + tempdir*3.075f;
		//}

		int count = 0;
		//if(Vector3::length(t->getVelocity()) > 0);
		while (t->position.distance(colliderT->position) < 3.075f*2.f)
		{
			t->position = t->position - thisVelocity*0.01f;
			colliderT->position = colliderT->position - colliderVelocity*0.01f;
			if (count > 150)
			{
				colliderT->position = t->position - (tempdir*3.08f);
				t->position = t->position + (tempdir*3.08f);
				break;
			}
			count++;
		}


		//////////////////

		if (count < 150)
		{
			float cE = collider->getE();


			float valueOfVelocity;

			tempdir = t->position - colliderT->position;
			tempdir.normalize();

			valueOfVelocity = (colliderVelocity.x * tempdir.x + colliderVelocity.z* tempdir.z);

			tempdir *= valueOfVelocity;
			colliderT->potentiate(tempdir* cE*vecToForce*-1);

			t->potentiate(tempdir* this->collider->getE()*vecToForce);
		}
	}

	else if (name.compare("XWALL") == 0)
	{
		Vector3 force(0, 0, 0);
		force.x = transform->getVelocity().x * -2.0f * System.frame * transform->weight;
		transform->potentiate(force);
		
	}
	else if (name.compare("ZWALL") == 0)
	{
		Vector3 force(0, 0, 0);
		force.z = transform->getVelocity().z * -2.0f *System.frame * transform->weight;
		transform->potentiate(force);
	}		
	/////////////////test 이동 경로 선 그리기(doing::start도 가볼것)
	//int i = test->lineCount;
	//test->line[i].setEnd(transform->position);
	//test->lineCount++;
	//test->line[test->lineCount].setStart(transform->position);
	//test->line[test->lineCount].setEnd(transform->position);
}

void CIRCLE::OnCollision(Collider * collider)
{
}

void CIRCLE::Start()
{
}

void CIRCLE::Update()
{
}

void CIRCLE::setE(float e)
{
	this->collider->setE(e);
}

void CIRCLE::DrawVertex(Circle circle)
{
	int size = 1368;
	point3* points = new point3[1368];
	pos* link = new pos[size];

	int k = 0;
	for (int i = 0; i < 36; i++)
	{
		//glBegin(GL_QUAD_STRIP);
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

			/////////////////////////////////////////////////////////////////
			point3 normalVec;

			for (int k = 0; k < 3; k++)
			{
				normalVec[k] = circle[i][j % 18][k];
			}
			memcpy(points[k] , normalVec,sizeof(point3));
			link[k][0] = (float)i / 36.0f;
			link[k][1] = (float)j / 18.0f;
			k++;
			//glNormal3fv(circle[i][j % 18]);

			//glNormal3fv(normalVec);
			//glTexCoord2f((float)i / 36.0f, (float)j / 18.0f);
			//glVertex3fv(circle[i][j % 18]);
			for (int k = 0; k < 3; k++)
			{
				normalVec[k] = circle[(i+1)%36][j % 18][k];
			}
			memcpy(points[k], normalVec, sizeof(point3));
			link[k][0] = (float)(i+1) / 36.0f;
			link[k][1] = (float)j / 18.0f;
			k++;
			//glNormal3fv(circle[(i + 1) % 36][j % 18]);
			//glNormal3fv(normalVec);
			//glTexCoord2f((float)(i + 1) / 36.0f, (float)j / 18.0f);
			//glVertex3fv(circle[(i + 1) % 36][j % 18]);
		}
	}

	model = new MODEL(size, points, points);
	model->setLink(size, link);
	delete[] points;
	delete[] link;
}