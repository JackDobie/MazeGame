#include "GameObject.h"

GameObject::GameObject(Mesh* mesh, Texture2D* texture, float x, float y, float z, float* deltaTime, LevelMap* levelMap) : SceneObject(mesh, texture)
{
	_material = nullptr;
	_rotation = 0;
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_deltaTime = deltaTime;
	currentLevelMap = levelMap;
	CreateMaterial();
}

GameObject::~GameObject()
{
	_material = NULL;
	delete _material;
	currentLevelMap = NULL;
	delete currentLevelMap;
}

void GameObject::Update()
{
	if (_position.z < -18.0f)
	{
		wonGame = true;
		_position.z -= (moveSpeed * 1.5f) * *_deltaTime;
	}
}

void GameObject::Draw()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialfv(GL_FRONT, GL_SHININESS, &(_material->Shininess));
	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation, -1.0f, 0.0f, 0.0f);

	if (_mesh->Vertices != nullptr && _mesh->Indices != nullptr && _mesh->Normals != nullptr)
	{
		glBindTexture(GL_TEXTURE, _texture->GetID());

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		//glColorPointer(3, GL_FLOAT, 0, _mesh->Colours);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);

		//glPushMatrix();
		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void GameObject::CreateMaterial()
{
	_material = new Material();
	_material->Ambient.x = 1.0f;
	_material->Ambient.y = 1.0f;
	_material->Ambient.z = 1.0f;
	_material->Ambient.w = 1.0f;

	_material->Diffuse.x = 0.05f;
	_material->Diffuse.y = 0.05f;
	_material->Diffuse.z = 0.05f;
	_material->Diffuse.w = 1.0f;

	_material->Specular.x = 0.05f;
	_material->Specular.y = 0.05f;
	_material->Specular.z = 0.05f;
	_material->Specular.w = 0.05f;

	_material->Shininess = 100.0f;
}


void GameObject::Keyboard()
{
	//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate
	if (GetAsyncKeyState(0x57)) //w pressed down
	{
		if (!CheckCollision(0))
			_position.z -= moveSpeed * *_deltaTime;
	}
	else if (GetAsyncKeyState(0x53)) //s pressed down
	{
		if (!CheckCollision(1))
			_position.z += moveSpeed * *_deltaTime;
	}
	if (GetAsyncKeyState(0x41)) //a pressed down
	{
		if (!CheckCollision(2))
			_position.x -= moveSpeed * *_deltaTime;
	}
	else if (GetAsyncKeyState(0x44)) //d pressed down
	{
		if (!CheckCollision(3))
			_position.x += moveSpeed * *_deltaTime;
	}
}

Vector3* GameObject::GetPos()
{
	return &_position;
}
void GameObject::SetPos(Vector3 newPos)
{
	_position = newPos;
}

//UP: 0
//DOWN: 1
//LEFT: 2
//RIGHT: 3
bool GameObject::CheckCollision(int direction)
{
	enum directionEnum
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT
	};

	Vector2 position{ _position.x + 18.0f, _position.z + 18.0f }; //set player at the centre of the maze

	switch (direction)
	{
	case UP:
		if (currentLevelMap->GetTileAt(position.y - (playerHeight / 2), position.x) == 1 ||
			currentLevelMap->GetTileAt(position.y - (playerHeight / 2), position.x + (playerWidth / 2)) == 1 ||
			currentLevelMap->GetTileAt(position.y - (playerHeight / 2), position.x - (playerWidth / 2)) == 1)
			return true;
		else
			return false;
		break;
	case DOWN:
		if (currentLevelMap->GetTileAt(position.y + (playerHeight / 2), position.x) == 1 ||
			currentLevelMap->GetTileAt(position.y + (playerHeight / 2), position.x + (playerWidth / 2)) == 1 ||
			currentLevelMap->GetTileAt(position.y + (playerHeight / 2), position.x - (playerWidth / 2)) == 1)
			return true;
		else
			return false;
		break;
	case LEFT:
		if (currentLevelMap->GetTileAt(position.y, position.x - (playerWidth / 2)) == 1 ||
			currentLevelMap->GetTileAt(position.y + (playerHeight / 2), position.x - (playerWidth / 2)) == 1 ||
			currentLevelMap->GetTileAt(position.y - (playerHeight / 2), position.x - (playerWidth / 2)) == 1)
			return true;
		else
			return false;
		break;
	case RIGHT:
		if (currentLevelMap->GetTileAt(position.y, position.x + (playerWidth / 2)) == 1 ||
			currentLevelMap->GetTileAt(position.y + (playerHeight / 2), position.x + (playerWidth / 2)) == 1 ||
			currentLevelMap->GetTileAt(position.y - (playerHeight / 2), position.x + (playerWidth / 2)) == 1)
			return true;
		else
			return false;
		break;
	default:
		cerr << "Error: Tried to check collision for a direction out of range 0-3" << endl;
		return false;
		break;
	}
}