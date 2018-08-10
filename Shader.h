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
	//����� ��������� ��������� �� ���������. ���� ������� �� ����� ������, �� ����� �������������� ���.
	static GLuint defaultProgram;
	//��������� ���������. ���� ������� ������ ��������� ���������, �� ��� ����� ��������������
	GLuint program;
public:
	//������������� ������� �� ���������
	void useDefault();
	//������������� �������
	void use();
	//����������� �������
	void unuse();
	//�������� ������� �� �����
	void loadShader(const GLchar* vertexPath, const GLchar* fragmentPath, GLboolean useDefault = false);
	//��������� ��������� ���������
	GLuint getProgramId();
	//��������� ��������� ���������.
	void setProgramId(GLuint program);
	/*������������ � �����������*/
	Shader();
	~Shader();
};

