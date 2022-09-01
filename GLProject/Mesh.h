#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include "Shader.h"
using namespace std;
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};
struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};
class Mesh
{
public:
    vector<Vertex>  vertices;
    vector<unsigned int>  indices;
    vector<Texture>  textures;

    Mesh(float vertices[]);
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(Shader shader);
    void Clear();
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
    
};

