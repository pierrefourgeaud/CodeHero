// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "renderer/GL/GLUtils.h"

#include <ostream>

#include "core/String.h"
#include "core/logger/Logger.h"
#include "renderer/GL/HAL/GLApi.h"

namespace CodeHero {

String GetGLErrorString(uint32_t err) {
    switch (err) {
        case GL_NO_ERROR: return TEXT("");
        case GL_INVALID_ENUM: return TEXT("Invalid Enum");
        case GL_INVALID_VALUE: return TEXT("Invalid Value");
        case GL_INVALID_OPERATION: return TEXT("Invalid Operation");
        case GL_INVALID_FRAMEBUFFER_OPERATION: return TEXT("Invalid Framebuffer Operation");
        case GL_OUT_OF_MEMORY: return TEXT("Out of Memory");
        case GL_STACK_UNDERFLOW: return TEXT("Stack Underflow");
        case GL_STACK_OVERFLOW: return TEXT("Stack Overflow");
    }
    return TEXT("Unknown");
}

void GLCheckErr(const char* location, const char* call) {
    GLenum err = glGetError();
    if (GL_NO_ERROR != err) {
        std::wostringstream s;
        s << "[GL_CALL_ERROR] 0x" << err << "(" << GetGLErrorString(err) << ")";
        if (location) {
            s << " at\n\t" << location;
        }
        if (call) {
            s << "\n\t\t" << call;
        }
        LOGE << s.str() << std::endl;
    }
}

} // namespace CodeHero