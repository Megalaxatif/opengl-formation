#pragma once

class VertexArray{
    private:
        unsigned int vertex_array_id;
    public:
        VertexArray(unsigned int size, unsigned int stride);
        ~VertexArray();
        void bind() const;
        void unbind() const;

};