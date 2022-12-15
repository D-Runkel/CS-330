#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H
#define WINDOW_HEIGHT  600
#define WINDOW_WIDTH  800

#endif
#include <iostream>        
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//CAMERA GLOBALS -- needs to be reachable by any part of the program
const char* const WINDOW_TITLE = "Dustin Runkel - Kitchen Table";

//here I am telling the linker "Pick one definition for the variable (across all files) and use it"
__declspec(selectany) float CAMERA_BASE_SPEED = 3.0f;
__declspec(selectany) float lastX = WINDOW_WIDTH / 2;
__declspec(selectany) float lastY = WINDOW_HEIGHT / 2;
__declspec(selectany) float yaw = -90.0f;
__declspec(selectany) float pitch;
__declspec(selectany) bool firstMouse = true;
__declspec(selectany) float deltaTime = 0.0f;	// Time between current frame and last frame
__declspec(selectany) float lastFrame = 0.0f; // Time of last frame
__declspec(selectany) glm::vec3 cameraPos = glm::vec3(0.0f, 3.0f, 4.0f);
__declspec(selectany) glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
__declspec(selectany) glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
__declspec(selectany) glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
__declspec(selectany) glm::vec3 cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f,1.0f,0.0f), cameraDirection));
__declspec(selectany) glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
__declspec(selectany) bool ortho = false;
__declspec(selectany) glm::vec3 lightPos = glm::vec3(-2.0f, 3.0f, 0.0f); //make light sit directly above
__declspec(selectany) glm::vec3 gLightColor(1.0f, 1.0f, 1.0f); //bright white light
__declspec(selectany) glm::vec3 gLightScale(1.0f);


struct Mesh
{
	GLuint vao;
	GLuint vbos[2];
	GLuint nVerts;
	GLuint indices;
	glm::vec3 scale = glm::vec3( 1.0f, 1.0f, 1.0f ); // x, y, z (object full scale at start)
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); //x, y, z (object defaults to origin)
	glm::mat4 rotation = glm::rotate(0.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // I'm allowing the mesh to store this
};

void UCreateCubeMesh(Mesh& mesh);
void UDestroyMesh(Mesh& mesh);
bool UCreateShaderProgram(GLuint& programId);
void UDestroyShaderProgram(GLuint programId);
void URender(Mesh& mesh, GLuint ProgramId, GLFWwindow** window, GLuint textureId, glm::vec2 UVscale);
void ProcessInput(GLFWwindow* window);
bool UInitialize(int argc, char* argv[], GLFWwindow** window);
void UDestroyShaderProgram(GLuint programId);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void UCreatePlaneMesh(Mesh& mesh);
void p_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void flipImageVertically(unsigned char* image, int width, int height, int channels);
bool UCreateTexture(const char* filename, GLuint& textureId, GLint wrap);
void UDestroyTexture(GLuint& textureId);