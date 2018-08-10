#include "MVPmatrix.h"

void MVPmatrix::setViewMatrix(glm::mat4 _viewMatrix) {
	viewMatrix = _viewMatrix;
}
void MVPmatrix::setModelMatrix(glm::mat4 _modelMatrix) {
	modelMatrix = _modelMatrix;
}
void MVPmatrix::setProjectionMatrix(glm::mat4 _projectionMatrix) {
	projectionMatrix = _projectionMatrix;
}

glm::mat4 MVPmatrix::getViewMatrix() {
	return viewMatrix;
}
glm::mat4 MVPmatrix::getModelMatrix() {
	return modelMatrix;
}
glm::mat4 MVPmatrix::getProjectionMatrix() {
	return projectionMatrix;
}

MVPmatrix::MVPmatrix() : viewMatrix(1), modelMatrix(1), projectionMatrix(1) {
	
}


MVPmatrix::~MVPmatrix(){
}
