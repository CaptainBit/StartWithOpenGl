#version 430 core

//Read memory of the gpu 
layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Color;

out vec4 vcolor;
void main(void) 
{
	
	gl_Position = Position;
	vcolor = Color;
}