#pragma once
#include "common.hpp"
#include "Texture.hpp"
#include "shader.hpp"


struct Mesh
{
    Shader shader;
    mat4 model;
    std::vector<Texture> Textures;
};

Mesh CreateMesh(std::vector<float> vertices, std::vector<unsigned int> indices){
    //VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    //Shaders
    Shader shader = Shader("../shaders/default.vs", "../shaders/default.fs");

    //VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO); 
    glBindVertexArray(VAO);
   // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW); 

    Texture testTex = Texture("../assets/container.jpg", GL_TEXTURE0);
    Texture testTex2 = Texture("../assets/Shrek.jpg", GL_TEXTURE1);

    Bind(shader);
    Bind(testTex, GL_TEXTURE0);
    Bind(testTex2, GL_TEXTURE1);
    setUniform(shader, "Texture1", 0);
    setUniform(shader, "Texture2", 1);
    glBindVertexArray(VAO);

    mat4 model = mat4(1.0f);
    model = rotate(model, glm::radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));

    return Mesh{shader, model};
}

void DrawMesh(Mesh m){
    setUniform(m.shader, "model", m.model);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}