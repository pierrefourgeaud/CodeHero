// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_NODE_H_
#define CODEHERO_GRAPHICS_NODE_H_ 

#include <vector>

namespace CodeHero {

// Forward declaration
class Drawable;

class Node {
public:

    template <class T>
    Drawable* CreateDrawable() {
        Drawable* newComponent = new T;
        AddDrawable(newComponent);
        return newComponent;
    }

    void AddDrawable(Drawable* iComponent);
    const std::vector<Drawable*>& GetComponents() const { return m_Drawables; }

    Node* CreateChild() {
        Node* node = new Node;
        m_Children.push_back(node);
        return node;
    }

    const std::vector<Node*>& GetChildren() const { return m_Children; }

private:
    std::vector<Drawable*> m_Drawables;
    std::vector<Node*> m_Children;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_NODE_H_
