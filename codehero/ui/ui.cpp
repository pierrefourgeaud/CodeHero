// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "ui/ui.h"
#include <queue>

namespace CodeHero {

UI::UI(std::shared_ptr<RenderSystem> iRS)
    : m_pRS(iRS) {}

void UI::Render() {
    std::queue<UIElement*> elements;
    std::vector<UIElement*>& children = m_RootElement.GetChildren();
    size_t size = children.size();
    for (size_t i = 0; i < size; ++i) {
        elements.push(children[i]);
    }

    // Going through the UI tree using a BFS algorithm
    while (!elements.empty()) {
        UIElement* el = elements.front();
        elements.pop();

        // Do something with the element
        
        
        children = el->GetChildren();
        size = children.size();
        for (size_t i = 0; i < size; ++i) {
            elements.push(children[i]);
        }
    }
}

} // namespace CodeHero

