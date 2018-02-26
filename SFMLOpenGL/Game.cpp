#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube Vertex and Fragment Shaders")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
} VertexStruct;

VertexStruct m_vertex[36]; //Struct Declaration
GLubyte triangles[36];

/* Variable to hold the VBO identifier and shader data */
GLuint	index, //Index to draw
		vsid, //Vertex Shader ID
		fsid, //Fragment Shader ID
		progID, //Program ID
		vao = 0, //Vertex Array ID
		vbo[1], // Vertex Buffer ID
		positionID, //Position ID
		colorID; // Color ID


void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	arraySetup();//Sets up the transformable Vertexs
	updateVertices();//Sets up the Vertex Locations
	setUpColour();//Sets up the Vertex colours

	/* Vertices counter-clockwise winding */
	//m_vertex[0].coordinate[0] = -0.5f;
	//m_vertex[0].coordinate[1] = -0.5f;
	//m_vertex[0].coordinate[2] = 0.0f;

	//m_vertex[1].coordinate[0] = -0.5f;
	//m_vertex[1].coordinate[1] = 0.5f;
	//m_vertex[1].coordinate[2] = 0.0f;

	//m_vertex[2].coordinate[0] = 0.5f;
	//m_vertex[2].coordinate[1] = 0.5f;
	//m_vertex[2].coordinate[2] = 0.0f;

	//m_vertex[0].color[0] = 0.0f;
	//m_vertex[0].color[1] = 0.0f;
	//m_vertex[0].color[2] = 0.0f;
	//m_vertex[0].color[3] = 1.0f;

	//m_vertex[1].color[0] = 0.0f;
	//m_vertex[1].color[1] = 0.0f;
	//m_vertex[1].color[2] = 0.0f;
	//m_vertex[1].color[3] = 1.0f;

	//m_vertex[2].color[0] = 0.0f;
	//m_vertex[2].color[1] = 0.0f;
	//m_vertex[2].color[2] = 0.0f;
	//m_vertex[2].color[3] = 1.0f;

	/*Index of Poly / Triangle to Draw */
	for (int index = 0; index < 36; index++)
	{
		triangles[index] = index;
	}

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexStruct) * 36, m_vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader which would normally be loaded from an external file */
	const char* vs_src = "#version 400\n\r"
		"in vec4 sv_position;"
		"in vec4 sv_color;"
		"out vec4 color;"
		"void main() {"
		"	color = sv_color;"
		"	gl_Position = sv_position;"
		"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	const char* fs_src = "#version 400\n\r"
		"in vec4 color;"
		"out vec4 fColor;"
		"void main() {"
		"	fColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);"
		"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	// Find variables in the shader
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//Rotates Up around X axis
	{
		m_changed = true;
		m_Matrix = m_Matrix.RotationX(.01);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//Rotates Down around X axis
	{
		m_changed = true;
		m_Matrix = m_Matrix.RotationX(-.01);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//Rotates Right around Y Axis
	{
		m_changed = true;
		m_Matrix = m_Matrix.RotationY(.01);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//Rotates Left around Y Axis
	{
		m_changed = true;
		m_Matrix = m_Matrix.RotationY(-.01);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))//Rotates Right around the Z Axis
	{
		m_changed = true;
		m_Matrix = m_Matrix.RotationZ(.01);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))//Rotates Left around the Z Axis
	{
		m_changed = true;
		m_Matrix = m_Matrix.RotationZ(-.01);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//Moves Right
	{
		m_changed = true;
		m_Matrix = m_Matrix.Translate(0.001, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))//Moves Left
	{
		m_changed = true;
		m_Matrix = m_Matrix.Translate(-0.001, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))//Scales Down
	{
		m_changed = true;
		m_Matrix = m_Matrix.Scale3D(99.95);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))//Scales Up
	{
		m_changed = true;
		m_Matrix = m_Matrix.Scale3D(100.05);
	}

	if (m_changed == true)//If something has needs to be changed the bool is reset and the vertices are transformed by the matrix
	{
		m_changed = false;
		transformVertices();
	}
	updateVertices();//Updates all the Vertices

	////Change vertex data
	//m_vertex[0].coordinate[0] += -0.0001f;
	//m_vertex[0].coordinate[1] += -0.0001f;
	//m_vertex[0].coordinate[2] += -0.0001f;

	//m_vertex[1].coordinate[0] += -0.0001f;
	//m_vertex[1].coordinate[1] += -0.0001f;
	//m_vertex[1].coordinate[2] += -0.0001f;

	//m_vertex[2].coordinate[0] += -0.0001f;
	//m_vertex[2].coordinate[1] += -0.0001f;
	//m_vertex[2].coordinate[2] += -0.0001f;

#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexStruct) * 36, m_vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStruct), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(VertexStruct), 0);

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
}



void Game::setUpColour()
{
	int triangleTracker = 0;
	for (int i = 0; i < 36; i++)//For all the vertexes
	{
		if (i != 0 && i % 6 == 0)//Increase the colour count once the current side is finished
		{
			index += 1;
		}
		m_vertex[i].color[0] = m_colourArray[index].x;
		m_vertex[i].color[1] = m_colourArray[index].y;
		m_vertex[i].color[2] = m_colourArray[index].z;
	}
}

void Game::arraySetup()
{
	m_transformableVertex[0] = MyVector3(0.25, 0.25, -0.1);//Front Side Top Right Corner
	m_transformableVertex[1] = MyVector3(-0.25, 0.25, -0.1);//Front Side Bottom Right Corner
	m_transformableVertex[2] = MyVector3(-0.25, -0.25, -0.1);//Front Side Bottom Left Corner
	m_transformableVertex[3] = MyVector3(0.25, -0.25, -0.1); //Front Side Top Left Corner

	m_transformableVertex[4] = MyVector3(0.25, 0.25, -0.5);//Back Side Top Right Corner
	m_transformableVertex[5] = MyVector3(-0.25, 0.25, -0.5);//Back Side Bottom Right Corner
	m_transformableVertex[6] = MyVector3(-0.25, -0.25, -0.5);//Back Side Top Left Corner
	m_transformableVertex[7] = MyVector3(0.25, -0.25, -0.5);//Back Side Bottom Left Corner
}

void Game::updateVertices()
{
	int temptIndex = 0;
	for (int i = 0; i < 8; i++)//Sets the current Corner Vectors into an array of doubles.
	{
		temptIndex = i * 3;
		m_vertexArray[temptIndex] = m_transformableVertex[i].getX();//Takes the transformable Vectors and turns them into 3 double values
		m_vertexArray[temptIndex + 1] = m_transformableVertex[i].getY();
		m_vertexArray[temptIndex + 2] = m_transformableVertex[i].getZ();
	}
	temptIndex = 0;
	for (int i = 0; i < 36; i++)//Sets the doubles values to the correct vertex.
	{
		m_vertex[i].coordinate[0] = m_vertexArray[vertex_index[i] * 3];//The Correct values are given to the correct vertex using the Vertex_index
		m_vertex[i].coordinate[1] = m_vertexArray[vertex_index[i] * 3 + 1];
		m_vertex[i].coordinate[2] = m_vertexArray[vertex_index[i] * 3 + 2];
	}

}

void Game::transformVertices()
{
	for (int i = 0; i < 8; i++)
	{
		m_transformableVertex[i] = m_transformableVertex[i] * m_Matrix;//Applies the transformation matrix to all transformable Vertices
	}
}

