#version 150

in  vec4 vPosition;
in  vec4 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 color;

void main() 
{
  gl_Position = projection * view * model * vPosition;
  color = vColor;
} 
