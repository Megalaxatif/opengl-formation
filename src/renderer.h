#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "index-buffer.h"
#include "vertex-array.h"

// macro for debugging
#define ASSERT(x)\
    glClearErrors();\
    x;\
    if(unsigned int error = glGetError()) {\
        glErrorLog(error, #x, __FILE__, __LINE__); std::cin.get(); __debugbreak();\
    }

// display the error
void glErrorLog(unsigned int error, const char* function, const char* file, int line);
// deal with previous errors
void glClearErrors();

class Renderer{
    public:
        void draw(VertexArray& va, IndexBuffer& ib, Shader& shader) const;
        void clear() const;
};
