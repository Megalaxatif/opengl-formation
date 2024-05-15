#include <shader.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <renderer.h>

Shader::Shader(std::string path){
    Shaders shader_source = loadShader(path);
    shader_id = createShader(shader_source.vertex_shader_source, shader_source.fragment_shader_source);
}
Shader::~Shader(){
    glDeleteProgram(shader_id);
}

void Shader::bind(){
    glUseProgram(shader_id);
}

void Shader::unbind(){
    glUseProgram(0);
}

unsigned int Shader::getShaderId(){
    return shader_id;
}
void Shader::setUniform4f(const char* name, float f1, float f2, float f3, float f4){
    ASSERT(int location = glGetUniformLocation(shader_id, name)); // store in <location> the adress of the u_color uniform
    if (location == -1) std::cerr << "erreur avec l'uniform a la ligne: " << __LINE__ -1 << "\n"; // debugging, location = -1 if it doesn't find the uniform
    ASSERT(glUniform4f(location, f1, f2, f3, f4)); // modify the uniform
}

void Shader::setUniform1i(const char* name, int i1){
    ASSERT(int location = glGetUniformLocation(shader_id, name)); // store in <location> the adress of the u_color uniform
    if (location == -1) std::cerr << "erreur avec l'uniform a la ligne: " << __LINE__ -1 << "\n"; // debugging, location = -1 if it doesn't find the uniform
    ASSERT(glUniform1i(location, i1)); // modify the uniform
}

Shaders Shader::loadShader(std::string filepath){
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream shader_array[2];
    shader_type type = shader_type::VERTEX;
    if (!getline(stream, line)){
        std::cout << "load_shaders error \n";
    }
    while(getline(stream, line)){
        // so the file needs to start with "shader" else it will crash
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos){
                type = shader_type::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos){
                type = shader_type::FRAGMENT;
            }
        }
        else{
            shader_array[(int)type] << line << "\n";
        }
    }
    return {shader_array[0].str(), shader_array[1].str()};
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = &source[0]; // convert std::string to const char (C type)
    glShaderSource(id, 1, &src, nullptr); // object file
    glCompileShader(id); // final compilation

    // TODO: error handling but I'm lazy so maybe later :)
    return id;
}

unsigned int Shader::createShader(const std::string& vertex_shader, const std::string& fragment_shader){
    unsigned int program = glCreateProgram();
    // compile shaders
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program); // link
    glValidateProgram(program);

    // delete shader object file
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}