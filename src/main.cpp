#include "common.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

//Temp Data
std::vector<float> vertices = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

std::vector<unsigned int> indices = {  
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

int main(){

    using namespace glm;
    
    Window::innit();

    glEnable(GL_DEPTH_TEST);  

    Camera mainCamera = {{0, 0, 9}};
    Mesh Shrek = CreateMesh(vertices, indices);

    while(!glfwWindowShouldClose(Window::Window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ControlCamera(&mainCamera, Window::Window);

        setUniform(Shrek.shader, "projection", mainCamera.Projection);
        setUniform(Shrek.shader, "view", mainCamera.ViewMatrix);
        DrawMesh(Shrek);

        Window::Update();
    }


    
    Window::Terminate();

    return 0;
}