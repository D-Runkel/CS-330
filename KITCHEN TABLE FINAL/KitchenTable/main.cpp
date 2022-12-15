#include "global.h"
#include "cylinder.h"

GLFWwindow* window = nullptr;
Mesh coasterMesh1; //this complex object is a stack of coasters
Mesh coasterMesh2; // the second coaster
Mesh table;
Mesh ground;
Mesh tableLegs[4];
GLuint programId;
GLuint floorText;
GLuint tableText;
GLuint coasterTex;
GLuint glassText;
Mesh candle;

int main(int argc, char* argv[])
{
	if (!UInitialize(argc, argv, &window)) // if the window doesn't start properly, exit
	{
		return EXIT_FAILURE;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, p_key_callback);

	//TEXTURE CREATION
	const char* textFilename = "wood_floor.jpg";
	if (!UCreateTexture(textFilename, floorText, GL_MIRRORED_REPEAT))
	{
		std::cout << "Failed to load texture" << std::endl;
		return EXIT_FAILURE;
	}
	
	textFilename = "table_top.jpg";
	if (!UCreateTexture(textFilename, tableText, GL_REPEAT))
	{
		std::cout << "Failed to load texture" << std::endl;
		return EXIT_FAILURE;
	}
	
	textFilename = "coaster_texture.jpg";
	if (!UCreateTexture(textFilename, coasterTex, GL_CLAMP_TO_EDGE))
	{
		std::cout << "Failed to load texture" << std::endl;
		return EXIT_FAILURE;
	}

	textFilename = "glass.jpg";
	if (!UCreateTexture(textFilename, glassText, GL_REPEAT))
	{
		std::cout << "Failed to load texture" << std::endl;
		return EXIT_FAILURE;
	}

	glUseProgram(programId);
	glUniform1i(glGetUniformLocation(programId, "uTexture"), 0);
	glUniform1i(glGetUniformLocation(programId, "uTexture"), 0);
	glUniform1i(glGetUniformLocation(programId, "uTexture"), 0);

	ground.scale = glm::vec3(30.0f, 30.0f, 1.0f);
	ground.position = glm::vec3(0.0f,-3.0f,0.0f);
	ground.rotation = glm::rotate(1.571f, glm::vec3(1.0f, 0.0f, 0.0f));   //rotate plane 90 degrees
	
	//THE TABLE
	table.scale = glm::vec3(5.0f, .22f, 9.0f);
	table.position = glm::vec3(0.0f, -0.3f, -2.35f);

	tableLegs[0].position = glm::vec3(2.35f, -1.6f, 2.0f);
	tableLegs[0].scale = glm::vec3(0.25f, 2.7f, 0.25f);

	tableLegs[1].position = glm::vec3(-2.35f, -1.6f, 2.0f);
	tableLegs[1].scale = glm::vec3(0.25f, 2.7f, 0.25f);

	tableLegs[2].position = glm::vec3(2.35f, -1.6f, -6.75f);
	tableLegs[2].scale = glm::vec3(0.25f, 2.7f, 0.25f);

	tableLegs[3].position = glm::vec3(-2.35f, -1.6f, -6.75f);
	tableLegs[3].scale = glm::vec3(0.25f, 2.7f, 0.25f);



	//rotaions - the first coaster sits on the bottom of the second, the second is tilted 45 degrees
	coasterMesh1.rotation = glm::rotate(1.571f, glm::vec3(1.0f, 0.0f, 0.0f));
	coasterMesh2.rotation = glm::rotate(1.571f, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(0.7855f, glm::vec3(0.0f,0.0f,1.0f)); //looks to me like its 45 degrees

	//before making mesh we set scale and transformations
	coasterMesh1.scale = glm::vec3(1.0f,1.0f,0.1f); // thickness of .1 on z axis
	coasterMesh2.scale = glm::vec3(1.0f, 1.0f, 0.1f); // thickness of .1 on z axis

	//move coaster2 up the thickness of coaster 1
	coasterMesh1.position = glm::vec3(0.0f, -0.15f, 0.0f);
	coasterMesh2.position = glm::vec3(0.0f, -0.05f, 0.0f);

	//Candle
	candle.position = glm::vec3(0.0f, 0.30f, -1.5f); //behind coasters
	candle.scale = glm::vec3(0.5f, 1.0f, 0.5f);

	if (!UCreateShaderProgram(programId))
	{
		std::cout << "SHADER FAILED LOAD" << std::endl;
		return EXIT_FAILURE;
	}

	//assigning values to meshes
	UCreateCubeMesh(coasterMesh2);
	UCreateCubeMesh(table);
	UCreateCubeMesh(coasterMesh1);
	UCreateCubeMesh(tableLegs[0]);
	UCreateCubeMesh(tableLegs[1]);
	UCreateCubeMesh(tableLegs[2]);
	UCreateCubeMesh(tableLegs[3]);
	UCreateCubeMesh(candle);
	UCreatePlaneMesh(ground);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{

		//render loop

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //ONE CLEAR
		//update delta time with each frame
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessInput(window);

		// render our stuff
		//ground
		URender(ground, programId, &window, floorText, glm::vec2(3.0f,3.0f));

		//coasters
		URender(coasterMesh1,programId, &window,coasterTex, glm::vec2(1.0f, 1.0f));
		URender(coasterMesh2, programId, &window, coasterTex, glm::vec2(1.0f, 1.0f));
		//table stuff
		URender(table, programId, &window, tableText, glm::vec2(3.0f, 1.0f));
		URender(tableLegs[0], programId, &window, tableText, glm::vec2(3.0f, 1.0f));
		URender(tableLegs[1], programId, &window, tableText, glm::vec2(3.0f, 1.0f));
		URender(tableLegs[2], programId, &window, tableText, glm::vec2(3.0f, 1.0f));
		URender(tableLegs[3], programId, &window, tableText, glm::vec2(3.0f, 1.0f));

		//Candles
		URender(candle, programId, &window, glassText, glm::vec2(1.0f, 1.0f));
		//ONE SWAP
		glfwSwapBuffers(window); // Flips the the back buffer with the front buffer every frame.

		glfwPollEvents(); // see if anything was pressed
	}

	UDestroyMesh(coasterMesh1);
	UDestroyMesh(coasterMesh2);
	UDestroyShaderProgram(programId);
	UDestroyTexture(coasterTex);
	UDestroyTexture(floorText);
	UDestroyTexture(tableText);

	exit(EXIT_SUCCESS);

}