// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_SCENE_H_
#define CODEHERO_GRAPHICS_SCENE_H_ 

namespace CodeHero {

class Scene {
public:
    Scene();
    ~Scene();

    void Render();

private:
    Node* m_pRootNode;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_SCENE_H_
