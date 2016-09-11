// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "./core/math/vector4.h"
#include "./core/math/utils.h"

namespace CodeHero {

Vector4::Vector4(float iX, float iY, float iZ, float iW) {
    m_Vec[0] = iX;
    m_Vec[1] = iY;
    m_Vec[2] = iZ;
    m_Vec[3] = iW;
}

Vector4::Vector4(const float iVec[4]) {
    m_Vec[0] = iVec[0];
    m_Vec[1] = iVec[1];
    m_Vec[2] = iVec[2];
    m_Vec[3] = iVec[3];
}

bool Vector4::operator==(const Vector4& iRhs) const {
    return FloatEqu(x(), iRhs.x()) &&
           FloatEqu(y(), iRhs.y()) &&
           FloatEqu(z(), iRhs.z()) &&
           FloatEqu(w(), iRhs.w());
}

Vector4& Vector4::operator+=(const Vector4& iVec) {
    m_Vec[0] += iVec.x();
    m_Vec[1] += iVec.y();
    m_Vec[2] += iVec.z();
    m_Vec[3] += iVec.w();
    return *this;
}

Vector4 Vector4::operator+(const Vector4& iVec) const {
    return Vector4(*this) += iVec;
}

Vector4 Vector4::operator*(const float iScalar) const {
    return Vector4(*this) *= iScalar;
}

Vector4& Vector4::operator*=(const float iScalar) {
    m_Vec[0] *= iScalar;
    m_Vec[1] *= iScalar;
    m_Vec[2] *= iScalar;
    m_Vec[3] *= iScalar;
    return *this;
}

} // namespace CodeHero
