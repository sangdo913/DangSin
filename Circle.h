#pragma once
#include"Object.h"
#include"���.h"


//class Test; //doing::start, doing::action, circle �������, ������, �Ҹ��� collide�� �Բ� ���� 
class CIRCLE : public Object
{
private:
	//float e; // ź�����
	void DrawVertex(Circle);
	void Draw();

public:
	//////////test
	//Test* test;
		///////
	point3 origin;
	point3 vector;
	point3* GetOrigin();
	point3* GetVector();
	void SetVector(point3);
	void SetOrigin(point3);

	CIRCLE();
	CIRCLE(point3);
	CIRCLE(point3, Rotation);
	~CIRCLE();
	virtual void collide(Collider *collider) override;

	virtual void OnCollision(Collider *collider) override;
	virtual void Start() override;
	virtual void Update() override;

	void setE(float e);
};