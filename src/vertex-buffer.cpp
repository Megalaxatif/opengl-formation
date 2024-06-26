#include <iostream>
#include <vertex-buffer.h>
#include <renderer.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    ASSERT(glGenBuffers(1, &buffer_id));
    ASSERT(glBindBuffer(GL_ARRAY_BUFFER, buffer_id));
    ASSERT(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0)); // unbind the buffer
}
VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &buffer_id);
}
void VertexBuffer::Bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
}
void VertexBuffer::Unbind() const{
     glBindBuffer(GL_ARRAY_BUFFER, 0);
}