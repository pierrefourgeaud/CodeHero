// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/math/matrix4.h"
#include "core/math/matrix3.h"
#include "core/math/vector3.h"
#include "core/math/vector4.h"
#include "core/math/quaternion.h"
#include "core/math/utils.h"
#include "core/assert.h"

namespace CodeHero {

Matrix4 Matrix4::Zero(0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f);

Matrix4::Matrix4(float m00, float m01, float m02, float m03,
                 float m10, float m11, float m12, float m13,
                 float m20, float m21, float m22, float m23,
                 float m30, float m31, float m32, float m33) {
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
    m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

Matrix4::Matrix4(const Matrix3& iMat3) {
    SetRotation(iMat3);
}

Matrix4::Matrix4(const Vector3& iPosition, const Quaternion& iRotation, const Vector3& iScale) {
    SetRotation(iRotation.RotationMatrix().Scale(iScale));
    Translate(iPosition);
}

void Matrix4::Set(unsigned int iX, unsigned int iY, float iValue) {
    CH_ASSERT(iX < 4 && iY < 4);

    m[iX][iY] = iValue;
}

float Matrix4::Get(unsigned int iX, unsigned int iY) const {
    CH_ASSERT(iX < 4 && iY < 4);

    return m[iX][iY];
}

void Matrix4::Translate(const Vector3& iTrans) {
    m[3][0] = iTrans.x();
    m[3][1] = iTrans.y();
    m[3][2] = iTrans.z();
}

void Matrix4::Rotate(float iAngle, const Vector3& iVector) {
    const float a = DegToRad(iAngle);
    const float c = cosf(a);
    const float s = sinf(a);

    Vector3 axis = iVector.Normalized();
    Vector3 temp = (1.0f - c) * axis;

    // Create a rotation matrix
    Matrix3 rotation;
    rotation.m[0][0] = c + temp.x() * axis.x();
    rotation.m[0][1] = temp.x() * axis.y() + s * axis.z();
    rotation.m[0][2] = temp.x() * axis.z() - s * axis.y();

    rotation.m[1][0] = temp.y() * axis.x() - s * axis.z();
    rotation.m[1][1] = c + temp.y() * axis.y();
    rotation.m[1][2] = temp.y() * axis.z() + s * axis.x();

    rotation.m[2][0] = temp.z() * axis.x() + s * axis.y();
    rotation.m[2][1] = temp.z() * axis.y() - s * axis.x();
    rotation.m[2][2] = c + temp.z() * axis.z();

    Vector4 x = Vector4(m[0]) * rotation.m[0][0] + Vector4(m[1]) * rotation.m[0][1] + Vector4(m[2]) * rotation.m[0][2];
    Vector4 y = Vector4(m[0]) * rotation.m[1][0] + Vector4(m[1]) * rotation.m[1][1] + Vector4(m[2]) * rotation.m[1][2];
    Vector4 z = Vector4(m[0]) * rotation.m[2][0] + Vector4(m[1]) * rotation.m[2][1] + Vector4(m[2]) * rotation.m[2][2];
    m[0][0] = x.x(); m[0][1] = x.y(); m[0][2] = x.z(); m[0][3] = x.w();
    m[1][0] = y.x(); m[1][1] = y.y(); m[1][2] = y.z(); m[1][3] = y.w();
    m[2][0] = z.x(); m[2][1] = z.y(); m[2][2] = z.z(); m[2][3] = z.w();
}

void Matrix4::Scale(float iScale) {
    m[0][0] *= iScale;
    m[1][1] *= iScale;
    m[2][2] *= iScale;
}

void Matrix4::Scale(const Vector3& iScale) {
    m[0][0] *= iScale.x();
    m[1][1] *= iScale.y();
    m[2][2] *= iScale.z();
}

void Matrix4::SetRotation(const Matrix3& iMat3) {
    m[0][0] = iMat3.Get(0, 0); m[0][1] = iMat3.Get(0, 1); m[0][2] = iMat3.Get(0, 2); m[0][3] = 0.0f;
    m[1][0] = iMat3.Get(1, 0); m[1][1] = iMat3.Get(1, 1); m[1][2] = iMat3.Get(1, 2); m[1][3] = 0.0f;
    m[2][0] = iMat3.Get(2, 0); m[2][1] = iMat3.Get(2, 1); m[2][2] = iMat3.Get(2, 2); m[2][3] = 0.0f;
    m[3][0] = 0.0f;            m[3][1] = 0.0f;            m[3][2] = 0.0f;            m[3][3] = 1.0f;
}

Matrix4 Matrix4::operator*(const Matrix4& iValue) const {
    Matrix4 mat;

    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            mat.m[x][y] = _DotWithIndex(x, y, iValue);
        }
    }

    return mat;
}

Vector4 Matrix4::operator*(const Vector4& iVector) const {
    return {
        iVector.x() * m[0][0] + iVector.y() * m[0][1] + iVector.w() * m[0][2] + iVector.w() * m[0][3],
        iVector.x() * m[1][0] + iVector.y() * m[1][1] + iVector.w() * m[1][2] + iVector.w() * m[1][3],
        iVector.x() * m[2][0] + iVector.y() * m[2][1] + iVector.w() * m[2][2] + iVector.w() * m[2][3],
        iVector.x() * m[3][0] + iVector.y() * m[3][1] + iVector.w() * m[3][2] + iVector.w() * m[3][3]
    };
}

bool Matrix4::operator==(const Matrix4& iRhs) const {
    for (int i = 0; i < 16; ++i) {
        if (!FloatEqu(_m[i], iRhs._m[i])) {
            return false;
        }
    }

    return true;
}

float Matrix4::_DotWithIndex(int iX, int iY, const Matrix4& iMat) const {
    float res = 0.0f;
    for (int i = 0; i < 4; ++i) {
        res += m[iX][i] * iMat.m[i][iY];
    }

    return res;
}

// Statics
Matrix4 Matrix4::MakeProjectionPerspective(float iFov, float iAspect, float iNear, float iFar) {
    CH_ASSERT(abs(iAspect - Epsilon()) > 0.0f);

    const float tanHalfFovy = tan(DegToRad(iFov) / 2.0f);

    Matrix4 result = Matrix4::Zero;
    result.m[0][0] = 1.0f / (iAspect * tanHalfFovy);
    result.m[1][1] = 1.0f / tanHalfFovy;
    result.m[2][3] = 1.0f;

    result.m[2][2] = (iFar + iNear) / (iFar - iNear);
    result.m[3][2] = -(2.0f * iFar * iNear) / (iFar - iNear);

    return std::move(result);
}

} // namespace CodeHero