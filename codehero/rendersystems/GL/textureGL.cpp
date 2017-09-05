#include <glad/glad.h>
#include "./core/image.h"
#include "./rendersystems/GL/textureGL.h"

namespace CodeHero {

static const uint32_t glTexture[] = {
    GL_TEXTURE_2D,
    GL_TEXTURE_CUBE_MAP
};

TextureGL::TextureGL(std::shared_ptr<EngineContext>& iContext, Type iType)
    : Texture(iContext, iType) {}

TextureGL::~TextureGL() {}

void TextureGL::Bind(int32_t iUnit /*= -1 */) {
    if (iUnit != -1) {
        glActiveTexture(GL_TEXTURE0 + iUnit);
    }

    glBindTexture(glTexture[m_Type], GetGPUObject().intHandle);
}

void TextureGL::Unbind() {
    glBindTexture(glTexture[m_Type], 0);
}

bool TextureGL::_CreateImpl() {
    glGenTextures(1, &_GetGPUObjectHandle()->intHandle);
    Bind();
    // Set our texture parameters
    glTexParameteri(glTexture[m_Type], GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(glTexture[m_Type], GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(glTexture[m_Type], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(glTexture[m_Type], GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum enumColorFormat = _GetGLFormat(_GetRawImage().GetFormat());
    if (enumColorFormat == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ||
        enumColorFormat == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT ||
        enumColorFormat == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT) {
        glCompressedTexImage2D(glTexture[m_Type], 0, enumColorFormat,
            _GetRawImage().GetWidth(), _GetRawImage().GetHeight(), 0,
            _GetRawImage().GetSize(), _GetRawImage().GetRawData());
    } else {
        GLint alignment = -1;
        glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        // Load, create texture and generate mipmaps
        glTexImage2D(glTexture[m_Type], 0, enumColorFormat,
            _GetRawImage().GetWidth(), _GetRawImage().GetHeight(), 0,
            enumColorFormat, GL_UNSIGNED_BYTE, _GetRawImage().GetRawData());
        if (alignment != -1) {
            glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
        }
    }
    glGenerateMipmap(glTexture[m_Type]);

    Unbind();

    return true;
}

GLenum TextureGL::_GetGLFormat(const Image::Format iFormat) {
    switch (iFormat) {
    case Image::Format::IFMT_Grayscale: return GL_RED;
    case Image::Format::IFMT_RGB: return GL_RGB;
    case Image::Format::IFMT_RGBA: return GL_RGBA;
    case Image::Format::IFMT_DXT1: return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
    case Image::Format::IFMT_DXT3: return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
    case Image::Format::IFMT_DXT5: return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
    default:
        return GL_RGB;
    }
}

} // namespace CodeHero
