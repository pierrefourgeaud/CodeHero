// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_MATH_VECTOR2_H_
#define CODEHERO_CORE_MATH_VECTOR2_H_

#include "core/typedefs.h"

namespace CodeHero {

class Vector2 {
public:
    Vector2() {}
    Vector2(float iX, float iY);
    ~Vector2() {}

    float x() const { return m_Vec[0]; }
    float y() const { return m_Vec[1]; }

    void SetX(float iX) { m_Vec[0] = iX; }
    void SetY(float iY) { m_Vec[1] = iY; }

    float Length() const;
    // Modify the current object and can be chained
    Vector2& Normalize();
    // Return a new vector being the current vector normalized
    Vector2 Normalized() const;

    const float* Data() const { return m_Vec; }

    bool operator==(const Vector2& iRhs) const;

    Vector2 operator-(const Vector2& iRhs) const {
        return Vector2(m_Vec[0] - iRhs.m_Vec[0], m_Vec[1] - iRhs.m_Vec[1]);
    }

    Vector2 operator+(const Vector2& iRhs) const {
        return Vector2(m_Vec[0] + iRhs.m_Vec[0], m_Vec[1] + iRhs.m_Vec[1]);
    }

    Vector2 operator+(float iRhs) const { return Vector2(m_Vec[0] + iRhs, m_Vec[1] + iRhs); }

    Vector2 operator*(const float iScalar) const {
        return Vector2(m_Vec[0] * iScalar, m_Vec[1] * iScalar);
    }

private:
    float m_Vec[2] = {0};
};

class IntVector2 {
public:
    IntVector2() {}
    IntVector2(int32_t iX, int32_t iY);
    ~IntVector2() {}

    int32_t x() const { return m_Vec[0]; }
    int32_t y() const { return m_Vec[1]; }

    float Length() const;
    // Modify the current object and can be chained
    IntVector2& Normalize();
    // Return a new vector being the current vector normalized
    IntVector2 Normalized() const;

    const int32_t* Data() const { return m_Vec; }

    IntVector2 operator-(const IntVector2& iRhs) const {
        return IntVector2(m_Vec[0] - iRhs.m_Vec[0], m_Vec[1] - iRhs.m_Vec[1]);
    }

private:
    int32_t m_Vec[2] = {0};
};

} // namespace CodeHero

#endif // CODEHERO_CORE_MATH_VECTOR2_H_
