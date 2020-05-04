#pragma once

#ifndef _MESHLOADER_H
#include <Windows.h>
#include <gl/GL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Structures.h"
using namespace std;

namespace MeshLoader
{
	Mesh* Load(char* path);
	Mesh* LoadOBJ(char* path);
};

#endif // !_MESHLOADER_H