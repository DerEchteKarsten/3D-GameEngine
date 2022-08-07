#pragma once
#include "common.hpp"

using namespace glm;


//Added to make the function local
namespace 
{
    std::string get_file_contents(const char *filename)
    {
        std::ifstream in(filename, std::ios::in | std::ios::binary);
        if (in)
        {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.reserve(in.tellg());
            in.seekg(0, std::ios::beg);
            contents.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
            in.close();
            return (contents);
        }
        throw(errno);
    }
} 



struct Shader {
    const char* vertexPath;
    const char* fragmentPath;
    unsigned int ID;
    Shader(std::string vertexPath, std::string fragmentPath){
        std::string vertexCode = get_file_contents(vertexPath.c_str());
        std::string fragmentCode = get_file_contents(fragmentPath.c_str());

        const char *vertexSource = vertexCode.c_str();
        const char *fragmentSource = fragmentCode.c_str();

        GLCatchError(GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER));
        GLCatchError(glShaderSource(vertexShader, 1, &vertexSource, NULL));
        GLCatchError(glCompileShader(vertexShader));

        GLCatchError(GLint compileStatusVertex);
        //Error hendaling
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatusVertex);
        if (!compileStatusVertex){
            GLint infoLogLenght;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLenght);
            GLchar* buffer = new GLchar[infoLogLenght];

            GLsizei bufferSizei;
            glGetShaderInfoLog(vertexShader, infoLogLenght, &bufferSizei, buffer);
            std::cout << buffer << std::endl;
            
            delete buffer;
        }

        GLCatchError(GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));

        GLCatchError(glShaderSource(fragmentShader, 1, &fragmentSource, NULL));
        GLCatchError(glCompileShader(fragmentShader));
        GLCatchError(GLint compileStatusFragment);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatusFragment);
        if (!compileStatusFragment){
            GLint infoLogLenght;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLenght);
            GLchar* buffer = new GLchar[infoLogLenght];

            GLsizei bufferSizei;
            glGetShaderInfoLog(fragmentShader, infoLogLenght, &bufferSizei, buffer);
            std::cout << buffer << std::endl;
            
            delete buffer;
        }

        GLCatchError(ID = glCreateProgram());
        GLCatchError(glAttachShader(ID, vertexShader));
        GLCatchError(glAttachShader(ID, fragmentShader));
        GLCatchError(glLinkProgram(ID));

        GLCatchError(glDeleteShader(vertexShader));
        GLCatchError(glDeleteShader(fragmentShader));

    }
};

void Bind(Shader s){
    GLCatchError(glUseProgram(s.ID));
}

void setUniform(Shader s, const std::string &name, float value){ 
    GLCatchError(glUniform1f(glGetUniformLocation(s.ID, name.c_str()), value)); 
} 

void setUniform(Shader s, const std::string &name, bool value){ 
    GLCatchError(glUniform1i(glGetUniformLocation(s.ID, name.c_str()), value)); 
} 

void setUniform(Shader s, const std::string &name, int value){ 
    GLCatchError(glUniform1i(glGetUniformLocation(s.ID, name.c_str()), value)); 
} 

void setUniform(Shader s, const std::string &name, glm::vec3 value){ 
    GLCatchError(glUniform3f(glGetUniformLocation(s.ID, name.c_str()), value.x, value.y, value.z)); 
} 

void setUniform(Shader s, const std::string &name, glm::vec4 value){ 
    GLCatchError(glUniform4f(glGetUniformLocation(s.ID, name.c_str()), value.x, value.y, value.z, value.w)); 
} 