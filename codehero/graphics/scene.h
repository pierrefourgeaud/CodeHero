// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_SCENE_H_
#define CODEHERO_GRAPHICS_SCENE_H_ 

#include "graphics/node.h"

namespace CodeHero {

// Forward declaration
class Camera;

// Scene is simply a rootNode.
// It will inerit everything everything for the node
// But with extra properties
class Scene : public Node {
public:
    Scene();
    ~Scene();

    void Render(Camera* iCamera);

private:
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_SCENE_H_
