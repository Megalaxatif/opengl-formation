#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

struct Shaders{
    std::string vertex_shader_source;
    std::string fragment_shader_source;
};

enum class shader_type{
    VERTEX = 0, FRAGMENT = 1
};

class Shader{
    private:
        unsigned int shader_id;
        Shaders loadShader(std::string filepath);
        unsigned int compileShader(unsigned int type, const std::string& source);
        unsigned int createShader(const std::string& vertex_shader, const std::string& fragment_shader);
        
    public:
        Shader(std::string path);
        ~Shader();
        void bind();
        void unbind();
        unsigned int getShaderId();
        void setUniform4f(const char* name, float f1, float f2, float f3, float f4);
        void setUniform1i(const char* name, int i1);
};