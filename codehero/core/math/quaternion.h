// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_MATH_QUATERNION_H_
#define CODEHERO_CORE_MATH_QUATERNION_H_

namespace CodeHero {

// Forward declaration
class Vector3;
class Matrix4;

class Quaternion {
public:
    Quaternion()
        : m_W(1.0f)
        , m_X(0.0f) 
        , m_Y(0.0f) 
        , m_Z(0.0f) {} // identity quaternion

    Quaternion(const Quaternion& iRhs)
        : m_W(iRhs.m_W)
        , m_X(iRhs.m_X)
        , m_Y(iRhs.m_Y)
        , m_Z(iRhs.m_Z) {} // Copy ctor

    Quaternion(float iW, float iX, float iY, float iZ)
        : m_W(iW)
        , m_X(iX)
        , m_Y(iY)
        , m_Z(iZ) {} // Explicit construction

    Quaternion(float iAngle, const Vector3& iAxis) { FromAngleAndAxis(iAngle, iAxis); }
    Quaternion(float iX, float iY, float iZ) { FromEulerAngles(iX, iY, iZ); }
    explicit Quaternion(const Matrix4& iMat) { FromRotationMatrix(iMat); }
    // From orthonormal axis
    Quaternion(const Vector3& iXAxis, const Vector3& iYAxis, const Vector3& iZAxis) {
        FromAxis(iXAxis, iYAxis, iZAxis);
    }
    // Look at
    Quaternion(const Vector3& iDirection, const Vector3& iUp) { FromLookAt(iDirection, iUp); }

    ~Quaternion() {}

    // Builder
    void FromAngleAndAxis(float iAngle, const Vector3& iAxis);
    void FromEulerAngles(float iX, float iY, float iZ);
    void FromRotationMatrix(const Matrix4& iMat);
    void FromAxis(const Vector3& iXAxis, const Vector3& iYAxis, const Vector3& iZAxis);
    void FromLookAt(const Vector3& iDirection, const Vector3& iUp);

    // Operators assignment
    Quaternion& operator=(const Quaternion& iRhs) {
        m_W = iRhs.m_W;
        m_X = iRhs.m_X;
        m_Y = iRhs.m_Y;
        m_Z = iRhs.m_Z;

        return *this;
    }

    Quaternion& operator+=(const Quaternion& iRhs) {
        m_W += iRhs.m_W;
        m_X += iRhs.m_X;
        m_Y += iRhs.m_Y;
        m_Z += iRhs.m_Z;

        return *this;
    }

    Quaternion& operator*=(const Quaternion& iRhs) {
        m_W *= iRhs.m_W;
        m_X *= iRhs.m_X;
        m_Y *= iRhs.m_Y;
        m_Z *= iRhs.m_Z;

        return *this;
    }

    // Operators comparison
    bool operator==(const Quaternion& iRhs) { // TODO(pierre) We should probably use the utils FloatEqu here
        return m_X == iRhs.m_X && m_Y == iRhs.m_Y && m_Z == iRhs.m_Z && m_W == iRhs.m_W;
    }

    bool operator!=(const Quaternion& iRhs) {
        return !(*this == iRhs);
    }

    // Operators op
    Vector3 operator*(const Vector3& iRhs) const;

    // Accessors
    float w() const { return m_W; }
    float x() const { return m_X; }
    float y() const { return m_Y; }
    float z() const { return m_Z; }
    const float* Data() const { return &m_W; }

    Matrix4 RotationMatrix() const;

private:

    // Quaternion data - Should stay at the end of the class declaration
    //                   because of the Data() accessor
    float m_W;
    float m_X;
    float m_Y;
    float m_Z;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_MATH_QUATERNION_H_