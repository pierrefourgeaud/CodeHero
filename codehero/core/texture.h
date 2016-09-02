// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TEXTURE_H_
#define CODEHERO_CORE_TEXTURE_H_

namespace CodeHero {

class Texture {
public:
    Texture();
    ~Texture();

    void Use();

    GLuint Get() const { return m_TextureID; }

private:
    GLuint m_TextureID;
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_TEXTURE_H_
