#pragma once
#include "common.hpp"
#include "Texture.hpp"
#include "shader.hpp"


struct Mesh
{
    Shader shader;
    mat4 modelMatrix;
    std::vector<Texture> Textures;
    unsigned int VAO;
    unsigned int triangleCount;
};

Mesh CreateMesh(std::vector<float> vertices, std::vector<unsigned int> indices, Shader shader, std::vector<Texture> textures = {}){
    //VBO
    unsigned int VBO;
    GL_CATCH_ERROR(glGenBuffers(1, &VBO));

    GL_CATCH_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO)); 
    GL_CATCH_ERROR(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW));

    //Shaders

    //VAO
    unsigned int VAO;
    GL_CATCH_ERROR(glGenVertexArrays(1, &VAO)); 
    GL_CATCH_ERROR(glBindVertexArray(VAO));
   // position attribute
    GL_CATCH_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0));
    GL_CATCH_ERROR(glEnableVertexAttribArray(0));
    // color attribute
    GL_CATCH_ERROR(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float))));
    GL_CATCH_ERROR(glEnableVertexAttribArray(1));
    // texture coord attribute
    GL_CATCH_ERROR(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float))));
    GL_CATCH_ERROR(glEnableVertexAttribArray(2));
    // normal attribute
    GL_CATCH_ERROR(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float))));
    GL_CATCH_ERROR(glEnableVertexAttribArray(3));

    //EBO
    unsigned int EBO;
    GL_CATCH_ERROR(glGenBuffers(1, &EBO));
    GL_CATCH_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GL_CATCH_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW)); 



    mat4 model = mat4(1.0f);

    return Mesh{shader, model, textures, VAO, (unsigned int)indices.size()};
}

void DrawMesh(Mesh* m){
    Bind(m->shader);

    for (int i = 0; i < m->Textures.size(); i++) {
        Bind(m->Textures[i], GL_TEXTURE0 + i);
        setUniform(m->shader, "Texture" + std::to_string(i), 0);
    }

    glBindVertexArray(m->VAO);

    setUniform(m->shader, "model", m->modelMatrix);
    glDrawElements(GL_TRIANGLES, m->triangleCount, GL_UNSIGNED_INT, 0);
}