// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/node.h"

namespace CodeHero {

void Node::AddComponent(Component* iComponent) {
    m_Components.push_back(iComponent);
}

} // namespace CodeHero

