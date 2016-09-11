// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_SHADER_H_
#define CODEHERO_CORE_SHADER_H_

#include <glad/glad.h>
#include <string>

namespace CodeHero {

class Shader {
public:
    Shader();
    ~Shader();

    Shader& Attach(const std::string& iFilename);
    Shader& Link();

    void Use();

    GLuint Get() const { return m_Program; }

private:
    GLuint m_Program;

    std::string _GetShader(const std::string& iShaderPath);
    GLuint _CreateShader(const std::string& iCode);
    bool _CompileShader(GLuint iShader, const std::string& iShaderCode);
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_SHADER_H_
