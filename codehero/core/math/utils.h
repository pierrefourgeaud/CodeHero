// Copyright (c) 2016 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_MATH_UTILS_H
#define CODEHERO_MATH_UTILS_H

namespace CodeHero {

static bool FloatEqu(float iLhs, float iRhs, float iEps = 1e-6) {
    float delta = iRhs - iLhs;
    if (delta < 0.0) {
        return delta >= -iEps;
    } else {
        return delta <= iEps;
    }
}

} // namespace CodeHero

#endif // CODEHERO_MATH_UTILS_H
