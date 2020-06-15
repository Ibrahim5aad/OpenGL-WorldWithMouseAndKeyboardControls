#define _USE_MATH_DEFINES
#include <iostream>
#include <gl/glew/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include<gl\glm\glm.hpp>
#include<gl\glm\gtc\type_ptr.hpp>
#include<gl\glm\gtx\transform.hpp>
#include<vector>
#include "camera.h"
#include "vertex.h"
#include "Cube.h"
#include "Sphere.h"
#include "Quad.h"
#include <SOIL.h>

using namespace std;
using namespace glm;


GLuint InitShader(const char* vertex_shader_file_name, const char* fragment_shader_file_name);


const GLint WIDTH = 1000, HEIGHT = 800;
GLuint VBO, FBO, RBO, program1, program2, skyboxProgramId, IBO, transMatId, TextureId;
GLuint modelMatLoc, viewMatLoc, projMatLoc, cameraPosLoc, MVPMatLoc;
GLuint refractionProgramId, reflectionProgramId, postprocessingProgramId;
GLuint tex1, tex2, skyboxTextureId, pptext;
GLuint quadVBO;
Camera camera;
vec3 camPos;
float theta = 0;


void CompileShader1()
{
	program1 = InitShader("shaders/VS.glsl", "shaders/FS.glsl");
	skyboxProgramId = InitShader("shaders/VSCM.glsl", "shaders/FSCM.glsl");
	reflectionProgramId = InitShader("shaders/VSref.glsl", "shaders/FSreflection.glsl");
	postprocessingProgramId = InitShader("shaders/VSpp.glsl","shaders/FSpp.glsl");
	glUseProgram(program1);

}


void BindTextures(GLuint text) {

	if (text == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	else {

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glBindTexture(GL_TEXTURE_2D, text);

	}

}

void CreateCubeMap()
{
	string cub_maps[6] = { "skybox2\\right.jpg",
		"skybox2\\left.jpg",
		"skybox2\\top.jpg",
		"skybox2\\bottom.jpg",
		"skybox2\\front.jpg",
		"skybox2\\back.jpg" };

	glGenTextures(1, &skyboxTextureId);
	sf::Image img;

	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureId);
	for (GLuint i = 0; i < 6; i++)
	{
		img.loadFromFile(cub_maps[i]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CreateRenderBuffer()
{
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT); // Use a single renderbuffer object for both a depth AND stencil buffer.
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);



	glGenTextures(1, &pptext);
	glBindTexture(GL_TEXTURE_2D, pptext);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pptext, 0);

}

