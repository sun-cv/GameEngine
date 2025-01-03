#include "Texture.h"

#include <stb/stb_image.h>


Texture::Texture(const std::string& name, const std::string & path) : rendererID(0), name(name), filepath(path), data(0), width(0), height(0), BPP(0)
{
    
    glGenTextures(1, &rendererID);
    glBindTexture(GL_TEXTURE_2D, rendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(path.c_str(), &width, &height, &BPP, 0);
    
    if (!data) 
    {
        Throw_(Error::runtime, "Creating texture {} failed (Missing data)", name)
    }
    
    GLenum format = (BPP == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &rendererID);
}

void Texture::bind(unsigned int slot) const
{
    Log_(Log::Loop, Log::Texture, "Binding texture {} to slot {}", rendererID, slot);

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, rendererID);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::reload()
{
    glDeleteTextures(1, &rendererID);
    try
    {
        Texture buffer(name, filepath);

        *this = buffer;

        Log_(Log::System, Log::Texture, "Reloaded Texture {} successfully", name);
        return true;
    }
    catch(Exceptions)
    {
        Log_(Log::Error, Log::Texture, "Reload failed | {}", error.what());
        throw;
    }
}