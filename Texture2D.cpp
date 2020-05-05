#include "Texture2D.h"

Texture2D::Texture2D()
{
	_width = NULL; _height = NULL; _ID = NULL;
}
Texture2D::~Texture2D()
{
	glDeleteTextures(_ID, &_ID);
	//glDeleteTextures
}

void Texture2D::DeleteTextures()
{
	glDeleteTextures(1, &_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData;
	int fileSize;
	ifstream inFile;

	_width = width;
	_height = height;

	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end); //seek to end of file
	fileSize = (int)inFile.tellg(); //get current position in file, giving the file size as end of file
	tempTextureData = new char[fileSize]; //new array to store data
	inFile.seekg(0, ios::beg); //seek to beginning of file
	inFile.read(tempTextureData, fileSize); //read all data in one go
	inFile.close(); //close file

	//cout << path << " loaded." << endl;

	glGenTextures(1, &_ID); //get next texture ID
	glBindTexture(GL_TEXTURE_2D, _ID); //bind the texture to the ID
	//cout << _ID << endl;

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete[] tempTextureData; //clear up the data
	return true;
}