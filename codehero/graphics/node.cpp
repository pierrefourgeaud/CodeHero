// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/node.h"

namespace CodeHero {

void Node::AddDrawable(Drawable* iDrawable) {
    m_Drawables.push_back(iDrawable);
}

} // namespace CodeHero

