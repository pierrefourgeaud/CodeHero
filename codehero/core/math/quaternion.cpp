// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/math/quaternion.h"
#include "core/math/vector3.h"
#include "core/math/matrix3.h"
#include "core/math/utils.h"
#include <math.h>

namespace CodeHero {

void Quaternion::FromAngleAndAxis(float iAngle, const Vector3& iAxis) {
    Vector3 normAxis = iAxis;
    normAxis.Normalize();
    
    float radians = DegToRad(iAngle);
    float sinAngle = sinf(radians);
    float cosAngle = cosf(radians);

    m_W = cosAngle;
    m_X = normAxis.x() * sinAngle;
    m_Y = normAxis.y() * sinAngle;
    m_Z = normAxis.z() * sinAngle;
}

// This function is inspired from Urho3D FromEulerAngles
// (no need to try to come up with something different here...)
void Quaternion::FromEulerAngles(float iX, float iY, float iZ) {
    // Order of rotations: Z first, then X, then Y
    // (like typical FPS camera with gimbal lock at top/bottom)
    float x = DegToRad(iX) * 0.5f;
    float y = DegToRad(iY) * 0.5f;
    float z = DegToRad(iZ) * 0.5f;
    float sinX = sinf(x);
    float cosX = cosf(x);
    float sinY = sinf(y);
    float cosY = cosf(y);
    float sinZ = sinf(z);
    float cosZ = cosf(z);

    m_W = cosY * cosX * cosZ + sinY * sinX * sinZ;
    m_X = cosY * sinX * cosZ + sinY * cosX * sinZ;
    m_Y = sinY * cosX * cosZ - cosY * sinX * sinZ;
    m_Z = cosY * cosX * sinZ - sinY * sinX * cosZ;
}

void Quaternion::FromRotationMatrix(const Matrix3& iMat) {
    float fourXSquaredMinus1 = iMat.Get(0, 0) - iMat.Get(1, 1) - iMat.Get(2, 2);
    float fourYSquaredMinus1 = iMat.Get(1, 1) - iMat.Get(0, 0) - iMat.Get(2, 2);
    float fourZSquaredMinus1 = iMat.Get(2, 2) - iMat.Get(0, 0) - iMat.Get(1, 1);
    float fourWSquaredMinus1 = iMat.Get(0, 0) + iMat.Get(1, 1) + iMat.Get(2, 2);

    int biggestIndex = 0;
    float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
    if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) {
        fourBiggestSquaredMinus1 = fourXSquaredMinus1;
        biggestIndex = 1;
    }
    if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) {
        fourBiggestSquaredMinus1 = fourYSquaredMinus1;
        biggestIndex = 2;
    }
    if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) {
        fourBiggestSquaredMinus1 = fourZSquaredMinus1;
        biggestIndex = 3;
    }

    float biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
    float mult = 0.25f / biggestVal;

    switch (biggestIndex) {
    case 0:
        m_W = biggestVal;
        m_X = (iMat.Get(1, 2) - iMat.Get(2, 1)) * mult;
        m_Y = (iMat.Get(2, 0) - iMat.Get(0, 2)) * mult;
        m_Z = (iMat.Get(0, 1) - iMat.Get(1, 0)) * mult;
        break;
    case 1:
        m_W = (iMat.Get(1, 2) - iMat.Get(2, 1)) * mult;
        m_X = biggestVal;
        m_Y = (iMat.Get(0, 1) + iMat.Get(1, 0)) * mult;
        m_Z = (iMat.Get(2, 0) + iMat.Get(0, 2)) * mult;
        break;
    case 2:
        m_W = (iMat.Get(2, 0) - iMat.Get(0, 2)) * mult;
        m_X = (iMat.Get(0, 1) + iMat.Get(1, 0)) * mult;
        m_Y = biggestVal;
        m_Z = (iMat.Get(1, 2) + iMat.Get(2, 1)) * mult;
        break;
    case 3:
        m_W = (iMat.Get(0, 1) - iMat.Get(1, 0)) * mult;
        m_X = (iMat.Get(2, 0) + iMat.Get(0, 2)) * mult;
        m_Y = (iMat.Get(1, 2) + iMat.Get(2, 1)) * mult;
        m_Z = biggestVal;
        break;

    default:
        // Should never reach here - Simply for sanity
        break;
    }
}

void Quaternion::FromAxis(const Vector3& iXAxis, const Vector3& iYAxis, const Vector3& iZAxis) {
    Matrix3 matrix(iXAxis.x(), iYAxis.x(), iZAxis.x(),
                   iXAxis.y(), iYAxis.y(), iZAxis.y(),
                   iXAxis.z(), iYAxis.z(), iZAxis.z());

    FromRotationMatrix(matrix);
}

void Quaternion::FromLookAt(const Vector3& iDirection, const Vector3& iUp) {
    Vector3 direction = -(iDirection.Normalized());
    Vector3 right = (direction).Cross(iUp).Normalize();
    Vector3 up = right.Cross((direction));

    Matrix3 matrix(right.x(), up.x(), direction.x(),
                   right.y(), up.y(), direction.y(),
                   right.z(), up.z(), direction.z());

    FromRotationMatrix(matrix);
}

Matrix3 Quaternion::RotationMatrix() const {
    float xx(m_X * m_X);
    float yy(m_Y * m_Y);
    float zz(m_Z * m_Z);
    float xz(m_X * m_Z);
    float xy(m_X * m_Y);
    float yz(m_Y * m_Z);
    float wx(m_W * m_X);
    float wy(m_W * m_Y);
    float wz(m_W * m_Z);

    return Matrix3(
        1.0f - 2.0f * (yy + zz), 2.0f * (xy + wz)       , 2.0f * (xz - wy)       ,
        2.0f * (xy - wz)       , 1.0f - 2.0f * (xx + zz), 2.0f * (yz + wx)       ,
        2.0f * (xz + wy)       , 2.0f * (yz - wx)       , 1.0f - 2.0f * (xx + yy)
    );
}

Vector3 Quaternion::operator*(const Vector3& iRhs) const {
    Vector3 quatVec(m_X, m_Y, m_Z);
    Vector3 uv(quatVec.Cross(iRhs));
    Vector3 uuv(quatVec.Cross(uv));

    return iRhs + ((uv * m_W) + uuv) * 2.0f;
}

} // namespace CodeHero