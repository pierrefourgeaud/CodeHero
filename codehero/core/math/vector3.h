// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_MATH_VECTOR3_H_
#define CODEHERO_CORE_MATH_VECTOR3_H_

namespace CodeHero {

class Vector3 {
public:
    Vector3() { ToIdentity(); } // Create Identity vector
    Vector3(float iX, float iY, float iZ);

    ~Vector3() {}

    float x() const { return m_Vec[0]; }
    float y() const { return m_Vec[1]; }
    float z() const { return m_Vec[2]; }

    void ToIdentity() { m_Vec[0] = m_Vec[1] = m_Vec[2] = 0.0f; }

    float Length() const;

    // Modify the current object and can be chained
    Vector3& Normalize();
    // Return a new vector being the current vector normalized
    Vector3 Normalized() const;

    Vector3 Cross(const Vector3& iVector) const;

    float Dot(const Vector3& iVector) const;

    // operators
    bool operator==(const Vector3& iRhs) const;
    Vector3 operator+(const Vector3& iRhs) const;
    Vector3 operator-(const Vector3& iRhs) const;
    Vector3 operator*(const float iScalar) const;
    Vector3& operator*=(const Vector3& iRhs);
    Vector3& operator*=(const float iScalar);
    Vector3& operator+=(const Vector3& iRhs);
    Vector3 operator-() const { return Vector3(-m_Vec[0], -m_Vec[1], -m_Vec[2]); }

    const float* Data() const { return m_Vec; }

    static const Vector3 Forward;
    static const Vector3 Backward;
    static const Vector3 Up;
    static const Vector3 Down;
    static const Vector3 Right;
    static const Vector3 Left;

private:
    float m_Vec[3] = {0};
};

inline Vector3 operator*(float iScalar, const Vector3& iVec) {
    return Vector3(iVec) *= iScalar;
}

} // namespace CodeHero

#endif // CODEHERO_CORE_MATH_VECTOR3_H_
