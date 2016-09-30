#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "./rendersystems/GL/renderwindowGL.h"

namespace CodeHero {

RenderWindowGL::RenderWindowGL() {
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

Error RenderWindowGL::Create(int iWidth, int iHeight) {
    m_pWindow = glfwCreateWindow(iWidth, iHeight, "CodeHero", nullptr, nullptr);

    // Check for Valid Context
    if (m_pWindow == nullptr) {
        return Error::ERR_CANT_CREATE;
    }

    glfwMakeContextCurrent(m_pWindow);

    gladLoadGL();

    glfwGetFramebufferSize(m_pWindow, &iWidth, &iHeight);
    glViewport(0, 0, iWidth, iHeight);

    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);

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
    if (iKey == GLFW_KEY_ESCAPE && iAction == GLFW_PRESS) {
        glfwSetWindowShouldClose(iWindow, GL_TRUE);
    }
}

} // namespace CodeHero
