// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_MATH_VECTOR3_H_
#define CODEHERO_CORE_MATH_VECTOR3_H_

namespace CodeHero {

class Vector3 {
public:
    Vector3() {} // Create Identity vector
    Vector3(float iX, float iY, float iZ);

    ~Vector3() {}

    float x() const { return m_Vec[0]; }
    float y() const { return m_Vec[1]; }
    float z() const { return m_Vec[2]; }

    void ToIdentity() { m_Vec[0] = m_Vec[1] = m_Vec[2] = 0.0f; }

    float Length() const;

    void Normalize();

    Vector3 Cross(const Vector3& iVector) const;

    float Dot(const Vector3& iVector) const;

    // operators
    bool operator==(const Vector3& iRhs) const;
    Vector3 operator*(const float iScalar) const;
    Vector3& operator*=(const float iScalar);

private:
    float m_Vec[3] = {0};
};

static Vector3 operator*(float iScalar, const Vector3& iVec) {
    return Vector3(iVec) *= iScalar;
}

} // namespace CodeHero

#endif // CODEHERO_CORE_MATH_VECTOR3_H_