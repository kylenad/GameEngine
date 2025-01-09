#ifndef GEOMETRY_H 
#define GEOMETRY_H 

#include <glad/glad.h>

class Geometry {
    public:
        static unsigned int createRectangle(float* verticies, unsigned int vertSize, unsigned int* indices, unsigned int indSize, unsigned int& VBO, 
            unsigned int& EBO, bool hasTextCords);
        static unsigned int createTriangle(float* verticies, unsigned int vertSize, unsigned int& VBO);
};
#endif // GEOMETRY_H
