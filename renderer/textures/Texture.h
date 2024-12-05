#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb_image.h>

#include "EngineCore.h"
class Texture {
   private:
    GLuint ID;  // OpenGL texture ID
    void loadTexture(const std::string& filePath);

   public:
    Texture(const std::string& filePath);  // Load texture from file
    Texture(const std::string& name, const unsigned char* data, int width, int height,
            int channels);  // Create custom texture
    ~Texture();

    void bind(GLuint unit) const;              // Bind texture to a unit
    void unbind() const;                       // Unbind texture
    GLuint getID() const;                      // Get texture ID
    bool reload(const std::string& filePath);  // Reload texture data
};

#endif  // TEXTURE_H
