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
    void Normalize();

    const float* GetPtr() const { return m_Vec; }

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
    void Normalize();

    const int32_t* GetPtr() const { return m_Vec; }

private:
    int32_t m_Vec[2] = {0};
};

} // namespace CodeHero

#endif // CODEHERO_CORE_MATH_VECTOR2_H_
