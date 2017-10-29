#pragma once

class Transform;

class Vector3;

class Camera
{
protected:
	int viewPort[4];
	double projection[16];
	double modelView[16];
public:


	Transform *const transform;

	Camera();
	Camera(Vector3 position);
	~Camera();

	void rotate(float angle, float);
	void goLeft();
	void ZoomIn();
	void ZoomOut();
	void goRight();
	void goUp();
	void goDown();

	void setProjection(const double * const projection);
	void setmodelView(const double * const modelView);
	void setviewPort(const int * const viewPort);

	void getProjection(double projection[16]) const;
	void getModelView(double modelView[16]) const;
	void getviewPort(int viewPort[4]) const;
	const float cameraSpeed = 10.f;

	void resetRotation();
};

class MainCamera : public Camera
{
private:
	MainCamera();
	MainCamera(Vector3);

	static class Singleton
	{
	private:
	public:
		static MainCamera *Instance;

		~Singleton()
		{
			delete Instance;
		}
	}Singleton;

public:
	~MainCamera();

	static MainCamera* getInstance();
	static void ToGlobal(float &x, float &y, float &z);
	static void ToGlobal(double &x, double &y);
	static void ToGlobal(int &x, int &y);
};
