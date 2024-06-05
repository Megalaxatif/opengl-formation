#pragma once

class VertexArray{
    private:
        unsigned int vertex_array_id;
        unsigned int vertex_buffer_id;
        unsigned int layout_num;
    public:
        VertexArray(unsigned int vertex_buffer);
        ~VertexArray();
        void createLayout(unsigned int vertex_size, unsigned int vertex_stride, unsigned int pointer);
        void bind() const;
        void unbind() const;

};