// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_PLANE_H_
#define CODEHERO_GRAPHICS_PLANE_H_ 

#include "graphics/mesh.h"
#include "core/enginecontext.h"

namespace CodeHero {

class Plane : public Mesh {
public:
    Plane(const std::shared_ptr<EngineContext>& iContext);
    ~Plane();

private:
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_PLANE_H_