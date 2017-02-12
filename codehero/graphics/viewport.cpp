// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/viewport.h"

namespace CodeHero {

Viewport::Viewport(uint32_t iX, uint32_t iY, uint32_t iWidth, uint32_t iHeight)
    : m_Position(iX, iY)
    , m_Dimension(iWidth, iHeight) {}

Viewport::Viewport(const IntVector2& iPosition, const IntVector2& iDimension)
    : m_Position(iPosition)
    , m_Dimension(iDimension) {}

Viewport::~Viewport() {}

} // namespace CodeHero

