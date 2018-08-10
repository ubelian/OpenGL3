#pragma once
#ifndef OGLRENDERER_H
#define OGLRENDERER_H

#define GLEW_STATIC
#include "c:/LIBRARY/GLEW/include/GL/glew.h"

#include "c:/LIBRARY/GLFW/glfw3.h"

#include "c:/LIBRARY/glm/glm/glm.hpp"
#include "c:/LIBRARY/glm/glm/gtc/type_ptr.hpp"
#include "c:/LIBRARY/glm/glm/mat4x4.hpp"

#include "iostream"
#include <vector>

#include "Shader.h"
#include "VBO.h"
#include "MVPmatrix.h"
#include "OGLobject.h"

#include "DebugDefinies.h"

struct ObjectCreateInfo {
	const GLenum mode = GL_TRIANGLES;
	const char *vertexPath = 0;
	const char *fragmentPath = 0;
	GLfloat *vertices = 0;
	size_t verticesSize = 0;
	GLuint *indices = nullptr;
	size_t indicesSize = 0;
	const char *picturePath = 0;
	GLfloat *texCoord = 0;
	size_t texCoordSize = 0;
};

class OglRenderer{
private:
	//������� ����, ��� ������ � ������
	int windowWidth, windowHeight;
	//��������� ����
	GLFWwindow *window;
	//�������������� �������
	std::vector<OGLobject> renderedObjects;
	//������ �� ���������
	Shader defaultShader;
	//���� ���� �� ���������
	glm::vec4 clearColor;

public:
	/**/
	bool Timer();
	/**/
	void setClearColor(glm::vec4 _clearColor);
	/*������ ������� ������ �� ������*/
	OGLobject &getCurrentObject(size_t index = 0);
	/*��� ��������������� �������. �������� GL_TRIANGLES*/
	GLenum mode;
	/*������ ���������*/
	void run();
	/*�������� �������� ��������� ���� �������*/
	void addRectangle(GLfloat _x1, GLfloat _y1, GLfloat _x2, GLfloat _y2, const char *texture = nullptr);
	/*�������� �������� ��������� ���� �����������*/
	void addTriangle(GLfloat _x1, GLfloat _y1, GLfloat _x2, GLfloat _y2, GLfloat _x3, GLfloat _y3, const char *texture = nullptr);
	/*������� ������ ������� ��� ������� �� ���������*/
	void push(ObjectCreateInfo &createInfo);
	//������ ���������� ����
	GLFWwindow **getWindowHandle();
	/*������������ � �����������*/
	OglRenderer();
	~OglRenderer();
};



















#endif

