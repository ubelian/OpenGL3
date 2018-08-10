#version 430 core

in vec3 ovifColor;

out vec4 Color;

void main(){
    Color = vec4(ovifColor, 1.0f);
}
