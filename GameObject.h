#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GL/freeglut_ext.h"
#include "GL/freeglut_std.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Structures.h"
#include "SceneObject.h"
#include "Texture2D.h"
#include "LevelMap.h"
using namespace std;

class GameObject : public SceneObject
{
private:
	static int	numVertices,
				numColours,
				numIndices;

	GLfloat		_rotation;
	Vector3		_position;
	Material*	_material;

	float		moveSpeed = 0.01f;
	float*		_deltaTime;
	float		playerHeight = 1, playerWidth = 1;
	bool		CheckCollision(int direction);
	void		CreateMaterial();
	LevelMap*	currentLevelMap;
	bool		wonGame = false;
public:
	GameObject(Mesh* mesh, Texture2D* texture, float x, float y, float z, float* deltaTime, LevelMap* levelMap);
	~GameObject();

	void Draw();
	void Update();
	Vector3* GetPos();
	void SetPos(Vector3 newPos);

	void Keyboard();
};