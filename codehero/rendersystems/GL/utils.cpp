#include "rendersystems/GL/utils.h"

#include <glad/glad.h>
#include <logger.h>
#include <ostream>

namespace CodeHero {
const char* GetGLErrorString(uint32_t err) {
    switch (err) {
        case GL_NO_ERROR: return "";
        case GL_INVALID_ENUM: return "Invalid Enum";
        case GL_INVALID_VALUE: return "Invalid Value";
        case GL_INVALID_OPERATION: return "Invalid Operation";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid Framebuffer Operation";
        case GL_OUT_OF_MEMORY: return "Out of Memory";
        case GL_STACK_UNDERFLOW: return "Stack Underflow";
        case GL_STACK_OVERFLOW: return "Stack Overflow";
    }
    return "Unknown";
}

void GLCheckErr(const char* location, const char* call) {
    GLenum err = glGetError();
    if (GL_NO_ERROR != err) {
        std::ostringstream s;
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