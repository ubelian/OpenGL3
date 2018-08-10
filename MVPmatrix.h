#pragma once
#include "c:/LIBRARY/glm/glm/mat4x4.hpp"
#include "c:/LIBRARY/glm/glm/glm.hpp"
#include "c:/LIBRARY/glm/glm/gtc/type_ptr.hpp"

#include"DebugDefinies.h"

class MVPmatrix{
private:
	glm::mat4 viewMatrix;
	glm::mat4 modelMatrix;
	glm::mat4 projectionMatrix;
public:
	void setViewMatrix(glm::mat4 _viewMatrix);
	void setModelMatrix(glm::mat4 _modelMatrix);
	void setProjectionMatrix(glm::mat4 _projectionMatrix);
	

	glm::mat4 getViewMatrix();
	glm::mat4 getModelMatrix();
	glm::mat4 getProjectionMatrix();

	MVPmatrix();
	~MVPmatrix();
};

