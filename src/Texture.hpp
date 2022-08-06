#pragma once
#include "common.hpp"
enum TextureType{
    ALBEDO
};

struct Texture{
    unsigned int ID;
    TextureType type;
    Texture(std::string Path, TextureType type = ALBEDO){
        this->type = type;
        //Loads the Raw data of the Image spezified
        int width, height, nrChannels;
        unsigned char *data = stbi_load(Path.c_str(), &width, &height, &nrChannels, 0); 
        if (!data){
            std::cout << "Failed to load texture" << std::endl;
            return;
        }

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
};

void Bind(Texture t){
    glBindTexture(GL_TEXTURE_2D, t.ID);
}
