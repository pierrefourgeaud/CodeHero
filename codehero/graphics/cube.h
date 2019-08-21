// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_CUBE_H_
#define CODEHERO_GRAPHICS_CUBE_H_

#include "core/enginecontext.h"
#include "graphics/mesh.h"

namespace CodeHero {

class Cube : public Mesh {
public:
    OBJECT(Cube, Mesh)

    Cube(const std::shared_ptr<EngineContext>& iContext);
    ~Cube();

    static void RegisterObject(const std::shared_ptr<EngineContext>& iContext);
    static std::shared_ptr<Cube> Create(const std::shared_ptr<EngineContext>& iContext);
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_CUBE_H_
