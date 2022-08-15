#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;   //高光半径
}; 
struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;

uniform Material material;  
uniform vec3 viewPos; 
uniform Light light;
void main()
{    
    // 环境光
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
   
    // 漫反射 
    vec3 lightDir = normalize(-light.direction);
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse *diff* vec3(texture(material.diffuse,TexCoords));
    
    // 镜面光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular* spec * vec3(texture(material.specular, TexCoords));

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
    //FragColor = vec4(spec,spec,spec,1.0);
}