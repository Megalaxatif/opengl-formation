#pragma once

class VertexBuffer{
    private:
        unsigned int buffer_id;
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();
        void Bind() const;
        void Unbind() const;
        unsigned int inline get_id(){ return buffer_id; }      
};