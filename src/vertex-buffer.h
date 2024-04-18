#pragma once

#include "renderer.h"

class VertexBuffer{
    private:
        unsigned int buffer_id;
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();
        void Bind();
        void Unbind();
};