#pragma once
#include "common.hpp"

namespace Window{
    glm::vec2 WindowSize = {800, 800};
    const std::string WindowTitle = "Hello World!";  
    GLFWwindow* Window;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height){
        glViewport(0, 0, width, height);
        WindowSize.x = width;
        WindowSize.y = height;
    }  

    void innit(){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        Window = glfwCreateWindow(WindowSize.x, WindowSize.y, WindowTitle.c_str(), NULL, NULL);
        if (Window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(Window);
        gladLoadGL();
        glViewport(0, 0, WindowSize.x, WindowSize.y);
        glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback); 
    }


    void Update() {
        glfwSwapBuffers(Window);
        glfwPollEvents();

        if(glfwGetKey(Window, GLFW_KEY_W) == true){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
    
    void Terminate(){
        glfwTerminate();
    }
}

