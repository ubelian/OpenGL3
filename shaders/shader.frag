#version 430 core

in vec2 out_texCoord;

out vec4 Color;

uniform vec3 u_Color;
uniform int u_textureEnable;
uniform sampler2D gSampler;

void main(){
  if(u_textureEnable == 1)
    Color = texture2D(gSampler, out_texCoord.st);
  if(u_textureEnable == 0)
    Color = vec4(u_Color, 1.0f);

}
