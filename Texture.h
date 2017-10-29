#pragma once
#include<iostream>
#include <string>

using namespace std;

class Texture
{
private:
	unsigned int texID;
	int w, h, format;
	unsigned char* image;
public:
	//void loadTexture(std::string path, int w, int h, int format);
	const unsigned int getTexID() const;
	const unsigned char* getImage() const;

	Texture();
	Texture(std::string path, int w, int h, int format);
	Texture(unsigned char* image, int w, int h, int format);
	~Texture();
};