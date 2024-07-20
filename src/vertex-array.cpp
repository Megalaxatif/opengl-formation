#include <iostream>
#include <vertex-array.h>
#include <renderer.h>

VertexArray::VertexArray(unsigned int vertex_buffer)
    :vertex_buffer_id(vertex_buffer), layout_num(0)
{
    // create the vertex array
    ASSERT(glGenVertexArrays(1, &vertex_array_id));
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &vertex_array_id);
}

void VertexArray::createLayout(unsigned int vertex_size, unsigned int vertex_stride, unsigned int pointer){
    ASSERT(glBindVertexArray(vertex_array_id));                 // binding the vertex array
    ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id));    // binding the vertex buffer
    ASSERT(glVertexAttribPointer(layout_num, vertex_size, GL_FLOAT, GL_FALSE, vertex_stride*sizeof(float), (void*)(pointer * sizeof(float))));
    ASSERT(glEnableVertexAttribArray(layout_num)); // tell the shader we want to use this attrib in the rendering
    // unbind buffers
    ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0)); // unbind the vertex buffer
    ASSERT(glBindVertexArray(0)); // unbind vertex array
    layout_num ++;
}

void VertexArray::bind() const{
    glBindVertexArray(vertex_array_id);
}

void VertexArray::unbind() const{
    glBindVertexArray(0);
}
