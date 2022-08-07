#pragma once 

#include <iostream>
#include <glad/glad.h>

#ifndef ASSERT_
    #define ASSERT_
    #define ASSERT(x) if(!(x)) abort();
#endif

#ifndef GL_CATCH_ERROR
#define GL_CATCH_ERROR
    #define GLCatchError(x) GLClearError();\
    x;\
    ASSERT(GLLogCall())
#endif

#ifndef GL_CLEAR_ERROR
#define GL_CLEAR_ERROR
    static void GLClearError(){
        while (glGetError() != GL_NO_ERROR);
    }
#endif

#ifndef GL_LOG_CALL
#define GL_LOG_CALL
    static bool GLLogCall(){
        while (GLenum error = glGetError()){
        std::cout << "An Error occurred:" + error << std::endl;
        return false;
        }
        return true;    
    }
#endif