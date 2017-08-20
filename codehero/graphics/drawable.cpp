// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/drawable.h"

namespace CodeHero {

std::shared_ptr<Node> Drawable::GetNode() {
    std::shared_ptr<Node> node = m_pNode.lock();

    return node;
}

} // namespace CodeHero