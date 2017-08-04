// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_NODE_H_
#define CODEHERO_GRAPHICS_NODE_H_ 

#include <memory>
#include <vector>

namespace CodeHero {

// Forward declaration
class Drawable;

class Node : public std::enable_shared_from_this<Node> {
public:

    template <class T>
    Drawable* CreateDrawable() {
        Drawable* newComponent = new T;
        AddDrawable(newComponent);
        return newComponent;
    }

    void AddDrawable(Drawable* iComponent);
    const std::vector<Drawable*>& GetComponents() const { return m_Drawables; }

    std::shared_ptr<Node> CreateChild() {
        std::shared_ptr<Node> node = std::make_shared<Node>();
        m_Children.push_back(node);
        return node;
    }

    const std::vector<std::shared_ptr<Node>>& GetChildren() const { return m_Children; }

private:
    std::vector<Drawable*> m_Drawables;
    std::vector<std::shared_ptr<Node>> m_Children;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_NODE_H_
