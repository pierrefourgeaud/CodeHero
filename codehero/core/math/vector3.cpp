// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <math.h>
#include "./core/math/vector3.h"
#include "./core/math/utils.h"

namespace CodeHero {

const Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Backward(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::Down(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Left(-1.0f, 0.0f, 0.0f);

Vector3::Vector3(float iX, float iY, float iZ) {
    m_Vec[0] = iX;
    m_Vec[1] = iY;
    m_Vec[2] = iZ;
}

float Vector3::Length() const {
    return sqrtf((x() * x()) +
                 (y() * y()) +
                 (z() * z()));
}

Vector3& Vector3::Normalize() {
    float l = Length();

    if (l == 0) {
        ToIdentity();
    } else {
        m_Vec[0] /= l;
        m_Vec[1] /= l;
        m_Vec[2] /= l;
    }
    return *this;
}

Vector3 Vector3::Normalized() const {
    float l = Length();

    if (l == 0) {
        return Vector3();
    } else {
        return Vector3(m_Vec[0] / l, m_Vec[1] / l, m_Vec[2] / l);
    }
}

Vector3 Vector3::Cross(const Vector3& iVector) const {
    return {
        (y() * iVector.z()) - (z() * iVector.y()),
        (z() * iVector.x()) - (x() * iVector.z()),
        (x() * iVector.y()) - (y() * iVector.x()),
    };
}

float Vector3::Dot(const Vector3& iVector) const {
    return x() * iVector.x() + y() * iVector.y() + z() * iVector.z();
}

bool Vector3::operator==(const Vector3& iRhs) const {
    return FloatEqu(x(), iRhs.x()) &&
           FloatEqu(y(), iRhs.y()) &&
           FloatEqu(z(), iRhs.z());
}

Vector3 Vector3::operator+(const Vector3& iRhs) const {
    return {
        x() + iRhs.x(),
        y() + iRhs.y(),
        z() + iRhs.z()
    };
}

Vector3 Vector3::operator-(const Vector3& iRhs) const {
    return {
        x() - iRhs.x(),
        y() - iRhs.y(),
        z() - iRhs.z()
    };
}

Vector3 Vector3::operator*(const float iScalar) const {
    return {
        x() * iScalar,
        y() * iScalar,
        z() * iScalar
    };
}

Vector3& Vector3::operator*=(const float iScalar) {
    m_Vec[0] *= iScalar;
    m_Vec[1] *= iScalar;
    m_Vec[2] *= iScalar;
    return *this;
}

Vector3& Vector3::operator+=(const Vector3& iRhs) {
    m_Vec[0] += iRhs.x();
    m_Vec[1] += iRhs.y();
    m_Vec[2] += iRhs.z();
    return *this;
}

} // namespace CodeHero
