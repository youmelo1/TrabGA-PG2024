#version 400

in vec3 vertexColor;
in vec2 texcoord;

uniform sampler2D texBuffer;

//Texture coords offsets for animation
uniform vec2 offset;

out vec4 color;
void main()
{
	color = texture(texBuffer, texcoord + offset);//vec4(vertexColor,1.0);

}