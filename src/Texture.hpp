#pragma once
#include "common.hpp"

struct Texture{
    unsigned int ID;
    GLenum type;
    Texture(std::string Path, GLenum slot, GLenum type = GL_TEXTURE_2D){
        this->type = type;

        int widthImg, heightImg, numColCh;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* bytes = stbi_load(Path.c_str(), &widthImg, &heightImg, &numColCh, 0);

        GLCatchError(glGenTextures(1, &ID));
        GLCatchError(glActiveTexture(slot));
        GLCatchError(glBindTexture(type, ID));

        GLCatchError(glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCatchError(glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCatchError(glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCatchError(glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT));

        GLCatchError(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
        GLCatchError(glPixelStorei(GL_UNPACK_ROW_LENGTH, 0));
        GLCatchError(glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0));
        GLCatchError(glPixelStorei(GL_UNPACK_SKIP_ROWS, 0));
        
        GLCatchError(glTexImage2D(type, 0, GL_RGBA8, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes));
        GLCatchError(glGenerateMipmap(type));
        stbi_image_free(bytes);

        GLCatchError(glBindTexture(type, 0));
    }
};

void Bind(Texture t, GLenum slot = GL_TEXTURE0){
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, t.ID);
}
