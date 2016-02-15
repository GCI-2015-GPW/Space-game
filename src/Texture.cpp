#include "Texture.h"

#include <stdexcept>

#include <cstdio>
#include <string>

#include "lodepng.h"

#include <glm/vec2.hpp>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

Texture::~Texture()
{
    glDeleteTextures(1, &name);
}



Texture Texture::FromDDSFile(const std::string& path)
{

    unsigned char header[124];

    /* try to open the file */
    FILE* fp = fopen(path.c_str(), "rb");
    if (fp == nullptr) throw std::invalid_argument("Cannot open file " + path);

    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        throw std::invalid_argument("Not a DDS");
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp);

    auto height = reinterpret_cast<size_t>(&(header[8]));
    auto width = reinterpret_cast<size_t>(&(header[12]));
    auto linearSize = reinterpret_cast<size_t>(&(header[16]));
    auto mipMapCount = reinterpret_cast<size_t>(&(header[24]));
    auto fourCC = reinterpret_cast<size_t>(&(header[80]));

    unsigned char* buffer;
    size_t bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = static_cast<unsigned char*>(malloc(bufsize * sizeof(unsigned char)));
    fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);

    unsigned int format;
    switch (fourCC)
    {
    case FOURCC_DXT1: format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; break;
    case FOURCC_DXT3: format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; break;
    case FOURCC_DXT5: format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; break;
    default: free(buffer); throw std::logic_error("Invalid DDS format.");
    }

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    size_t blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    size_t offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        auto size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
        glCompressedTexImage2D(
            GL_TEXTURE_2D, level, format, (GLsizei)width, (GLsizei)height, 0, (GLsizei)size, buffer + offset);

        offset += size;
        width /= 2;
        height /= 2;
    }
    free(buffer);

    
    return Texture{textureID};
}

Texture Texture::FromPNGFile(const std::string& path)
{
    glm::uvec2 size;
    
    std::vector<GLubyte> buffer;
    if(int err = lodepng::decode(buffer, size.x, size.y, path, LCT_RGBA, 8) != 0)
    {
        throw std::runtime_error("Error loading file + " + path + + " Error: " + lodepng_error_text(err));
    }
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer.data());
    
    return Texture{textureID};    
    
}

Texture Texture::FromMemory(GLubyte* data, size_t width, size_t height, GLenum channelConfig, GLenum type)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, channelConfig, type, data);
    
    return Texture{textureID};
}

