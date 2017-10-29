#pragma once
#pragma comment(lib,"glut32.lib")
#include<iostream>
#include<math.h>
#include<stdio.h>
#include<math.h>

#include <Windows.h>
#include<GL/GL.h>
#include<GL/GLU.h>
#include<gl/glut.h>

#include"Matrix.h"
#include"Camera.h"
#include"Physics.h"
#include"Collider.h"
#include"state.h"
#include"input.h"
#include"Object.h"
#include "System.h"
#include"Wall.h"
#include"Circle.h"
#include"Texture.h"
#include"Line.h"

#define PI 3.141592
#define SELECT_BUF_SIZE		512*512*3

//delegate
typedef void (SCRIPT) (void);

void SetLight();
void DrawAxis();
void LoadTexture();

void YRotate(point3 &point, float theta);
void ZRotate(point3 &point, float theta);

void orientMe(float ang);
void moveMeFlat(int direction);

void SetupRC();