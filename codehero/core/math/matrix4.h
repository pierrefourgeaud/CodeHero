// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_MATH_MATRIX4_H_
#define CODEHERO_CORE_MATH_MATRIX4_H_

#include <math.h>
#include "./core/math/utils.h"

namespace CodeHero {

// Forward declaration
class Vector3;
class Vector4;
class Matrix3;
class Quaternion;

/**
 * @brief Matrix 44f
 */
class Matrix4 {
   public:
    Matrix4() { ToIdentity(); }
    Matrix4(float m00,
            float m01,
            float m02,
            float m03,
            float m10,
            float m11,
            float m12,
            float m13,
            float m20,
            float m21,
            float m22,
            float m23,
            float m30,
            float m31,
            float m32,
            float m33);
    explicit Matrix4(const Matrix3& iMat3);
    Matrix4(const Vector3& iPosition, const Quaternion& iRotation, const Vector3& iScale);

    void ToIdentity() {
        m[0][0] = 1.0f;
        m[0][1] = 0.0f;
        m[0][2] = 0.0f;
        m[0][3] = 0.0f;
        m[1][0] = 0.0f;
        m[1][1] = 1.0f;
        m[1][2] = 0.0f;
        m[1][3] = 0.0f;
        m[2][0] = 0.0f;
        m[2][1] = 0.0f;
        m[2][2] = 1.0f;
        m[2][3] = 0.0f;
        m[3][0] = 0.0f;
        m[3][1] = 0.0f;
        m[3][2] = 0.0f;
        m[3][3] = 1.0f;
    }

    void Set(unsigned int iX, unsigned int iY, float iValue);
    float Get(unsigned int iX, unsigned int iY) const;

    // Should we also do it with Vector3 ? Or maybe implicit conversion ?
    void Translate(const Vector3& iTrans);
    void Rotate(float iAngle, const Vector3& iAxis);
    void Scale(float iScale);
    void Scale(const Vector3& iScale);

    void SetRotation(const Matrix3& iRotation);

    Vector3 Translation() const;

    Matrix4 operator*(const Matrix4& iValue) const;
    Vector4 operator*(const Vector4& iVector) const;
    Vector3 operator*(const Vector3& iVector) const;

    bool operator==(const Matrix4& iRhs) const;

    const float* Data() const { return _m; }

    // Factory
    static Matrix4 MakeProjectionOrtho(float iLeft,
                                       float iRight,
                                       float iBottom,
                                       float iTop,
                                       float iNear,
                                       float iFar);
    static Matrix4 MakeProjectionOrtho(float iLeft, float iRight, float iBottom, float iTop);
    static Matrix4 MakeProjectionPerspective(float iFov, float iAspect, float iNear, float iFar);

    static Matrix4 Zero;

   private:
    union {
        float m[4][4];
        float _m[16];
    };

    float _DotWithIndex(int iX, int iY, const Matrix4& iMat) const;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_MATH_MATRIX4_H_
