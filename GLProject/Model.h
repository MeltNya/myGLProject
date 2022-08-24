#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class Model
{
public:
    Model(string  path)
    {
        loadModel(path);
    }
    ~Model();
    void Draw(Shader shader);
private:
    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    string directory;                                                                                    //保存当前加载模型所在的目录

    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,  string typeName);
    unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);
};

