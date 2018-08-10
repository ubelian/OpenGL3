#include "OglRenderer.h"
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	using std::cout;
	using std::endl;

	if (id == 131204)
		return;
	cout << "---------------------opengl-callback-start------------" << endl;
	cout << "message: " << message << endl;
	
	cout << "source: ";
	switch (source) {
	case GL_DEBUG_SOURCE_API:
		cout << "API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		cout << "WINDOW_SYSTEM";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		cout << "THIRD_PARTY";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		cout << "APPLICATION";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		cout << "OTHER";
		break;
	}

	cout << endl;
	cout << "type: ";

	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		cout << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		cout << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		cout << "OTHER";
		break;
	}
	cout << endl;

	cout << "id: " << id << endl;
	cout << "severity: ";
	switch (severity) {
	case GL_DEBUG_SEVERITY_LOW:
		cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		cout << "HIGH";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		cout << "NOTIFICATION";
		break;
	}
	cout << endl;
	cout << "---------------------opengl-callback-end--------------" << endl;
}

void OglRenderer::run() {
	while (!glfwWindowShouldClose(window)) {

		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if (renderedObjects.size() == 0) {
			std::cout << "ERROR::OPENGL::OGLRENDERER::No rendering objects." << std::endl;
			return;
		}

		for (size_t i = 0; i < renderedObjects.size(); i++) {
			OGLobject &object = renderedObjects.at(i);
			/*Привязка шейдера, VAO и VBO относящихся к заданому объекту*/
			
			object.shader.use();
			object.vbo.useVAO();
			object.vbo.useVBO();

			/*Если к объекту привязана текстура, то активировать её*/
			if (object.getTextureState())
				object.texture.bindTexture();
			/*******************************************************/

			glfwPollEvents();
			object.loadMatrixToShader();

			if (object.getTextureState() == true){
				glUniform1i(glGetUniformLocation(object.shader.getProgramId(), "u_textureEnable"), 1);
			}
			else {
				glUniform1i(glGetUniformLocation(object.shader.getProgramId(), "u_textureEnable"), 0);
			}

			/*Определяет какой метод отрисовки будет использоваться исходя из переменной bool drawElements.*/
			/*drawElements == true когда vbo загружает массив элементов*/
			object.getDrawElements() == false ? glDrawArrays(object.mode, 0, object.vbo.getVertexCount() / 3)
				                              : glDrawElements(object.mode, object.vbo.getIndexCount(), GL_UNSIGNED_INT, 0);
			/***********************************************************/

			/*Отвязка VBO, VAO и шейдера относящихся к заданому объекту*/
			/*Если к объекту привязана текстура, то деактивировать её*/
			if (object.getTextureState())
				object.texture.unbindTexture();
			/*********************************************************/

			object.vbo.unuseVBO();
			object.vbo.unuseVAO();
			object.shader.unuse();
			/***********************************************************/
		}
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	exit(1);
}

void OglRenderer::push(ObjectCreateInfo &createInfo) {
	//Создаем отрисовываемый объект
	//Определяем ему такие свойства как шейдер, вершины
	OGLobject newObject;
	//*************************************************

	//Помещаем его в коллекцию отрисовывающих объектов
	renderedObjects.push_back(newObject);
	//************************************************

	OGLobject &object = renderedObjects.back();

	//Если шейдера нет, то будет использоваться шейдер по умолчанию
	if (createInfo.vertexPath == nullptr || createInfo.fragmentPath == nullptr) {
		object.shader = defaultShader;
		object.shader.use();
	}
	//Иначе загрузить шейдер из файла
	else {
		object.shader.loadShader(createInfo.vertexPath, createInfo.fragmentPath);
	}

	object.vbo.loadVertices(createInfo.vertices, createInfo.verticesSize / sizeof(GLfloat));
	if (createInfo.indices != nullptr) {
		object.vbo.loadIndices(createInfo.indices, createInfo.indicesSize / sizeof(GLfloat));
		object.setDrawElements(true);
	}
	object.vbo.createVBO();

	//Если объект имеет текстуру, то загрузить её.
	//Иначе u_textureEnable == 0 и будет использоваться цвет по умолчанию
	if (createInfo.picturePath != 0) {
		//Загрузка текстурных координат
		object.texture.loadTextureCoord(createInfo.texCoord, createInfo.texCoordSize / sizeof(GLfloat));

		/*Для создание текстуры необходимо активное VAO*/
		object.vbo.useVAO();
		object.texture.createTexture(createInfo.picturePath);
		object.vbo.unuseVAO();
		/***********************************************/

		//Состояние текстуры теперь активно
		object.setTextureState(true);
		glUniform1i(glGetUniformLocation(object.shader.getProgramId(), "u_textureEnable"), 1);
	}
	else {
		object.setTextureState(false);
		glUniform1i(glGetUniformLocation(object.shader.getProgramId(), "u_textureEnable"), 0);
	}

	glUniform3fv(glGetUniformLocation(object.shader.getProgramId(), "u_Color"), 1, value_ptr(object.vbo.getDefaultColor()));

	object.mvpMatrix.setProjectionMatrix(glm::orthoRH(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, -1.0f));
	object.loadMatrixToShader();

}

OGLobject &OglRenderer::getCurrentObject(size_t index){
	if (index > renderedObjects.size()) {
		std::cout << "ERROR::OPENGL::OGLRENDERER::getCurrentObject:: index > renderedObjects.size()" << std::endl;
	}
	return renderedObjects.at(index);
}


 

GLFWwindow **OglRenderer::getWindowHandle() {
	return &window;
}



OglRenderer::OglRenderer() : clearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f)) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(1024, 768, "LearnOpenGL",nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "OPENGL: FAILED TO CREATE GLFW WINDOW" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyCallback);
	
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "OPENGL: FAILED TO INITIALIZE GLEW" << std::endl;
		glfwTerminate();
	}

	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


