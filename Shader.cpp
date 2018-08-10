#include "Shader.h"

GLuint Shader::defaultProgram = 0;

/*�������� ���������*/
void Shader::use() {
	glUseProgram(program);
}
/********************/

/*������� ���������*/
void Shader::unuse() {
	glUseProgram(0);
}
/*******************/

/*������������� ��������� ��������� �� ���������*/
void Shader::useDefault() {
	glUseProgram(defaultProgram);
}
/************************************************/

/*��������� ��������� ���������*/
void Shader::setProgramId(GLuint _program) {
	program = _program;
}
/*******************************/

/*��������� ��������� ���������*/
GLuint Shader::getProgramId() {
	return program;
}
/*******************************/

void Shader::loadShader(const GLchar* vertexPath, const GLchar* fragmentPath, GLboolean useDefault){
	
	// 1. �������� �������� ��� ������� �� filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// �������������, ��� ifstream ������� ����� ���������� ����������
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try {
		// ��������� �����
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// ��������� ������ � ������
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// ��������� �����
		vShaderFile.close();
		fShaderFile.close();
		// ��������������� ������ � ������ GLchar
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	// 2. ������ ��������
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	// ��������� ������
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// ���� ���� ������ - ������� ��
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ����������� ������
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// ���� ���� ������ - ������� ��
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	program = glCreateProgram();
	if (program == 0)
		std::cout << "OPENGL::SHADER::PROGRAM::Can't create program with glCreateProgram(Returned NULL)" << std::endl;

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	//���� ���� ������ - ������� ��
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// ������� �������, ��������� ��� ��� � ��������� � ��� ������ �� �����.
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	glUseProgram(program);
}


Shader::Shader(){

}


Shader::~Shader(){
	glUseProgram(0);
	if(program == 0)
		glDeleteProgram(program);
}
