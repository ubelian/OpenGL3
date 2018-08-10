#pragma once

#define GLEW_STATIC
#include "c:/LIBRARY/GLEW/include/GL/glew.h"
#include "c:/LIBRARY/GLFW/glfw3.h"

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<Windows.h>

#include"DebugDefinies.h"

class Shader{
private:
	//Общая шейдерная программа по умолчанию. Если объекту не задан шейдер, то будет использоваться эта.
	static GLuint defaultProgram;
	//Шейдерная программа. Если объекту задана шейдерная программа, то она будет использоваться
	GLuint program;
public:
	//Использование шейдера по умолчанию
	void useDefault();
	//Использование шейдера
	void use();
	//Отвязывание шейдера
	void unuse();
	//Загрузка шейдера из файла
	void loadShader(const GLchar* vertexPath, const GLchar* fragmentPath, GLboolean useDefault = false);
	//Получение шейдерной программы
	GLuint getProgramId();
	//Установка шейдерной программы.
	void setProgramId(GLuint program);
	/*Конструкторы и деструкторы*/
	Shader();
	~Shader();
};

