#pragma once
#include<string>
#include"Physics.h"
#include"Texture.h"
#include"MODEL.h"
#include"Texture.h"
#include <Windows.h>
#include<GL/GL.h>
#include<GL/GLU.h>
#include<GL/glut.h>
typedef float point3[3];
typedef float Rotation[3];
typedef point3 Circle[36][18];
class Transform;
class Object;
class Collider;
class Vector3;
class MODEL;
class Texture;

using namespace std;
enum class ColliderType;

//면이 삼각형인지 사각형인지 정합니다.
enum class FaceType
{
	Triangle = 0,
	Rectangular,
	Line,
	Rect,
	Text
};

//오브젝트를 그리기위한 타입입니다. (삼각형 그리기와 사각형 그리기)
class Draw
{
protected:
	Object*  obj;

public:
	Draw();
	Draw(Object*);
	virtual void draw();

	Draw& operator = (const Draw &In) const;
};

class DrawLine : public Draw
{
private:
	Vector3 start;
	Vector3 end;
	point3 color;
public:
	DrawLine(Object* obj);
	void setStart(Vector3 start) ;
	void setEnd(Vector3 End) ;
	void setColor(const point3& color) ;

	virtual void draw() override;
};

class DrawTriangle : public Draw
{
public:
	DrawTriangle(Object*);
	void draw() override;
};

class DrawRectangular : public Draw
{
public:
	DrawRectangular(Object*);
	void draw() override;
};

class DrawRect : public Draw
{
public:
	DrawRect(Object*);
	void draw() override;
};

class DrawFont :public Draw
{
public:
	DrawFont(Object*);
	void draw() override;
};

// basic Object
class Object
{
	friend class ObjManager;
protected:
	int id;
	string name;
	Rotation rotation;
	void DrawFactory(FaceType);
	void setVertices(int size, point3* vertices, point3* vectors);
	bool isKinetic;
	Draw* Draw;
public:
	bool isPicked;
	Collider* collider;
	Transform * const transform;
	RectTransform* rect;
	Texture* texture;
	MODEL* model;

	// functions
	Object();
	Object(int ,point3*, point3*);
	Object(int, point3*, point3*, point3);
	Object(int ,point3*, point3*, FaceType);
	Object(int ,point3*, point3*, FaceType, point3);	
	Rotation* GetRotation();
	void setName(const string name);
	string getName() const;

	void draw();
	void move();

	void setModel(int size, point3* vertices, point3* NormalVec);

	void SetRotation(Rotation);
	void SetCollider(ColliderType type, float length, char index);

	virtual ~Object();
	virtual void picked();
	virtual void collide(Collider *collider);

	virtual void Start();
	virtual void Update();
	virtual void OnCollision(Collider* collider);

	void setKinetic(const bool isKinetic);
};

static class ObjManager
{
private:
	static int num;
	static Object* objects[100];
	static class ObjQueue
	{
	public:
		Object* objects[100];
		static int cursor;
		static int end;
		
		bool isEmpty() const;
		bool isFull() const;
		Object* pop();
		void push(Object* obj);
		
	} newObjects;

	static int available;


	void Draw(int id) const;
	//check collsiion
	bool CheckCollision(int id1, int id2) const;
	
	//is Arr full?
	bool checkArr();
public:
	~ObjManager();

	int addObj(Object*);
	void delObj(int);

	Object* const getObj(int id)const;
	
	void Selector() const;
	void Selector(int) const;
	void Loop(void) const;
	void draw(void) const;
}ObjManager;

class GUI : public Object
{
public:
	GUI();
};

void prepareVertex();
void prepareVertex(Circle);
void prepareVertex(Circle, point3);
void DrawVertex(Circle circle);

class Text :public  GUI
{
private:
public:
	static const int base;
	static const HWND hwnd;
	static const HDC hDC;
	int fontSize;
	point3 color;
	string text;
	int right;
	int up;
	Text();
};