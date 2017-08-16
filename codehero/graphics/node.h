// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_NODE_H_
#define CODEHERO_GRAPHICS_NODE_H_ 

#include <memory>
#include <vector>
#include "core/math/vector3.h"
#include "core/math/quaternion.h"

namespace CodeHero {

// Forward declaration
class Drawable;

enum TransformSpace {
    TS_Local = 0,
    TS_Parent,
    TS_World
};

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
        node->SetParent(shared_from_this());
        m_Children.push_back(node);
        return node;
    }
    void SetParent(const std::shared_ptr<Node> iParent) { m_pParent = iParent; }

    const std::vector<std::shared_ptr<Node>>& GetChildren() const { return m_Children; }

    void Update();
    void MarkDirty();

    void SetPosition(const Vector3& iPosition);
    void SetRotation(const Quaternion& iRotation);
    const Vector3& GetPosition() const { return m_Position; }
    const Quaternion& GetRotation() const { return m_Rotation; }

    void Translate(const Vector3& iDelta, TransformSpace iSpace = TS_Local);

private:
    std::shared_ptr<Node> m_pParent;
    std::vector<Drawable*> m_Drawables;
    std::vector<std::shared_ptr<Node>> m_Children;

    bool m_IsDirty = true;

    Vector3 m_Position;
    Quaternion m_Rotation;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_NODE_H_
