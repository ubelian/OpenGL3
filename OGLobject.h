#pragma once
#include "c:/LIBRARY/GLEW/include/GL/glew.h"
#include "c:/LIBRARY/glm/glm/mat4x4.hpp"
#include "c:/LIBRARY/glm/glm/glm.hpp"
#include "c:/LIBRARY/glm/glm/gtc/type_ptr.hpp"
#include "c:/LIBRARY/glm/glm/gtc/matrix_transform.hpp"

#include "MVPmatrix.h"
#include "Shader.h"
#include "VBO.h"
#include "Texture.h"

#include"DebugDefinies.h"

/*Класс представляет собой рисуемый объект на экране, с которым можно производить такие действия как перемещение, 
поворот, текстурирования и т.д. Каждому объекту соответствует свой VBO, свой Shader*/

class OGLobject{
	static int objectsCount;
private:
	//Переменная определяет использует ли объект текстуру
	bool textureState = false;
	//Выполняется ли отрисовка с помощью glDrawElements(). По умолчанию отлючено
	bool drawElements = false;

	void loadModelMatrixToShader();
	void loadViewMatrixToShader();
	void loadProjectionMatrixToShader();
public:
	MVPmatrix mvpMatrix;
	Shader shader;
	VBO vbo;
	Texture texture;
	GLenum mode = GL_TRIANGLES;
	std::string objectName = "";
	int objectId;
	int getObjectsCount();
	void loadMatrixToShader();
	void translate(GLfloat _x, GLfloat _y, GLfloat _z);
	void translate(glm::vec3 _vec3);
	void scale(GLfloat _x, GLfloat _y, GLfloat _z);
	void scale(glm::vec3 _vec3);
	void rotate(GLfloat _angle, GLfloat _x, GLfloat _y, GLfloat _z);
	void rotate(GLfloat _angle, glm::vec3 _vec3);

	bool getTextureState();
	void setTextureState(bool _textureState);

	bool getDrawElements();
	void setDrawElements(bool _drawElements);

	OGLobject(const OGLobject &object);
	OGLobject();
	~OGLobject();
};


