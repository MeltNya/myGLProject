#version 410 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;
void main()
{
    //FragColor = texture(ourTexture, TexCoord) * texture(ourFace,TexCoord);
    FragColor = texture(ourTexture, TexCoord);
}