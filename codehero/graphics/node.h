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

private:
    std::vector<Component*> m_Components;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_NODE_H_
