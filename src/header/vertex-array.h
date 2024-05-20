#pragma once

class VertexArray{
    private:
        unsigned int vertex_array_id;
        unsigned int vertex_buffer_id;
    public:
        VertexArray(unsigned int vertex_buffer, unsigned int vertex_size, unsigned int vertex_stride);
        ~VertexArray();
        void bind() const;
        void unbind() const;

};