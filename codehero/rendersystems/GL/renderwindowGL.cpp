#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "rendersystems/GL/renderwindowGL.h"
#include "graphics/rendersystem.h"

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

    glfwSetKeyCallback(m_pWindow, RenderWindowGL::_HandleKey);

    return Error::OK;
}

bool RenderWindowGL::ShouldClose() const {
    return glfwWindowShouldClose(m_pWindow);
}

void RenderWindowGL::SwapBuffers() {
    glfwSwapBuffers(m_pWindow);
}

// static
void RenderWindowGL::_HandleKey(GLFWwindow* iWindow, int32_t iKey, int32_t iScancode, int32_t iAction, int32_t iMode) {
    (void)iScancode;
    (void)iMode;
    if (iKey == GLFW_KEY_ESCAPE && iAction == GLFW_PRESS) {
        glfwSetWindowShouldClose(iWindow, GL_TRUE);
    }
}

} // namespace CodeHero
