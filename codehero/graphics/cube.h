// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_CUBE_H_
#define CODEHERO_GRAPHICS_CUBE_H_ 

#include "graphics/mesh.h"

namespace CodeHero {

class Cube : public Mesh{
public:
    Cube(const Vector3& iPosition, float iSize);
    ~Cube();

private:
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_CUBE_H_
