// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_NODE_H_
#define CODEHERO_GRAPHICS_NODE_H_ 

#include <memory>
#include <vector>
#include "core/math/vector3.h"
#include "core/math/matrix4.h"
#include "core/math/quaternion.h"

namespace CodeHero {

// Forward declaration
class Drawable;
class Scene;

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

    std::shared_ptr<Node> CreateChild();
    void SetParent(const std::shared_ptr<Node>& iParent) { m_pParent = iParent; }
    void SetScene(const std::shared_ptr<Scene>& iScene) { m_pScene = iScene; }

    const std::vector<std::shared_ptr<Node>>& GetChildren() const { return m_Children; }

    void Update();
    void MarkDirty();

    void SetScale(float iScale);
    void SetScale(const Vector3& iScale);
    void SetPosition(const Vector3& iPosition);
    void SetRotation(const Quaternion& iRotation);
    const Vector3& GetPosition() const { return m_Position; }
    const Quaternion& GetRotation() const { return m_Rotation; }

    void Translate(const Vector3& iDelta, TransformSpace iSpace = TS_Local);
    void Rotate(const Quaternion& iDelta, TransformSpace iSpace = TS_Local);
    void Scale(float iDelta);
    void Scale(const Vector3& iDelta);

    Matrix4 GetTransform();
    // This takes in cound the parents node
    Matrix4 GetWorldTransform();

private:
    std::shared_ptr<Node> m_pParent;
    std::shared_ptr<Scene> m_pScene;
    std::vector<Drawable*> m_Drawables;
    std::vector<std::shared_ptr<Node>> m_Children;

    bool m_IsDirty = true;

    Vector3 m_Scale{1.0f, 1.0f, 1.0f};
    Vector3 m_Position;
    Quaternion m_Rotation;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_NODE_H_