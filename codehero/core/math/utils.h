// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_MATH_UTILS_H
#define CODEHERO_MATH_UTILS_H

#include <limits>

namespace CodeHero {

static const double PI = 3.14159265358979323846264338327950288;

static float Epsilon() {
    return std::numeric_limits<float>::epsilon();
}

static float DegToRad(float iDeg) {
    return iDeg * (static_cast<float>(PI) / 180.0f);
}

static bool FloatEqu(float iLhs, float iRhs, float iEps = Epsilon()) {
    float delta = iRhs - iLhs;
    if (delta < 0.0) {
        return delta >= -iEps;
    } else {
        return delta <= iEps;
    }
}

} // namespace CodeHero

#endif // CODEHERO_MATH_UTILS_H