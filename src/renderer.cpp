#include <renderer.h>

void glErrorLog(unsigned int error, const char* function, const char* file, int line){
    std::cout << "error code [" << error << "] of the function [" << function << "] in the file [" << file << "] at line [" << line << "]" << "\n";
}
// deal with previous errors
void glClearErrors(){
    while(glGetError() != GL_NO_ERROR); // loop until glGetError == 0
}

void Renderer::draw(VertexArray& va, IndexBuffer& ib, Shader& shader) const{
    va.bind();
    ib.bind();
    shader.bind();
    ASSERT(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT); // clear the window
}