#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 in_texCoord;

out vec2 out_texCoord;

uniform mat4x4 mMatrix;
uniform mat4x4 vMatrix;
uniform mat4x4 pMatrix;


void main(){
  mat4x4 mvpMatrix = pMatrix * mMatrix * vMatrix;
  out_texCoord = in_texCoord;
  gl_Position = mvpMatrix * vec4(position, 1.0f);
}
