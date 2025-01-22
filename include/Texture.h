#ifndef TEXTURE_H
#define TEXTURE_H

#include <stb_image/stb_image.h>
#include <glad/glad.h>

class Texture {
    public:
        static unsigned int setTexture(const char* filepath, int& width, int& height, int& nrChannels, bool flip);
    
};
#endif //TEXTURE_H