#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "rendersystems/GL/renderwindowGL.h"
#include "graphics/rendersystem.h"
#include "input/input.h"

namespace CodeHero {

RenderWindowGL::RenderWindowGL(RenderSystem& iRenderSystem)
    : RenderWindow(iRenderSystem) {
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
    m_rRenderSystem.SetPixelScalling(
            (float)width / (float)iWidth, (float)height / (float)iHeight);

    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetWindowUserPointer(m_pWindow, (void*)this);
    glfwSetKeyCallback(m_pWindow, RenderWindowGL::_HandleKey);

    return Error::OK;
}

void RenderWindowGL::SwapBuffers() {
    glfwSwapBuffers(m_pWindow);
}

// static
void RenderWindowGL::_HandleKey(GLFWwindow* iWindow, int32_t iKey, int32_t iScancode, int32_t iAction, int32_t iMode) {
    (void)iScancode;
    (void)iMode;
    RenderWindowGL* me = static_cast<RenderWindowGL*>(glfwGetWindowUserPointer(iWindow));
    me->m_pInputHandler->HandleKey(static_cast<Key>(iKey), static_cast<KeyEvent>(iAction));
}

} // namespace CodeHero
