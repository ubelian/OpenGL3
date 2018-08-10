#ifndef MAIN_H
#define MAIN_H

/*Подключение OpenGL*/
#pragma comment(lib, "c:/LIBRARY/opengl/OpenGL32.lib")
/********************/

/*Подключение GLEW*/
#define GLEW_STATIC
#pragma comment(lib, "c:/LIBRARY/GLEW/lib/Release/Win32/glew32s.lib")
#include "c:/LIBRARY/GLEW/include/GL/glew.h"
/******************/

/*Подключение библиотеки GLFW*/
#define GLFW_INCLUDE_NONE
#pragma comment(lib, "c:/LIBRARY/GLFW/glfw3.lib")
#include "c:/LIBRARY/GLFW/glfw3.h"
/*****************************/

/*Подключение библиотеки SOIL2 для работы с текстурами*/
#pragma comment(lib, "c:/LIBRARY/SOIL2/lib/soil2.lib")
/******************************************************/

#include "OglRenderer.h"
#include "OGLobject.h"

#include <AclAPI.h>//

#include "iostream"
#include "c:/LIBRARY/glm/glm/mat4x4.hpp"
#include "c:/LIBRARY/glm/glm/glm.hpp"
#include "c:/LIBRARY/glm/glm/gtc/type_ptr.hpp"
#include "c:/LIBRARY/glm/glm/gtc/matrix_transform.hpp"







#endif

