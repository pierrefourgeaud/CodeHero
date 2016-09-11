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

bool Vector4::operator==(const Vector4& iRhs) const {
    return FloatEqu(x(), iRhs.x()) &&
           FloatEqu(y(), iRhs.y()) &&
           FloatEqu(z(), iRhs.z()) &&
           FloatEqu(w(), iRhs.w());
}

} // namespace CodeHero
