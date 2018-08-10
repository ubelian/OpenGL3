#include "OGLobject.h"

int OGLobject::objectsCount = 0;

void OGLobject::translate(GLfloat _x, GLfloat _y, GLfloat _z) {
	glm::mat4 tr = glm::translate(mvpMatrix.getModelMatrix(), glm::vec3(_x, _y, _z));
	mvpMatrix.setModelMatrix(tr);
	loadModelMatrixToShader();
}

void OGLobject::translate(glm::vec3 _vec3) {
	GLuint _program = this->shader.getProgramId();
	this->shader.use();
	glm::mat4 tr = glm::translate(mvpMatrix.getModelMatrix(), _vec3);
	this->mvpMatrix.setModelMatrix(tr);
	this->loadModelMatrixToShader();
	glUseProgram(_program);
}

void OGLobject::scale(GLfloat _x, GLfloat _y, GLfloat _z) {
	glm::mat4 tr = glm::scale(mvpMatrix.getModelMatrix(), glm::vec3(_x, _y, _z));
	tr = mvpMatrix.getModelMatrix() * tr;
	mvpMatrix.setModelMatrix(tr);
	loadModelMatrixToShader();
}

void OGLobject::scale(glm::vec3 _vec3) {
	glm::mat4 tr = glm::scale(mvpMatrix.getModelMatrix(), _vec3);
	tr = mvpMatrix.getModelMatrix() * tr;
	mvpMatrix.setModelMatrix(tr);
	loadModelMatrixToShader();
}

void OGLobject::rotate(GLfloat _angle, GLfloat _x, GLfloat _y, GLfloat _z) {
	glm::mat4 tr = glm::rotate(mvpMatrix.getModelMatrix(), _angle, glm::vec3(_x, _y, _z));
	tr = mvpMatrix.getModelMatrix() * tr;
	mvpMatrix.setModelMatrix(tr);
	loadModelMatrixToShader();
}

void OGLobject::rotate(GLfloat _angle, glm::vec3 _vec3) {
	glm::mat4 tr = glm::rotate(mvpMatrix.getModelMatrix(), _angle, _vec3);
	tr = mvpMatrix.getModelMatrix() * tr;
	mvpMatrix.setModelMatrix(tr);
	loadModelMatrixToShader();
}

bool OGLobject::getTextureState(){
	return textureState;
}

void OGLobject::setTextureState(bool _textureState){
	textureState = _textureState;
}

void OGLobject::loadMatrixToShader() {
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramId(), "mMatrix"), 1, GL_FALSE, glm::value_ptr(mvpMatrix.getModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramId(), "vMatrix"), 1, GL_FALSE, glm::value_ptr(mvpMatrix.getViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramId(), "pMatrix"), 1, GL_FALSE, glm::value_ptr(mvpMatrix.getProjectionMatrix()));
}

void OGLobject::loadModelMatrixToShader(){
	GLint _program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &_program);
	if (_program != 0)
		this->shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramId(), "mMatrix"),
		               1, GL_FALSE, glm::value_ptr(mvpMatrix.getModelMatrix()));
	if (_program != 0)
		glUseProgram(static_cast<GLuint>(_program));
}

void OGLobject::loadViewMatrixToShader(){
	GLint _program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &_program);
	if(_program != 0)
		this->shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramId(), "vMatrix"),
		               1, GL_FALSE, glm::value_ptr(mvpMatrix.getViewMatrix()));
	if (_program != 0)
		glUseProgram(static_cast<GLuint>(_program));
}

void OGLobject::loadProjectionMatrixToShader() {
	GLint _program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &_program);
	if (_program != 0)
		this->shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramId(), "pMatrix"), 
		               1, GL_FALSE, glm::value_ptr(mvpMatrix.getProjectionMatrix()));
	if (_program != 0)
		glUseProgram(static_cast<GLuint>(_program));
}

int OGLobject::getObjectsCount() {
	return objectsCount;
}

bool OGLobject::getDrawElements() {
	return drawElements;
}

void OGLobject::setDrawElements(bool _drawElements) {
	drawElements = _drawElements;
}

/*Конструкторы и деструкторы*/
OGLobject::OGLobject(const OGLobject &object){
	std::cout << "Copy constructor. objects count = " << ++objectsCount << std::endl;
}

OGLobject::OGLobject() : vbo(), mvpMatrix(), shader(){
#ifdef OGLOBJECT_DEBUG
	objectsCount++;
	std::cout << "Constructor. objects count = " << objectsCount << std::endl;
#endif
}

OGLobject::~OGLobject(){
#ifdef OGLOBJECT_DEBUG
	objectsCount--;
	std::cout << "Destructor. objects count = " << objectsCount << std::endl;
#endif
}
/***************************/

