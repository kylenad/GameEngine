#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    public:
        //Program ID
        unsigned int ID;
        //Constructor (reads and builds shader)
        Shader(const char* vertexPath, const char* fragmentPath);
        //Activate shader for use
        void use();
        //Utility uniform functions
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec4(const std::string &name, float x, float y, float z, float w) const;
    private:
        void checkCompileErrors(unsigned int shader, std::string type);
};
#endif