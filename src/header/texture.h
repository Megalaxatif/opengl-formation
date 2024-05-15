#pragma once

#include <string>

class Texture{
    private:
        std::string file_path;
        unsigned char* local_buffer;
        unsigned int texture_id;
        int width, height, bitPerPixel;

    public:
        Texture(const std::string file_path);
        ~Texture();
        void bind(unsigned int slot = 0) const;
        void unbind();
        inline int get_width() const {return width;}
        inline int get_heigth() const {return height;}
};