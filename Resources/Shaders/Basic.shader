#shader vertex

#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 coord;

out vec2 v_coord;

void main()
{
   gl_Position = position;
   v_coord = coord;
}

#shader fragment

#version 330 core

in vec2 v_coord;

layout(location = 0) out vec4 color;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
	vec4 texColor = texture(u_texture, v_coord);
	color = texColor;
}