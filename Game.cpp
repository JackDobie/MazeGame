#include "Game.h"


Game::Game(int argc, char* argv[])
{
	InitGL(argc, argv);
	InitObjects();
	InitLighting();

	glutMainLoop();
}

void Game::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Maze");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE); //sets to 60 fps (1000/60=16.6666)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800); //set the viewport to be the entire window
	gluPerspective(45, 1, 0.1, 1000); //set the perspective
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glCullFace(GL_BACK);
}
void Game::InitObjects()
{
	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 10.0f; camera->eye.z = 0.5f;
	camera->centre.x = 0.0f; camera->centre.y = 0.0f; camera->centre.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
	
	InitLevelMap();

	Mesh* cubeMeshOBJ = MeshLoader::LoadOBJ((char*)"Models/cube.obj");
	Mesh* mazeMeshOBJ = MeshLoader::LoadOBJ((char*)"Models/maze.obj");
	texture = new Texture2D();

	Objects[0] = new GameObject(cubeMeshOBJ, texture, 0, 0, 0, &deltaTime, levelMap);
	Objects[1] = new GameObject(mazeMeshOBJ, texture, 0, 0, 0, &deltaTime, levelMap);

	cameraZOffset = 0;
}
void Game::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.25f;
	_lightPosition->y = 0.25f;
	_lightPosition->z = 0.25f;
	_lightPosition->w = 0.25f;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2f;
	_lightData->Ambient.y = 0.2f;
	_lightData->Ambient.z = 0.2f;
	_lightData->Ambient.w = 1.0f;
	_lightData->Diffuse.x = 0.8f;
	_lightData->Diffuse.y = 0.8f;
	_lightData->Diffuse.z = 0.8f;
	_lightData->Diffuse.w = 1.0f;
	_lightData->Specular.x = 0.2f;
	_lightData->Specular.y = 0.2f;
	_lightData->Specular.z = 0.2f;
	_lightData->Specular.w = 1.0f;
}
void Game::InitLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1},
										{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
										{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1},
										{1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,1,1,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1},
										{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
										{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
										{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1},
										{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
	levelMap = new LevelMap(map);
}

Game::~Game()
{
	delete(camera);
	delete texture;
}

void Game::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	texture->Load((char*)"Images/brick.bmp", 256, 512); //problems changing between the two using glActiveTexture so I just load a new texture on draw
	Objects[0]->Draw();
	//texture->DeleteTextures(); //delete the old texture to avoid having hundreds of textures in memory
	texture->Load((char*)"Images/solid-colour.bmp", 128, 128);
	Objects[1]->Draw();
	texture->DeleteTextures();

	if (wonGame)
	{
		Vector3 v = { Objects[0]->GetPos()->x + 1, Objects[0]->GetPos()->y, Objects[0]->GetPos()->z - 1 };
		Colour c = { 0.0f, 0.8f, 1.0f };
		DrawString("You Win!", &v, &c);
	}
	
	glFlush();
	glutSwapBuffers();
}

void Game::Update()
{
	glLoadIdentity();

	camera->centre = Vector3{ Objects[0]->GetPos()->x,Objects[0]->GetPos()->y + (wonGame ? cameraZOffset : 0), Objects[0]->GetPos()->z - (wonGame ? cameraZOffset += 0.08f : 0) };
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->centre.x, camera->centre.y, camera->centre.z, camera->up.x, camera->up.y, camera->up.z);

	glutPostRedisplay();

	if (Objects[0]->GetPos()->z < -18.0f && !wonGame) //if the player escapes the maze
	{
		wonGame = true;
		glutTimerFunc(4000, GLUTCallbacks::Restart, NULL); //set a timer before restarting the game
	}

	if (!wonGame)
		Keyboard();

	for (int i = 0; i < 2; i++)
	{
		Objects[i]->Update();
	}

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	Sleep(5);
}

void Game::Keyboard()
{
	if(Objects[0] != nullptr)
		Objects[0]->Keyboard();
}

void Game::DrawString(const char* text, Vector3* position, Colour* colour)
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glColor3f(colour->r, colour->g, colour->b);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)text);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void Game::Restart() //requires int and static to be used as a callback for glutTimerFunc
{
	wonGame = false;
	Objects[0]->SetPos({ 0, 0, 0 });
	cameraZOffset = 0;
}