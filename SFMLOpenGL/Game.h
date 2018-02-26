#ifndef GAME_H
#define GAME_H

#include <Debug.h>

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <Vector3.h>
#include <Matrix3.h>

using namespace std;
using namespace sf;
//using namespace gpp;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	void setUpColour();
	bool m_changed;
	sf::Vector3f m_colourArray[6] = {
		{ 1,0,0 },//RED
	{ 0,1,0 },//GREEN
	{ 0,0,1 },//BLUE
	{ 1,1,0 },//YELLOW
	{ 0,1,1 },//AQUA
	{ 1,0,1 } };//PINK
	float m_vertexArray[24];//Array to hold the co ordinates in a format Open GL can use
	unsigned int vertex_index[36] = {
		0, 1, 2, //Triangle 0 Side 1
		0, 2, 3,//Triangle 1 Side 1
		4, 5, 6,//Triangle 0 Side 2
		4, 6, 7,//Triangle 1 Side 2
		4, 5, 1, //Triangle 0 Side 3
		4, 1, 0,//Triangle 1 Side 3
		7, 6, 2, //Triangle 0 Side 4
		7, 2, 3,//Triangle 1 Side 4
		4, 0, 3, //Triangle 0 Side 5
		4, 3, 7,//Triangle 1 Side 5
		1, 5, 6,//Triangle 0 Side 6
		1, 6, 2 //Triangle 1 Side 6
	};

	Matrix3 m_Matrix;//Transformation Matrix
	void arraySetup();//Sets up the Tranformable Array
	void updateVertices();//Applies current co ordinates to the Open GL Float Array 
	void transformVertices();//Transforms Vertices by tranformation matrix


	MyVector3 m_transformableVertex[8];//Array to Hold transformable values for Array
	Clock clock;
	Time elapsed;

	float rotationAngle = 0.0f;
};

#endif