#include <iostream>
#include <vertex-array.h>
#include <renderer.h>

VertexArray::VertexArray(unsigned int size, unsigned int stride){
    // defining how to interpret the index buffer
    ASSERT(glGenVertexArrays(1, &vertex_array_id));
    ASSERT(glBindVertexArray(vertex_array_id));
    ASSERT(glEnableVertexAttribArray(0));
    ASSERT(glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, stride*sizeof(float), 0));
    //ASSERT(glBindVertexArray(0));
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &vertex_array_id);
}

void VertexArray::bind() const{
    glBindVertexArray(vertex_array_id);
}

void VertexArray::unbind() const{
    glBindVertexArray(0);
}
