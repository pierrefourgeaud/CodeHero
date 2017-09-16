// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_MATH_UTILS_H
#define CODEHERO_MATH_UTILS_H

#include <limits>

namespace CodeHero {

static const double PI = 3.14159265358979323846264338327950288;

static inline float Epsilon() {
    return std::numeric_limits<float>::epsilon();
}

static inline float DegToRad(float iDeg) {
    return iDeg * (static_cast<float>(PI) / 180.0f);
}

static inline bool FloatEqu(float iLhs, float iRhs, float iEps = Epsilon()) {
    float delta = iRhs - iLhs;
    if (delta < 0.0) {
        return delta >= -iEps;
    } else {
        return delta <= iEps;
    }
}

static inline int Clamp(int iValue, int iMin, int iMax)
{
    if (iValue < iMin) {
        return iMin;
    } else if (iValue > iMax) {
        return iMax;
    } else {
        return iValue;
    }
}

static inline float Clamp(float iValue, float iMin, float iMax)
{
    if (iValue < iMin) {
        return iMin;
    } else if (iValue > iMax) {
        return iMax;
    } else {
        return iValue;
    }
}

} // namespace CodeHero

#endif // CODEHERO_MATH_UTILS_H
