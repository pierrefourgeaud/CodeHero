// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_MATH_MATRIX3_H_
#define CODEHERO_CORE_MATH_MATRIX3_H_

#include <math.h>
#include "core/math/utils.h"

namespace CodeHero {

// Forward declaration
class Vector3;

/**
* @brief Matrix 33f
*
* Used for rotation and scaling
*/
class Matrix3 {
public:
    Matrix3() { ToIdentity(); }
    Matrix3(float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22);

    void ToIdentity() {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
    }

    void Set(unsigned int iX, unsigned int iY, float iValue);
    float Get(unsigned int iX, unsigned int iY) const;

    Matrix3 operator*(const Matrix3& iRhs) const;
    Vector3 operator*(const Vector3& iVector) const;

    bool operator==(const Matrix3& iRhs) const;

    const float* Data() const { return _m; }

    // TODO(pierre) Make From/To methods (FromQuaternion, ToQuat, FromAxisAngle, ToAxisAngle, ...)

private:
    union {
        float _m[9];
        float m[3][3];
    };
};

} // namespace CodeHero

#endif // CODEHERO_CORE_MATH_MATRIX3_H_
