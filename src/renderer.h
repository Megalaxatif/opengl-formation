#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <fstream>
#include <thread>

// macro for debugging
#define ASSERT(x)\
    glClearErrors();\
    x;\
    if(unsigned int error = glGetError()) {\
        glErrorLog(error, #x, __FILE__, __LINE__); std::cin.get(); __debugbreak();\
    }

// afficher l'erreur
void glErrorLog(unsigned int error, const char* function, const char* file, int line);
// s'occuper des erreurs precédentes
void glClearErrors();