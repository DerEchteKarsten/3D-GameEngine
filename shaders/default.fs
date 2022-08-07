#version 330 core
out vec4 FragColor;
  
in vec3 Color;
in vec2 TexCoord;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main()
{
    FragColor = texture(Texture2, TexCoord);
}

