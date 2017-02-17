// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_NODE_H_
#define CODEHERO_GRAPHICS_NODE_H_ 

#include <vector>

namespace CodeHero {

// Forward declaration
class Component;

class Node {
public:

    template <class T>
    Component* CreateComponent() {
        Component* newComponent = new T;
        AddComponent(newComponent);
        return newComponent;
    }

    void AddComponent(Component* iComponent);
    const std::vector<Component*>& GetComponents() const { return m_Components; }

    Node* CreateChild() {
        Node* node = new Node;
        m_Children.push_back(node);
        return node;
    }

    const std::vector<Node*>& GetChildren() const { return m_Children; }

private:
    std::vector<Component*> m_Components;
    std::vector<Node*> m_Children;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_NODE_H_
