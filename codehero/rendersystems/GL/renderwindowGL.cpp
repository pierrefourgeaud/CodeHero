#include "rendersystems/GL/renderwindowGL.h"

#include "graphics/rendersystem.h"
#include "input/input.h"
#include "rendersystems/GL/utils.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace CodeHero {

RenderWindowGL::RenderWindowGL(RenderSystem& iRenderSystem) : RenderWindow(iRenderSystem) {
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

Error RenderWindowGL::Create(const int iWidth, const int iHeight) {
    m_pWindow = glfwCreateWindow(iWidth, iHeight, "CodeHero", nullptr, nullptr);

    // Check for Valid Context
    if (m_pWindow == nullptr) {
        return Error::ERR_CANT_CREATE;
    }

    glfwMakeContextCurrent(m_pWindow);
    glfwSwapInterval(0);

    gladLoadGL();

    int width = iWidth;
    int height = iHeight;
    glfwGetFramebufferSize(m_pWindow, &width, &height);
    m_rRenderSystem.SetPixelScalling((float)width / (float)iWidth, (float)height / (float)iHeight);

    // Setup OpenGL options
    CH_GL_CALL(glEnable(GL_DEPTH_TEST));

    glfwSetWindowUserPointer(m_pWindow, (void*)this);
    glfwSetKeyCallback(m_pWindow, RenderWindowGL::_HandleKey);
    glfwSetCursorPosCallback(m_pWindow, RenderWindowGL::_HandleMouse);

    return Error::OK;
}

void RenderWindowGL::SetShouldClose(bool iShouldClose) {
    glfwSetWindowShouldClose(m_pWindow, iShouldClose);
}

void RenderWindowGL::SetMouseVisible(bool iIsVisible, bool iGrabbed /* = true */) {
    int mode;
    if (iIsVisible) {
        mode = GLFW_CURSOR_NORMAL;
    } else {
        mode = iGrabbed ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_HIDDEN;
    }
    glfwSetInputMode(m_pWindow, GLFW_CURSOR, mode);
}

bool RenderWindowGL::ShouldClose() const {
    return glfwWindowShouldClose(m_pWindow);
}

void RenderWindowGL::SwapBuffers() {
    glfwSwapBuffers(m_pWindow);
}

// static
void RenderWindowGL::_HandleKey(GLFWwindow* iWindow,
                                int32_t iKey,
                                int32_t iScancode,
                                int32_t iAction,
                                int32_t iMode) {
    (void)iScancode;
    (void)iMode;
    RenderWindowGL* me = static_cast<RenderWindowGL*>(glfwGetWindowUserPointer(iWindow));
    me->m_pInputHandler->HandleKey(static_cast<Key>(iKey), static_cast<KeyEvent>(iAction));
}

void RenderWindowGL::_HandleMouse(GLFWwindow* iWindow, double iPosX, double iPosY) {
    RenderWindowGL* me = static_cast<RenderWindowGL*>(glfwGetWindowUserPointer(iWindow));
    me->m_pInputHandler->HandleMouse(iPosX, iPosY);
}

} // namespace CodeHero
