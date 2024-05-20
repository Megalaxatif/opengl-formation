#include <shader.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
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
    //check if the program id we are currently using is the same as the shader id 
    int program_id = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &program_id);
    if (program_id != shader_id){
        glUseProgram(shader_id); // we use this shader if it wasn't the already the case
    }
    ASSERT(int location = glGetUniformLocation(shader_id, name)); // store in <location> the adress of the u_color uniform
    if (location == -1) std::cerr << "\n" << "erreur avec l'uniform a la ligne: " << __LINE__ -1; // debugging, location = -1 if it doesn't find the uniform
    ASSERT(glUniform4f(location, f1, f2, f3, f4)); // modify the uniform
}

void Shader::setUniform1i(const char* name, int i1){
    //check if the program id we are currently using is the same as the shader id 
    int program_id = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &program_id);
    if (program_id != shader_id){
        glUseProgram(shader_id); // we use this shader if it wasn't the already the case
    }
    ASSERT(int location = glGetUniformLocation(shader_id, name)); // store in <location> the adress of the u_color uniform
    if (location == -1) std::cerr << "\n" << "erreur avec l'uniform a la ligne: " << __LINE__ -1 << "\n"; // debugging, location = -1 if it doesn't find the uniform
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
    ASSERT(glShaderSource(id, 1, &src, nullptr)); // object file
    ASSERT(glCompileShader(id)); // final compilation

    //error handling
    //GLint is_compiled = 0;
    //glGetShaderiv(shader_id, GL_COMPILE_STATUS, &is_compiled);
/*
    if(is_compiled == GL_FALSE){
        // If compilation failed, find out why and log the error
        GLint max_length = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length); // get the length of the error message

        if (max_length > 0){
            std::vector<GLchar> info_log(max_length); // allocate enought memory to store the error message
            glGetShaderInfoLog(shader_id, max_length, &max_length, info_log.data()); // store the error message

            std::cerr << "Shader compilation failed with error:" << "\n" << info_log.data();
        }
        else {
            std::cerr << "Shader compilation failed with an unknown error." << std::endl;
        }
    //delete the shader if compilation failed
    glDeleteShader(shader_id);
    }
    */
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