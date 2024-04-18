#include "index-buffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int size){
    ASSERT(glGenBuffers(1, &buffer_id));
    ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id));
    ASSERT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), data, GL_STATIC_DRAW));
}
IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1, &buffer_id);
}
void IndexBuffer::Bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
}
void IndexBuffer::Unbind(){
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}