#ifdef OGLRENDERER_DEBUG
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(debugCallback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
#endif

	renderedObjects.reserve(100);

	defaultShader.loadShader("C:/Users/Sergey/source/repos/OpenGL3/shaders/shader.vert", 
		                     "C:/Users/Sergey/source/repos/OpenGL3/shaders/shader.frag");

}

void OglRenderer::addTriangle(GLfloat _x1, GLfloat _y1, GLfloat _x2, GLfloat _y2, GLfloat _x3, GLfloat _y3, const char *texture) {

	GLfloat vertices[] = {
		_x1, _y1, 0.0f,
		_x2, _y2, 0.0f,
		_x3, _y3, 0.0f
	};

	ObjectCreateInfo createInfo = {};
	createInfo.vertices = vertices;
	createInfo.verticesSize = sizeof(vertices);

	if (texture != nullptr) {
		GLfloat texCoord[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
		};
		createInfo.texCoord = texCoord;
		createInfo.texCoordSize = sizeof(texCoord);
		createInfo.picturePath = texture;
	}

	this->push(createInfo);

}

void OglRenderer::addRectangle(GLfloat _x1, GLfloat _y1, GLfloat _x2, GLfloat _y2, const char *texture) {

	GLfloat vertices[] = {
		_x1, _y1, 0.0f,
		_x1, _y2, 0.0f,
		_x2, _y2, 0.0f,
		_x2, _y1, 0.0f,
	};

	GLuint indices[] = {
	    0, 1, 2,
	    0, 2, 3
	};

	ObjectCreateInfo createInfo = {};
	createInfo.vertices = vertices;
	createInfo.verticesSize = sizeof(vertices);
	createInfo.indices = indices;
	createInfo.indicesSize = sizeof(indices);
	
	if (texture != nullptr) {
		GLfloat texCoord[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		};
		createInfo.texCoord = texCoord;
		createInfo.texCoordSize = sizeof(texCoord);
		createInfo.picturePath = texture;
	}

	this->push(createInfo);

}

bool OglRenderer::Timer() {
	double seconds = 1.0;
	glfwSetTime(0);
	while (seconds < glfwGetTime()) {
		;
	}
	return true;
}

void OglRenderer::setClearColor(glm::vec4 _clearColor) {
	clearColor = _clearColor;
}


OglRenderer::~OglRenderer(){
}

