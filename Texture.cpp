#include"Texture.h"
#include<string>
#include <Windows.h>
#include<GL/GL.h>
#include<GL/GLU.h>
#include<GL/glut.h>

//
//void Texture::loadTexture(std::string path, int w, int h , int format)
//{
//	if (image) delete[] image;
//	image = new unsigned char[w*h*format];
//
//	this->w = w;
//	this->h = h;
//	this->format = format;
//
//	FILE* fp;
//
//	fopen_s(&fp, path.data(), "rb");
//	fread(image, w*h, format, fp);
//	fclose(fp);
//
//	glGenTextures(1, &texID);
//
//	glBindTexture(GL_TEXTURE_2D, texID);
//	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h,
//		0, GL_RGB, GL_UNSIGNED_BYTE, image);
//
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//}

const unsigned int Texture::getTexID() const
{
	return texID;
}

const unsigned char * Texture::getImage() const
{
	return image;
}

Texture::Texture()
{
	image = nullptr;
}

Texture::Texture(std::string path, int w, int h, int format)
{

	if (image) delete[] image;
	image = new unsigned char[w*h*format];

	this->w = w;
	this->h = h;
	this->format = format;

	FILE* fp;

	fopen_s(&fp, path.data(), "rb");
	fread(image, w*h, format, fp);
	fclose(fp);

	glGenTextures(1, &texID);

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h,
		0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

Texture::Texture(unsigned char * image, int w, int h, int format)
{
	if (this->image) delete[] this->image;
	this->image = new unsigned char[w*h*format];

	memcpy(this->image, image, sizeof(unsigned char)* w*h*format);
	this->w = w;
	this->h = h;
	this->format = format;

	glGenTextures(1, &texID);

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h,
		0, GL_RGB, GL_UNSIGNED_BYTE, this->image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

Texture::~Texture()
{
	if (image) delete[]image;
	glDeleteTextures(1, &texID);
}
