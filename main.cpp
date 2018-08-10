#include "main.h"

OglRenderer app;
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

int main() {

	glfwSetTime(0);
	app.addRectangle(-0.1f, 0.0f, 0.0f, -0.1f);

	app.getCurrentObject(0).translate(glm::vec3(0.0f, 0.1f, 0.0f));

	app.run();
	
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
	static GLfloat zBuffer = 0.0f;
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if(action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	case GLFW_KEY_UP:
		if (action != GLFW_RELEASE) {
			app.getCurrentObject(0).translate(0.0f, 0.1f, 0.0f);
			//app.getCurrentObject(0).translate(0.0f, 0.1f, 0.0f);
		}
		break;
	case GLFW_KEY_DOWN:
		if (action != GLFW_RELEASE) {
			app.getCurrentObject(0).translate(0.0f,-0.1f, 0.0f);
			//app.getCurrentObject(0).translate(0.0f, -0.1f, 0.0f);
		}
		break;
	case GLFW_KEY_LEFT:
		if (action != GLFW_RELEASE) {
			//app.getCurrentObject(1).translate(-0.1f, 0.0f, 0.0f);
			app.getCurrentObject(0).translate(-0.1f, 0.0f, 0.0f);
		}
		break;
	case GLFW_KEY_RIGHT:
		if (action != GLFW_RELEASE) {
			//app.getCurrentObject(1).translate(0.1f, 0.0f, 0.0f);
			app.getCurrentObject(0).translate(0.1f, 0.0f, 0.0f);
		}
		break;
	case GLFW_KEY_KP_0:
		if (action == GLFW_PRESS) {
			zBuffer = zBuffer - 0.1f;
			std::cout << "z buffer = " << zBuffer << std::endl;
			app.getCurrentObject(0).translate(0.0f, 0.0f, -0.1f);
		}
		break;
	case GLFW_KEY_KP_1:
		if (action == GLFW_PRESS) {
			zBuffer = zBuffer + 0.1f;
			std::cout << "z buffer = " << zBuffer << std::endl;
			app.getCurrentObject(0).translate(0.0f, 0.0f, 0.1f);
		}
		break;
	case GLFW_KEY_KP_2:
		if (action == GLFW_PRESS) {
			zBuffer = zBuffer - 1.0f;
			std::cout << "z buffer = " << zBuffer << std::endl;
			app.getCurrentObject(0).translate(0.0f, 0.0f, -1.0f);
		}
		break;
	case GLFW_KEY_KP_5:
		if (action == GLFW_PRESS) {
			zBuffer = zBuffer + 1.0f;
			std::cout << "z buffer = " << zBuffer << std::endl;
			app.getCurrentObject(0).translate(0.0f, 0.0f, 1.0f);
		}
		break;
	case GLFW_KEY_1:
		system("pause");
		break;
	default:
		break;


	}
}