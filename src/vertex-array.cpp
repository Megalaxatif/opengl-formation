#include <iostream>
#include <vertex-array.h>
#include <renderer.h>

VertexArray::VertexArray(unsigned int vertex_buffer, unsigned int vertex_size, unsigned int vertex_stride)
    :vertex_buffer_id(vertex_buffer)
{
    // defining how to interpret the index buffer
    ASSERT(glGenVertexArrays(1, &vertex_array_id));
    ASSERT(glBindVertexArray(vertex_array_id));
    ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer)); // binding the vertex buffer so we can use it in the next line of code

    ASSERT(glVertexAttribPointer(0, vertex_size, GL_FLOAT, GL_FALSE, vertex_stride*sizeof(float), 0));
    ASSERT(glEnableVertexAttribArray(0));
    //texture coordinates just for test
    ASSERT(glVertexAttribPointer(1, vertex_size, GL_FLOAT, GL_FALSE, vertex_stride*sizeof(float), (void*)(2*sizeof(float))));
    ASSERT(glEnableVertexAttribArray(1));

    ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0)); // unbind the vertex buffer
    ASSERT(glBindVertexArray(0)); // unbind vertex array
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
