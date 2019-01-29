#version 150

in vec4 color;
in vec4 position;
out vec4 fColor;

void main() 
{ 
    fColor = color + position;
}
