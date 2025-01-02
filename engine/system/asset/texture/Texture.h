#pragma once

#include "CoreUtility.h"
#include "RenderGladGLFW.h"


class Texture
{
    private:
        unsigned int                            rendererID;
        std::string                             name;

        std::string                             filepath;
        unsigned char*                          data;

        int                                     width;
        int                                     height;
        int                                     BPP;

    public:
        Texture(const std::string& name, const std::string& path);
        ~Texture();


        void bind(unsigned int slot = 0) const;
        void unbind();
        bool reload();

        inline unsigned int getID() const { return rendererID; }
        inline int getHeight()      const { return height; }
        inline int getWidth()       const { return width; }

};
