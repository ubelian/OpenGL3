#include "Shader.h"

GLuint Shader::defaultProgram = 0;

/*Привязка программы*/
void Shader::use() {
	glUseProgram(program);
}
/********************/

/*Отвязка программы*/
void Shader::unuse() {
	glUseProgram(0);
}
/*******************/

/*Использование шейдерной программы по умолчанию*/
void Shader::useDefault() {
	glUseProgram(defaultProgram);
}
/************************************************/

/*Установка шейдерной программы*/
void Shader::setProgramId(GLuint _program) {
	program = _program;
}
/*******************************/

/*Получение шейдерной программы*/
GLuint Shader::getProgramId() {
	return program;
}
/*******************************/

void Shader::loadShader(const GLchar* vertexPath, const GLchar* fragmentPath, GLboolean useDefault){
	
	// 1. Получаем исходный код шейдера из filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// Удостоверимся, что ifstream объекты могут выкидывать исключения
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try {
		// Открываем файлы
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// Считываем данные в потоки
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// Закрываем файлы
		vShaderFile.close();
		fShaderFile.close();
		// Преобразовываем потоки в массив GLchar
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	// 2. Сборка шейдеров
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	// Вершинный шейдер
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// Если есть ошибки - вывести их
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Фрагментный шейдер
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// Если есть ошибки - вывести их
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
	//Если есть ошибки - вывести их
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Удаляем шейдеры, поскольку они уже в программу и нам больше не нужны.
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
