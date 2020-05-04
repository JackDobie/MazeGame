#pragma once

struct Vector2
{
	float	x, y;
};
struct Vector3
{
	float	x, y, z;
};
struct Vector4
{
	float	x, y, z, w;
};
struct Camera
{
	Vector3 eye, centre, up;
};
struct Colour
{
	GLfloat r, g, b;
};
struct Vertex
{
	GLfloat x, y, z;
};
struct TexCoord
{
	GLfloat u, v;
};
struct Mesh
{
	Vertex*		Vertices;
	GLushort*	Indices;
	Vector3*	Normals;
	TexCoord*	TexCoords;
	int			VertexCount, NormalCount, IndexCount, TexCoordCount;
};
struct Lighting
{
	Vector4 Ambient, Diffuse, Specular;
};
struct Material
{
	Vector4	Ambient, Diffuse, Specular;
	GLfloat	Shininess;
};