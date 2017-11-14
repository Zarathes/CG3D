#shader vertex
#version 450 core

uniform mat4 MVP;

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 f_color;

void main() 
{
	gl_Position = MVP * position;
	f_color = color; 
};

#shader fragment
#version 450 core

uniform float alpha;

in  vec4 f_color; 
layout(location = 0) out vec4 color; 

void main() 
{
  color =  vec4(f_color.r, f_color.g, f_color.b, alpha);
};