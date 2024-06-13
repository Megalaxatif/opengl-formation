#include <iostream>
#include <index-buffer.h>
#include <renderer.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int size){
    buffer_length = size;
    ASSERT(glGenBuffers(1, &buffer_id));
    ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id));
    ASSERT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), data, GL_STATIC_DRAW));
    ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // unbind the buffer
}

IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1, &buffer_id);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
}

void IndexBuffer::unbind() const {
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}