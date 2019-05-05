// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/color.h"

namespace CodeHero {

const Color Color::Black = Color(0.0f, 0.0f, 0.0f);
const Color Color::White = Color(1.0f, 1.0f, 1.0f);
const Color Color::Red = Color(1.0f, 0.0f, 0.0f);
const Color Color::Green = Color(0.0f, 1.0f, 0.0f);
const Color Color::Blue = Color(0.0f, 0.0f, 1.0f);

Color::Color() {
    *this = Black;
}

Color::Color(float iR, float iG, float iB, float iA /* = 0.1f*/) : m_Rgba{iR, iG, iB, iA} {}

Color::~Color() {}

} // namespace CodeHero