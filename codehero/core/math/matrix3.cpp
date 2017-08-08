// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/math/matrix3.h"
#include "core/math/quaternion.h"
#include "core/math/vector3.h"
#include "core/assert.h"

namespace CodeHero {

Matrix3::Matrix3(float m00, float m01, float m02,
                 float m10, float m11, float m12,
                 float m20, float m21, float m22) {
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
}

void Matrix3::Set(unsigned int iX, unsigned int iY, float iValue) {
    CH_ASSERT(iX < 3 && iY < 3);

    m[iX][iY] = iValue;
}

float Matrix3::Get(unsigned int iX, unsigned int iY) const {
    CH_ASSERT(iX < 3 && iY < 3);

    return m[iX][iY];
}

Matrix3 Matrix3::operator*(const Matrix3& iRhs) const {
    return Matrix3(
        m[0][0] * iRhs.m[0][0] + m[0][1] * iRhs.m[1][0] + m[0][2] * iRhs.m[2][0],
        m[0][0] * iRhs.m[0][1] + m[0][1] * iRhs.m[1][1] + m[0][2] * iRhs.m[2][1],
        m[0][0] * iRhs.m[0][2] + m[0][1] * iRhs.m[1][2] + m[0][2] * iRhs.m[2][2],
        m[1][0] * iRhs.m[0][0] + m[1][1] * iRhs.m[1][0] + m[1][2] * iRhs.m[2][0],
        m[1][0] * iRhs.m[0][1] + m[1][1] * iRhs.m[1][1] + m[1][2] * iRhs.m[2][1],
        m[1][0] * iRhs.m[0][2] + m[1][1] * iRhs.m[1][2] + m[1][2] * iRhs.m[2][2],
        m[2][0] * iRhs.m[0][0] + m[2][1] * iRhs.m[1][0] + m[2][2] * iRhs.m[2][0],
        m[2][0] * iRhs.m[0][1] + m[2][1] * iRhs.m[1][1] + m[2][2] * iRhs.m[2][1],
        m[2][0] * iRhs.m[0][2] + m[2][1] * iRhs.m[1][2] + m[2][2] * iRhs.m[2][2]
    );
}

Vector3 Matrix3::operator*(const Vector3& iVector) const {
    return {
        iVector.x() * m[0][0] + iVector.y() * m[0][1] + iVector.z() * m[0][2],
        iVector.x() * m[1][0] + iVector.y() * m[1][1] + iVector.z() * m[1][2],
        iVector.x() * m[2][0] + iVector.y() * m[2][1] + iVector.z() * m[2][2]
    };
}

Matrix3 Matrix3::operator-() const {
    return Matrix3(
        -m[0][0], -m[0][1], -m[0][2],
        -m[1][0], -m[1][1], -m[1][2],
        -m[2][0], -m[2][1], -m[2][2]
    );
}

bool Matrix3::operator==(const Matrix3& iRhs) const {
    for (int i = 0; i < 9; ++i) {
        if (!FloatEqu(_m[i], iRhs._m[i])) {
            return false;
        }
    }

    return true;
}

Matrix3& Matrix3::Transpose() {
    std::swap(m[1][0], m[0][1]);
    std::swap(m[2][0], m[0][2]);
    std::swap(m[1][2], m[2][1]);

    return *this;
}

Matrix3 Matrix3::Transposed() const {
    return Matrix3(
        m[0][0], m[1][0], m[2][0],
        m[0][1], m[1][1], m[2][1],
        m[0][2], m[1][2], m[2][2]
    );
}

void Matrix3::FromQuaternion(const Quaternion& iQuat) {
    *this = iQuat.RotationMatrix();
}

} // namespace CodeHero