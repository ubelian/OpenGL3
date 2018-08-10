#include "VBO.h"

//Шартрёз
glm::vec3 VBO::defaultColor = glm::vec3(0.5f, 1.0f, 0.0f);

/*Загрузка вершин*/
void VBO::loadVertices(GLfloat *_vertices, size_t _size) {
	vertices.reserve(_size);
	for (size_t i = 0; i < _size; i++) {
		vertices.push_back(_vertices[i]);
	}
}
void VBO::loadVertices(std::vector<GLfloat> _vertices) {
	vertices = _vertices;
}
/*****************/

/*Загрузка цвета*/
void VBO::loadColors(GLfloat *_colors, size_t _size) {
	for (size_t i = 0; i < _size; i++) {
		colors.push_back(_colors[i]);
	}
}
void VBO::loadColors(std::vector<GLfloat> _colors) {
	colors = _colors;
}
/****************/
	 
/*Загрузка текстурных координат*/
void VBO::loadTexturesCoord(GLfloat *_texturesCoord, size_t _size) {
	for (size_t i = 0; i < _size; i++) {
		texturesCoord.push_back(_texturesCoord[i]);
	}
}
void VBO::loadTexturesCoord(std::vector<GLfloat> _texturesCoord) {
	texturesCoord = _texturesCoord;
}
/*******************************/
	 
/*Загрузка индексов*/
void VBO::loadIndices(GLuint *_indices, size_t _size) {
	for (size_t i = 0; i < _size; i++) {
		indices.push_back(_indices[i]);
	}
}
void VBO::loadIndices(std::vector<GLuint> _indices) {
	indices = _indices;
}
/*******************/

size_t VBO::getVertexCount() {
	return vertices.size();
}
size_t VBO::getColorCount() {
	return colors.size();
}
size_t VBO::getTexturesCoordConut() {
	return texturesCoord.size();
}
size_t VBO::getIndexCount() {
	return indices.size();
}

std::vector<GLfloat> VBO::genVCNTbuffer() {
	//Создаём буффер и выделяем ему необходимую память в зависимости от размера списка вершин.
	std::vector<GLfloat> vcntBuffer;
	vcntBuffer.reserve(2 * vertices.size());

	for (size_t i = 0; i < vertices.size(); i = i + 3) {

		//Загрузка 3 вершин
		vcntBuffer.push_back(vertices.at(i));
		vcntBuffer.push_back(vertices.at(i + 1));
		vcntBuffer.push_back(vertices.at(i + 2));
		//Загрузка 3 цветов
		vcntBuffer.push_back(colors.at(i));
		vcntBuffer.push_back(colors.at(i + 1));
		vcntBuffer.push_back(colors.at(i + 2));

	}

	return vcntBuffer;

}

void VBO::createVBO() {
	if (vertices.empty()) {
		std::cout << "OGLRENDERER::VBO:: Can't to create VBO, vertices.empty() returned NULL" << std::endl;
	}
	//VAO создается при вызове функции CreateVBO и связывается
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer
	   (0,                   //Аттрибут
		3, 					 //Кол-во элементов за 1 раз
		GL_FLOAT,			 //Тип данных в памяти.
		GL_FALSE,			 //Нормализовано?
		3 * sizeof(GLfloat), //Расстояние между данными. Поскольку у нас 3 значения типа GLfloat, 3 * sizeof(GLfloat) 
		(GLvoid*)0			 //Отступ. Поскольку для каждого буфера объект буфера разный устанавливается в 0.
	   );

	if (indices.size() != 0) {
		glGenBuffers(1, &_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STREAM_DRAW);
	}
	
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

glm::vec3 &VBO::getDefaultColor() {
	return defaultColor;
}

/*Привязка и отвязка VAO*/
void VBO::useVAO() {
	glBindVertexArray(_VAO);
}
void VBO::unuseVAO(){
	glBindVertexArray(0);
}
/************************/

/*Привязка и отвязка VBO*/
void VBO::useVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
}
void VBO::unuseVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
/************************/

/*Конструкторы и деструкторы*/
VBO::VBO(){
	
}

VBO::~VBO(){
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &_VBO);
	glDeleteVertexArrays(1, &_VAO);
}
/****************************/

/*Создание VBO и загрузка в него вершин*/
void VBO::createVBO_OLD() {
	if (vertices.empty()) {
		std::cout << "OGLRENDERER::VBO:: Can't to create VBO, vertices.empty() returned NULL" << std::endl;
	}

	//Если список цвета меньше списка вершин, то возьмем первый вектор в кач-ве заданого цвета для всех вершин.
	//Однако если цвета нет вообще, то будет использоваться стандартный цвет.
	if (vertices.size() > colors.size()) {
		//Если список цветов пуст, использовать defaultColor и заполнить им весь вектор цвета для создания VBO и отправки его в шейдер
		if (colors.empty()) {
			//Заполняем вектор
			colors.reserve(vertices.size());
			for (size_t i = 0; i < vertices.size(); i = i + 3) {
				colors.push_back(defaultColor.x);
				colors.push_back(defaultColor.y);
				colors.push_back(defaultColor.z);
			}
		}
		//Если список цветов не пуст, то для цвета для всех вершин берется первый vec3. 
		//Если vec3 не набирается(например нет 2ого и\или 3его элемента, они заполняются нулями
		else {
			//Проверка есть ли 2ой и 3ий элемент. Если нет, то эти контейнера заполнятся нулями
			if (colors.size() == 1) {
				colors.push_back(0.0f);
				colors.push_back(0.0f);
			}
			else
				if (colors.size() == 2) {
					colors.push_back(0.0f);
				}


			glm::vec3 defColor(colors.at(0), colors.at(1), colors.at(2));
			colors.clear();
			for (size_t i = 0; i < vertices.size(); i = i + 3) {
				colors.push_back(defColor.x);
				colors.push_back(defColor.y);
				colors.push_back(defColor.z);
			}
		}
	}

	//Создать единый буфер
	std::vector<GLfloat> vcntBuffer = genVCNTbuffer();

	//Если список цвета пуст, то создать VBO со стандартным цветом.
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, vcntBuffer.size() * sizeof(GLfloat), vcntBuffer.data(), GL_STATIC_DRAW);
	
	//Вершины
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Цвет
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

}
/***************************************/