int Init()
{
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		cout << "Error";
		getchar();
		return 1;
	}
	else
	{
		if (GLEW_VERSION_3_0)
			cout << "Driver support OpenGL 3.0\nDetails:\n";
	}
	cout << "\tUsing glew " << glewGetString(GLEW_VERSION) << endl;
	cout << "\tVendor: " << glGetString(GL_VENDOR) << endl;
	cout << "\tRenderer: " << glGetString(GL_RENDERER) << endl;
	cout << "\tVersion: " << glGetString(GL_VERSION) << endl;
	cout << "\tGLSL:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	camera = Camera(glm::vec3(-5.f, 0.f, 5.f), 5.f, 5.f);

	CompileShader1();


	tex1 = SOIL_load_OGL_texture
	(
		"container2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	tex2 = SOIL_load_OGL_texture
	(
		"ground-texture.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	glGenBuffers(1, &transMatId);
	glGenBuffers(1, &VBO);

	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	
	CreateRenderBuffer();

	CreateCubeMap();

	glClearColor(0.372549, 0.623529, 0.623529, 1);

	glEnable(GL_DEPTH_TEST);

	return 0;

}

void Update()
{
	theta += 0.001f;
}


void Render()
{

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	//glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	mat4 viewMat = camera.LookAtMat();
	mat4 projMat = camera.ProjectionMat();
	vec3 camPos = camera.Position;

	viewMatLoc = glGetUniformLocation(program1, "viewMat");
	projMatLoc = glGetUniformLocation(program1, "projMat");
	cameraPosLoc = glGetUniformLocation(program1, "camPos");
	modelMatLoc = glGetUniformLocation(program1, "modMat");
	MVPMatLoc = glGetUniformLocation(skyboxProgramId, "mvp_mat");


	//Skybox 
	glDepthMask(GL_FALSE); // <== Disable Depth Mask

	glUseProgram(skyboxProgramId);

	Cube::CreateCube();
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureId);
	glm::mat4 ModelMat = glm::translate(glm::vec3(0, 0, -3)) *
					     glm::scale(glm::vec3(50.f, 50.f, 50.f));
	glm::mat4 MVPMat = projMat * viewMat * ModelMat;
	glUniformMatrix4fv(MVPMatLoc, 1, GL_FALSE, glm::value_ptr(MVPMat));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDepthMask(GL_TRUE);  // <== Enable Depth Mask


	glUseProgram(program1);

	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
	glUniform3fv(cameraPosLoc, 1, &camPos[0]);
	
	//Ground

	BindTextures(tex2);
	ModelMat = glm::translate(glm::vec3(0.f, -0.8f, 0.f)) * glm::scale(glm::vec3(20.f, 0.3f, 20.f));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	Cube::CreateCube();
	glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());
	
	
	//Cube Instances (glDrawArrayInstanced)
	BindTextures(tex1);
	ModelMat = mat4(1);
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));

	glBindBuffer(GL_ARRAY_BUFFER, transMatId);
	Cube::CubeTransformationMatsData();
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, sizeof(modelMats) / sizeof(glm::mat4));


	//Reflective Sphere
	viewMatLoc = glGetUniformLocation(reflectionProgramId, "viewMat");
	projMatLoc = glGetUniformLocation(reflectionProgramId, "projMat");
	cameraPosLoc = glGetUniformLocation(reflectionProgramId, "camPos");
	modelMatLoc = glGetUniformLocation(reflectionProgramId, "modMat");
	glUseProgram(reflectionProgramId);

	ModelMat = glm::translate(glm::vec3(cos(10*theta) * 6, 3, sin(10 * theta)*6)) *
		       glm::rotate(theta * 180 / 3.14f, glm::vec3(1, 1, 1)) *
		       glm::scale(glm::vec3(1, 1, 1));

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
	glUniform3fv(cameraPosLoc, 1, &camPos[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	Sphere::CreateSphere(5);
	glDrawArrays(GL_TRIANGLES, 0, sphere_vertices.size());


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(postprocessingProgramId);
	Quad::QuadData();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pptext);
	glDrawArrays(GL_TRIANGLES, 0, 6);


}

int main()
{

	sf::ContextSettings context;
	context.depthBits = 24;
	sf::Window window(sf::VideoMode(WIDTH, HEIGHT), "   ", sf::Style::Close, context);

	if (Init()) return 1;


	bool _firstMove = true;
	glm::vec2 _lastPos;
	const float cameraSpeed = 0.1f;
	const float sensitivity = 0.25f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::Closed:
				window.close();
				break;


			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::W:
					camera.Position += glm::vec3(camera.Front.x, 0, camera.Front.z) * cameraSpeed;
					break;
				case sf::Keyboard::S:
					camera.Position -= glm::vec3(camera.Front.x, 0, camera.Front.z) * cameraSpeed;
					break;
				case sf::Keyboard::A:
					camera.Position -= camera.Right * cameraSpeed;
					break;
				case sf::Keyboard::D:
					camera.Position += camera.Right * cameraSpeed;
					break;

				case sf::Keyboard::Escape:
					window.close();
					break;
				}


			case sf::Event::MouseMoved:
				if (_firstMove) {
					_lastPos = glm::vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					_firstMove = false;
				}
				else {
					float deltaX = float(sf::Mouse::getPosition(window).x) - _lastPos.x;
					float deltaY = float(sf::Mouse::getPosition(window).y) - _lastPos.y;
					_lastPos = glm::vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					camera.UpdateYaw(deltaX * sensitivity);
					camera.UpdatePitch(deltaY * sensitivity);
				}
				break;

			}

		}

		Update();
		Render();
		window.display();
	}
	return 0;
}