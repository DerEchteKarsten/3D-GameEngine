#include "common.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

//Temp Data
float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = {  
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};


int main(){

    using namespace glm;

    Window::innit();

    glEnable(GL_DEPTH_TEST);  

    //VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    Camera mainCamera = Camera({0.0f, 0.0f, -3.0f});

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

    while(!glfwWindowShouldClose(Window::Window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ControlCamera(&mainCamera, Window::Window);

        setUniform(shader, "projection", mainCamera.Projection);
        setUniform(shader, "model", model);
        setUniform(shader, "view", mainCamera.ViewMatrix);


        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        Window::Update();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader.ID);
    
    Window::Terminate();

    return 0;
}