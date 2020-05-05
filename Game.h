#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "MeshLoader.h"
#include "SceneObject.h"
#include "GameObject.h"
#include "LevelMap.h"

#define REFRESHRATE 16

class Game
{
public:
	Game(int argc, char* argv[]);
	~Game(void);

	void Display();
	void Update();
	float deltaTime;

	void InitGL(int argc, char* argv[]);
	void InitObjects();
	void InitLighting();
	void InitLevelMap();

	void Keyboard();
	void DrawString(const char* text, Vector3* position, Colour* colour);

	bool wonGame = false;
	void Restart();

	Texture2D* texture;
private:
	Camera*			camera;
	Vector4*		_lightPosition;
	Lighting*		_lightData;
	LevelMap*		levelMap;
	SceneObject*	Objects[2];
	float			cameraZOffset;
};

