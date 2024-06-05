#pragma once

class IndexBuffer{
    private:
        unsigned int buffer_id;
        unsigned int buffer_length;
    public:
        IndexBuffer(const unsigned int* data, unsigned int size);
        ~IndexBuffer();
        void bind() const;
        void unbind() const;
        inline unsigned int get_ib_size() const {return buffer_length;}
};