// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

// TODO(pierre) to remove
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>

#include "./main.h"
#include <logger.h>
#include <filelogger.h>
#include <consolelogger.h>

#include "./core/shader.h"
#include "./core/imageloader.h"
#include "./core/image.h"

#include "./core/renderwindow.h"
#include "./rendersystems/GL/rendersystemGL.h"
#include "./rendersystems/GL/textureGL.h"

#include "./core/math/vector3.h"
#include "./core/math/matrix4.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>

#ifdef DRIVER_PNG
# include "./drivers/png/imagecodec_png.h"
#endif  // DRIVER_PNG

namespace CodeHero {

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    uint32_t width;
    uint32_t height;
    int32_t left;
    int32_t top;
    GLuint Advance;    // Horizontal offset to advance to next glyph
};

Main::Main()
    : m_ImageLoader(*ImageLoader::GetInstance()) {
    _Initialize();
}

Main::~Main() {
    _Cleanup();
}

Error Main::Start() {
    LOGD2 << "[>] Main::Start()" << std::endl;

    m_pRS.reset(new RenderSystemGL);
    Error error = m_pRS->Initialize();

    if (!error) {
        m_pMainWindow.reset(m_pRS->CreateWindow());
    }

    LOGD2 << "[<] Main::Start()" << std::endl;

    return error;
}

