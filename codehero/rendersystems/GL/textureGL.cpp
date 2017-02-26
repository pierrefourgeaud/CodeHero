#include <glad/glad.h>
#include "./core/image.h"
#include "./rendersystems/GL/textureGL.h"

namespace CodeHero {

TextureGL::TextureGL(std::shared_ptr<EngineContext>& iContext)
    : Texture(iContext) {}

TextureGL::~TextureGL() {}

bool TextureGL::_CreateImpl() {
    glGenTextures(1, &_GetGPUObjectHandle()->intHandle);
    glBindTexture(GL_TEXTURE_2D, GetGPUObject().intHandle);
    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum enumColorFormat = _GetGLFormat(_GetRawImage().GetFormat());
    // Load, create texture and generate mipmaps
    glTexImage2D(GL_TEXTURE_2D, 0, enumColorFormat,
                 _GetRawImage().GetWidth(), _GetRawImage().GetHeight(), 0,
                 enumColorFormat, GL_UNSIGNED_BYTE, _GetRawImage().GetRawData());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

GLenum TextureGL::_GetGLFormat(const Image::Format iFormat) {
    switch (iFormat) {
    case Image::Format::IFMT_Grayscale: return GL_RED;
    case Image::Format::IFMT_RGB: return GL_RGB;
    case Image::Format::IFMT_RGBA: return GL_RGBA;
    default:
        return GL_RGB;
    }
}

} // namespace CodeHero
