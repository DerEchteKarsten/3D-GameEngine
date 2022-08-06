#pragma once
#include "common.hpp"

using namespace glm;

struct Shader {
    const char* vertexPath;
    const char* fragmentPath;
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath){


        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        //Error Handeling (I have no idea waht this does (I found it on the Internet))
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
           
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();		
           
            vShaderFile.close();
            fShaderFile.close();
           
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();		
        }
        catch(std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];
        
        // vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        //Error Handeling
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
        
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        //Error Handeling
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        

        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }
};

void Bind(Shader s){
    glUseProgram(s.ID);
}

void setUniform(Shader s, const std::string &name, float value){ 
    glUniform1f(glGetUniformLocation(s.ID, name.c_str()), value); 
} 

void setUniform(Shader s, const std::string &name, bool value){ 
    glUniform1i(glGetUniformLocation(s.ID, name.c_str()), value); 
} 

void setUniform(Shader s, const std::string &name, int value){ 
    glUniform1i(glGetUniformLocation(s.ID, name.c_str()), value); 
} 

void setUniform(Shader s, const std::string &name, glm::vec3 value){ 
    glUniform3f(glGetUniformLocation(s.ID, name.c_str()), value.x, value.y, value.z); 
} 

void setUniform(Shader s, const std::string &name, glm::vec4 value){ 
    glUniform4f(glGetUniformLocation(s.ID, name.c_str()), value.x, value.y, value.z, value.w); 
} 