void RenderText(GLuint VAO, GLuint VBO, std::map<GLchar, Character>& Characters, Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, Vector3 color)
{
    // Activate corresponding render state
    shader.Use();
    glUniform3fv(glGetUniformLocation(shader.GetGPUObject().intHandle, "textColor"), 1, color.GetPtr());
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        GLfloat xpos = x + ch.left * scale;
        GLfloat ypos = y - (ch.height - ch.top) * scale;

        GLfloat w = ch.width * scale;
        GLfloat h = ch.height * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Error Main::Run() {
    LOGD2 << "[>] Main::Run()" << std::endl;

    // TODO TUTO

    // Build and compile our shader program
//    Shader* ourShader = m_pRS->CreateShader();
//    ourShader->Attach("./codehero/shaders/cs_basic.vert")
//             .Attach("./codehero/shaders/shader_basic_trans.frag")
//             .Link();

    Shader* textShader = m_pRS->CreateShader();
    textShader->Attach("./codehero/shaders/text_basic.vert")
              .Attach("./codehero/shaders/text_basic.frag")
              .Link();
    textShader->Use();
    OrthoMatrix ortho(0, 800, 0, 600);
    glUniformMatrix4fv(glGetUniformLocation(textShader->GetGPUObject().intHandle, "projection"), 1, GL_FALSE, ortho.GetPtr());

//    Vector3 vec(0, 0, 0);
//    vec.Length();

    // Set up vertex data (and buffer(s)) and attribute pointers
//    GLfloat vertices[] = {
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };

//    GLuint indices[] = {  // Note that we start from 0!
//        0, 1, 3, // First Triangle
//        1, 2, 3  // Second Triangle
//    };
//    GLuint VBO, VAO;//, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // Position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//
//    // TexCoord attribute
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(2);
//
//    glBindVertexArray(0); // Unbind VAO

    // FreeType
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    // Load font as face
    FT_Face face;
    if (FT_New_Face(ft, "./resources/fonts/Roboto-Regular.ttf", 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 24);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    std::map<GLchar, Character> Characters;

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            face->glyph->bitmap_left,
            face->glyph->bitmap_top,
            (GLuint)face->glyph->advance.x
        };
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    GLuint VAO2, VBO2;
    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Load and create a texture
//    Texture* texture1 = m_pRS->CreateTexture();
//    texture1->Load("/Users/pierrefourgeaud/Documents/container.png");
//
//    Texture* texture2 = m_pRS->CreateTexture();
//    texture2->Load("/Users/pierrefourgeaud/Documents/awesomeface.png");

//    Vector3 cubePositions[] = {
//        { 0.0f,  0.0f,  0.0f},
//        { 2.0f,  5.0f, -15.0f},
//        {-1.5f, -2.2f, -2.5f},
//        {-3.8f, -2.0f, -12.3f},
//        { 2.4f, -0.4f, -3.5f},
//        {-1.7f,  3.0f, -7.5f},
//        { 1.3f, -2.0f, -2.5f},
//        { 1.5f,  2.0f, -2.5f},
//        { 1.5f,  0.2f, -1.5f},
//        {-1.3f,  1.0f, -1.5f}
//    };

//    auto start = std::chrono::system_clock::now();

    while (!m_pMainWindow->ShouldClose()) {
        m_pRS->PollEvents();

        m_pRS->ClearFrameBuffer();

        RenderText(VAO2, VBO2, Characters, *textShader, "This is sample text", 10.0f, 565.0f, 1.0f, {0.5, 0.8f, 0.2f});
//        RenderText(VAO2, VBO2, Characters, *textShader, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, {0.3, 0.7f, 0.9f});

        // TODO(pierre) TUTO
        // Draw the triangle
//        ourShader->Use();

        // Bind Textures using texture units
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture1->GetGPUObject().intHandle);
//        glUniform1i(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "ourTexture1"), 0);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2->GetGPUObject().intHandle);
//        glUniform1i(glGetUniformLocation(ourShader->GetGPUObject().intHandle, "ourTexture2"), 1);

//        auto end = std::chrono::system_clock::now();
//
//        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//        float tr;
//        if (diff.count() < 2500) {
//            tr = -1.0f + (float)diff.count() / 1250.0f;
//        } else if (diff.count() < 5000) {
//            tr = 1.0f - ((float)diff.count() - 2500.0f) / 1250.0f;
//        } else {
//            start = end;
//        }

//        Matrix4 view;
//        view.Translate({0.0f, 0.0f, -3.0f});
//
//        PerspectiveMatrix projection(45.0f, 800 / 600, 0.1f, 100.0f);
//
//        GLint transformLoc = glGetUniformLocation(ourShader->GetGPUObject().intHandle, "model");
//        GLint viewLoc = glGetUniformLocation(ourShader->GetGPUObject().intHandle, "view");
//        GLint projectionLoc = glGetUniformLocation(ourShader->GetGPUObject().intHandle, "projection");
//
//        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.GetPtr());
//        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.GetPtr());
//
//        // Draw container
//        glBindVertexArray(VAO);
//        for(GLuint i = 0; i < 10; ++i) {
//            Matrix4 model;
//            model.Translate(cubePositions[i]);
//            model.Rotate(glfwGetTime() * 20.0f * i, {1.0f, 0.3f, 0.5f});
//
//            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, model.GetPtr());
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//        glBindVertexArray(0);


        m_pMainWindow->SwapBuffers();
    }

    // TODO TUTO
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);

//    delete ourShader;

    LOGD2 << "[<] Main::Run()" << std::endl;
    return Error::OK;
}

void Main::_Initialize() {
    SimpleLogger::ReportingLevel() = ELogLevel::Debug2;

    m_pFileLogger.reset(new FileLogger());
    SimpleLogger::AddListener(m_pFileLogger.get());

    m_pConsoleLogger.reset(new ConsoleLogger());
    SimpleLogger::AddListener(m_pConsoleLogger.get());

    LOGD2 << "[>] Main::_Initialize()" << std::endl;

    _LoadDrivers();
    LOGD2 << "[<] Main::_Initialize()" << std::endl;
}

void Main::_Cleanup() {
    m_pRS->Cleanup();

    _UnloadDrivers();
}

void Main::_LoadDrivers() {
    LOGI << "Loading drivers..." << std::endl;
#ifdef DRIVER_PNG
    m_ImageLoader.AddCodec(new ImageCodecPNG());
#endif  // DRIVER_PNG
    LOGI << "Drivers loaded..." << std::endl;
}

void Main::_UnloadDrivers() {
    LOGI << "Unloading drivers..." << std::endl;
    m_ImageLoader.ClearCodecs();
    LOGI << "Drivers unloaded..." << std::endl;
}

}  // namespace CodeHero
