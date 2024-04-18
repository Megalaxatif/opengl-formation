#pragma once

#include "renderer.h"

class IndexBuffer{
    private:
        unsigned int buffer_id;
    public:
        IndexBuffer(const unsigned int* data, unsigned int size);
        ~IndexBuffer();
        void Bind();
        void Unbind();
};