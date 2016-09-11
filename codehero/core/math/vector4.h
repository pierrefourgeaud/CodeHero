// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_MATH_VECTOR4_H_
#define CODEHERO_CORE_MATH_VECTOR4_H_

namespace CodeHero {

class Vector4 {
public:
    Vector4() {}
    Vector4(float iX, float iY, float iZ, float iW);

    ~Vector4() {}

    float x() const { return m_Vec[0]; }
    float y() const { return m_Vec[1]; }
    float z() const { return m_Vec[2]; }
    float w() const { return m_Vec[3]; }

    // operators
    bool operator==(const Vector4& iRhs) const;

private:
    float m_Vec[4] = {0};
};

} // namespace CodeHero

#endif // CODEHERO_CORE_MATH_VECTOR4_H_
