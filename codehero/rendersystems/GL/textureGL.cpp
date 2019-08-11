#include "rendersystems/GL/textureGL.h"

#include "core/assert.h"
#include "core/image.h"
#include "rendersystems/GL/utils.h"

#include <glad/glad.h>

namespace CodeHero {

static const uint32_t glTexture[] = {GL_TEXTURE_2D, GL_TEXTURE_CUBE_MAP};

static const uint32_t glWrapModes[] = {GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE,
                                       GL_MIRROR_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER};

TextureGL::TextureGL(std::shared_ptr<EngineContext>& iContext) : Texture(iContext) {}

TextureGL::~TextureGL() {}

void TextureGL::Bind(int32_t iUnit /*= -1 */) {
    if (iUnit != -1) {
        CH_GL_CALL(glActiveTexture(GL_TEXTURE0 + iUnit));
    }

    CH_GL_CALL(glBindTexture(glTexture[m_Type], GetGPUObject().intHandle));
}

void TextureGL::Unbind() {
    CH_GL_CALL(glBindTexture(glTexture[m_Type], 0));
}

bool TextureGL::_CreateImpl() {
    CH_GL_CALL(glGenTextures(1, &_GetGPUObjectHandle()->intHandle));
    Bind();
    // Set our texture parameters
    CH_GL_CALL(glTexParameteri(glTexture[m_Type], GL_TEXTURE_WRAP_S,
                               glWrapModes[m_WrapCoordinates[TC_U]]));
    CH_GL_CALL(glTexParameteri(glTexture[m_Type], GL_TEXTURE_WRAP_T,
                               glWrapModes[m_WrapCoordinates[TC_V]]));
    if (m_Type == T_Cube) {
        CH_GL_CALL(glTexParameteri(glTexture[m_Type], GL_TEXTURE_WRAP_R,
                                   glWrapModes[m_WrapCoordinates[TC_W]]));
    }
    // Set texture filtering
    CH_GL_CALL(glTexParameteri(glTexture[m_Type], GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    CH_GL_CALL(glTexParameteri(glTexture[m_Type], GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    if (m_Type == T_2D) {
        _GenerateTexture2D();
    } else if (m_Type == T_Cube) {
        _GenerateTextureCubeMap();
    } else {
        CH_ASSERT(false);
    }
    CH_GL_CALL(glGenerateMipmap(glTexture[m_Type]));

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
        default: return GL_RGB;
    }
}

void TextureGL::_GenerateTexture2D() {
    GLenum enumColorFormat = _GetGLFormat(_GetImage()->GetFormat());
    if (enumColorFormat == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ||
        enumColorFormat == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT ||
        enumColorFormat == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT) {
        CH_GL_CALL(glCompressedTexImage2D(glTexture[m_Type], 0, enumColorFormat,
                                          _GetImage()->GetWidth(), _GetImage()->GetHeight(), 0,
                                          _GetImage()->GetSize(), _GetImage()->GetRawData()));
    } else {
        GLint alignment = -1;
        CH_GL_CALL(glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment));
        CH_GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
        // Load, create texture and generate mipmaps
        CH_GL_CALL(glTexImage2D(glTexture[m_Type], 0, enumColorFormat, _GetImage()->GetWidth(),
                                _GetImage()->GetHeight(), 0, enumColorFormat, GL_UNSIGNED_BYTE,
                                _GetImage()->GetRawData()));
        if (alignment != -1) {
            CH_GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, alignment));
        }
    }
}

void TextureGL::_GenerateTextureCubeMap() {
    size_t nbTextures = numberTextureFaces[m_Type];
    for (size_t i = 0; i < nbTextures; ++i) {
        TextureFace face = static_cast<TextureFace>(i);
        GLenum enumColorFormat = _GetGLFormat(_GetImage(face)->GetFormat());
        if (enumColorFormat == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ||
            enumColorFormat == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT ||
            enumColorFormat == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT) {
            CH_GL_CALL(
                glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, enumColorFormat,
                                       _GetImage(face)->GetWidth(), _GetImage(face)->GetHeight(), 0,
                                       _GetImage(face)->GetSize(), _GetImage(face)->GetRawData()));
        } else {
            GLint alignment = -1;
            CH_GL_CALL(glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment));
            CH_GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
            // Load, create texture and generate mipmaps
            CH_GL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, enumColorFormat,
                                    _GetImage(face)->GetWidth(), _GetImage(face)->GetHeight(), 0,
                                    enumColorFormat, GL_UNSIGNED_BYTE,
                                    _GetImage(face)->GetRawData()));
            if (alignment != -1) {
                CH_GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, alignment));
            }
        }
    }
}

} // namespace CodeHero
