// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/math/vector2.h"
#include <math.h>
#include "core/math/utils.h"

namespace CodeHero {

// Vector2
Vector2::Vector2(float iX, float iY) {
    m_Vec[0] = iX;
    m_Vec[1] = iY;
}

float Vector2::Length() const {
    return sqrt(x() * x() + y() * y());
}

Vector2& Vector2::Normalize() {
    float l = Length();

    if (FloatEqu(l, 0.0f)) {
        m_Vec[0] = m_Vec[1] = 0.0f;
    } else {
        m_Vec[0] /= l;
        m_Vec[1] /= l;
    }

    return *this;
}

Vector2 Vector2::Normalized() const {
    float l = Length();

    if (l == 0) {
        return Vector2();
    } else {
        return Vector2(m_Vec[0] / l, m_Vec[1] / l);
    }
}

bool Vector2::operator==(const Vector2& iRhs) const {
    return FloatEqu(x(), iRhs.x()) &&
           FloatEqu(y(), iRhs.y());
}

// IntVector2
IntVector2::IntVector2(int32_t iX, int32_t iY) {
    m_Vec[0] = iX;
    m_Vec[1] = iY;
}

float IntVector2::Length() const {
    return sqrt(x() * x() + y() * y());
}

IntVector2& IntVector2::Normalize() {
    float l = Length();

    if (FloatEqu(l, 0.0f)) {
        m_Vec[0] = m_Vec[1] = 0;
    } else {
        m_Vec[0] /= l;
        m_Vec[1] /= l;
    }

    return *this;
}

IntVector2 IntVector2::Normalized() const {
    float l = Length();

    if (l == 0) {
        return IntVector2();
    } else {
        return IntVector2(m_Vec[0] / l, m_Vec[1] / l);
    }
}

} // namespace CodeHero

