#pragma once

#ifndef _TEXTURE2D_H
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include <iostream>
#include <fstream>
#include "Structures.h"
using namespace std;

class Texture2D
{
private:
	GLuint	_ID;
	int		_width,
			_height;
public:
	Texture2D();
	~Texture2D();

	bool Load(char* path, int width, int height);
	void DeleteTextures();

	GLuint GetID() const { return _ID; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }
};

#endif // !_TEXTURE2D_H