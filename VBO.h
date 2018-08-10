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

	/*Каждый объект хранит свой VAO, VBO и EBO*/
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

	/*Создание единого буфера, содержащего вершины, цвета, нормали и текстуры*/
	std::vector<GLfloat> genVCNTbuffer();
	/*************************************************************************/

	/*Вернет значение цвета по умолчанию*/
	glm::vec3 &getDefaultColor();
	/************************************/

	/*Создание VBO*/
	void createVBO();
	void createVBO_OLD();
	/**************/

	/*Привязка и отвязка VAO*/
	void useVAO();
	void unuseVAO();
	/************************/

	/*Связывает VBO и отвязывает его*/
	void useVBO();
	void unuseVBO();
	/********************************/

	VBO();
	~VBO();
};



