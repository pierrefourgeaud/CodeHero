// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_COLOR_H_
#define CODEHERO_CORE_COLOR_H_

namespace CodeHero {

class Color {
   public:
    Color();
    Color(float iR, float iG, float iB, float iA = 1.0f);
    ~Color();

    float r() const { return m_Rgba[0]; }
    float g() const { return m_Rgba[1]; }
    float b() const { return m_Rgba[2]; }
    float a() const { return m_Rgba[3]; }

    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;

   private:
    float m_Rgba[4] = {0};
};

} // namespace CodeHero

#endif // CODEHERO_CORE_COLOR_H_