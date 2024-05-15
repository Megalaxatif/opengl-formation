#include <texture.h>
#include <renderer.h>
#include <STBI/stb_image.h>

Texture::Texture(const std::string path) 
    : file_path(path), texture_id(0), local_buffer(nullptr), height(0), width(0), bitPerPixel(0)
{
    stbi_set_flip_vertically_on_load(1); // flip the image because it may be load upside down
    local_buffer = stbi_load(path.c_str(), &width, &height, &bitPerPixel, 4);

    ASSERT(glGenTextures(1, &texture_id));
    ASSERT(glBindTexture(GL_TEXTURE_2D, texture_id));

    ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer));
    ASSERT(glBindTexture(GL_TEXTURE_2D, 0)); // unbind the texture because we don't work on it anymore
    stbi_image_free(local_buffer); // free the local buffer because it is already linked with the texture
}

Texture::~Texture(){
    glDeleteTextures(1, &texture_id);
}

void Texture::bind(unsigned int slot) const {
    ASSERT(glActiveTexture(GL_TEXTURE0 + slot)) // GL_TEXTURE(X) = GL_TEXTURE(X-1) +1
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}