#pragma once

#ifndef _SCENEOBJECT_H
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Mesh*			_mesh;
	Texture2D*		_texture;
public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject();

	virtual void Update();
	virtual void Draw();
	virtual Vector3* GetPos();
	virtual void SetPos(Vector3 newPos);
	virtual void Keyboard();
};

#endif // !_SCENEOBJECT_H