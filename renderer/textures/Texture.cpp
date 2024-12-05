#include "Texture.h"

Texture::Texture(const std::string& filePath) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Set texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image data
    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

    if (data) {
        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
        std::cout << "[SYSTEM]::[TEXTURE] Loaded successfully ID: " << ID << " :: File Path: " << filePath << "\n";
    } else {
        std::cerr << "[FAILED]::[TEXTURE] Failed to load texture: " << filePath << "\n";
        stbi_image_free(data);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string& name, const unsigned char* data, int width, int height, int channels) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    std::cout << "[SYSTEM]::[TEXTURE] Custom texture '" << name << "' created.\n";
}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
    std::cout << "[SYSTEM]::[TEXTURE] Deleted texture ID: " << ID << "\n";
}

void Texture::bind(GLuint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

GLuint Texture::getID() const { return ID; }

bool Texture::reload(const std::string& filePath) {
    glBindTexture(GL_TEXTURE_2D, ID);

    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

    if (data) {
        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
        std::cout << "[SYSTEM]::[TEXTURE] Reloaded successfully: " << filePath << "\n";
        glBindTexture(GL_TEXTURE_2D, 0);
        return true;
    } else {
        std::cerr << "[FAILED]::[TEXTURE] Failed to reload texture: " << filePath << "\n";
        stbi_image_free(data);  // Cleanup in case of partial load
        glBindTexture(GL_TEXTURE_2D, 0);
        return false;
    }
}
