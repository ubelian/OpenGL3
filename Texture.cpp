#include "Texture.h"

void Texture::createTexture(std::string picturePath) {
	
	unsigned char* image = SOIL_load_image(picturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	if (!image)
		std::cout << "ERROR::OPENGL::TEXTURE::Cant load texture from file" << std::endl;

	glActiveTexture(GL_TEXTURE0);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);

	glGenBuffers(1, &TBO);
	glBindBuffer(GL_ARRAY_BUFFER, TBO);

	glBufferData(GL_ARRAY_BUFFER, textureCoord.size() * sizeof(GLfloat), textureCoord.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	//int loc = glGetUniformLocation(shaderProgram, "gSampler");
	//if (loc >= 0)
		//glUniform1i(loc, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
}

void Texture::loadTextureCoord(GLfloat *_texturesCoord, size_t _size) {
	for (size_t i = 0; i < _size; i++) {
		textureCoord.push_back(_texturesCoord[i]);
	}
}

void Texture::bindTexture(){
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbindTexture(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(){
}


Texture::~Texture(){
}
