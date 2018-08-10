#pragma once
#include<vector>
#include<iostream>
#include "c:/LIBRARY/glm/glm/glm.hpp"
#include "c:/LIBRARY/GLEW/include/GL/glew.h"

#include"DebugDefinies.h"

class VBO{
private:
	static glm::vec3 defaultColor;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> colors;
	std::vector<GLfloat> texturesCoord;
	std::vector<GLuint> indices;

	/*������ ������ ������ ���� VAO, VBO � EBO*/
	GLuint _VAO = 0;
	GLuint _VBO = 0;
	GLuint _EBO = 0;
	/******************************************/
public:

	size_t getVertexCount();
	size_t getColorCount();
	size_t getTexturesCoordConut();
	size_t getIndexCount();

	void loadVertices(GLfloat *_vertices, size_t _size);
	void loadVertices(std::vector<GLfloat> _vertices);

	void loadColors(GLfloat *_vertices, size_t _size);
	void loadColors(std::vector<GLfloat> _vertices);

	void loadTexturesCoord(GLfloat *_vertices, size_t _size);
	void loadTexturesCoord(std::vector<GLfloat> _vertices);

	void loadIndices(GLuint *_vertices, size_t _size);
	void loadIndices(std::vector<GLuint> _vertices);

	/*�������� ������� ������, ����������� �������, �����, ������� � ��������*/
	std::vector<GLfloat> genVCNTbuffer();
	/*************************************************************************/

	/*������ �������� ����� �� ���������*/
	glm::vec3 &getDefaultColor();
	/************************************/

	/*�������� VBO*/
	void createVBO();
	void createVBO_OLD();
	/**************/

	/*�������� � ������� VAO*/
	void useVAO();
	void unuseVAO();
	/************************/

	/*��������� VBO � ���������� ���*/
	void useVBO();
	void unuseVBO();
	/********************************/

	VBO();
	~VBO();
};



