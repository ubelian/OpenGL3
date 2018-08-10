#pragma once
#include "c:/LIBRARY/SOIL2/include/SOIL2.h"
#include "c:/LIBRARY/GLEW/include/GL/glew.h"
#include <iostream>
#include <string>
#include <vector>
class Texture{
private:
	int width, height; //Размеры текстуры
	std::vector<GLfloat> textureCoord;
	GLuint textureID;
	GLuint TBO;
public:
	void createTexture(std::string picturePath);
	void loadTextureCoord(GLfloat *_texturesCoord, size_t _size);
	void bindTexture();
	void unbindTexture();
	Texture();
	~Texture();
};

