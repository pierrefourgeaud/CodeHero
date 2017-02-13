// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/scene.h"
#include "graphics/node.h"

namespace CodeHero {

Scene::Scene()
    : m_pRootNode(new Node) {}

Scene::~Scene() {}

void Scene::Render() {
}

} // namespace CodeHero

