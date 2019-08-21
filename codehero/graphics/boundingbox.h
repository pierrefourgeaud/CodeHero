// Copyright (c) 2019 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_BOUNDINGBOX_H_
#define CODEHERO_GRAPHICS_BOUNDINGBOX_H_

#include "core/math/vector3.h"

namespace CodeHero {

class BoundingBox {
   public:
    BoundingBox();
    ~BoundingBox();

    void Merge(const Vector3& iPoint);

    // Return the center of the box
    Vector3 Center() const;

   private:
    Vector3 m_Min;
    Vector3 m_Max;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_BOUNDINGBOX_H_