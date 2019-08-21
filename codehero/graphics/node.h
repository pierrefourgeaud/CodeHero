// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_NODE_H_
#define CODEHERO_GRAPHICS_NODE_H_

#include <memory>
#include <vector>
#include "core/math/matrix4.h"
#include "core/math/quaternion.h"
#include "core/math/vector3.h"
#include "core/serializable.h"

namespace CodeHero {

// Forward declaration
class Drawable;
class Scene;
class EngineContext;

enum TransformSpace { TS_Local = 0, TS_Parent, TS_World };

class Node : public Serializable, public std::enable_shared_from_this<Node> {
public:
    OBJECT(Node, Serializable);

    Node(const std::shared_ptr<EngineContext>& iContext);
    virtual ~Node() {}

    static void RegisterObject(const std::shared_ptr<EngineContext>& iContext);
    static std::shared_ptr<Node> Create(const std::shared_ptr<EngineContext>& iContext);

    template <class T, class... Args>
    std::shared_ptr<T> CreateDrawable(const std::shared_ptr<EngineContext>& iContext,
                                      Args&&... iArgs) {
        std::shared_ptr<T> newComponent(new T(iContext, std::forward<Args>(iArgs)...));
        AddDrawable(newComponent);
        return newComponent;
    }

    void AddDrawable(const std::shared_ptr<Drawable>& iComponent);
    const std::vector<std::shared_ptr<Drawable>>& GetComponents() const { return m_Drawables; }

    std::shared_ptr<Node> CreateChild();
    void SetParent(const std::shared_ptr<Node>& iParent) { m_pParent = iParent; }
    void SetScene(const std::shared_ptr<Scene>& iScene);
    std::shared_ptr<Scene> GetScene() const { return m_pScene; }

    // Mostly used for serialization
    void AddChild(const std::shared_ptr<Node>& iChild);

    const std::vector<std::shared_ptr<Node>>& GetChildren() const { return m_Children; }

    void Update();
    void MarkDirty();

    void SetScale(float iScale);
    void SetScale(const Vector3& iScale);
    void SetPosition(const Vector3& iPosition);
    void SetRotation(const Quaternion& iRotation);
    const Vector3& GetPosition() const { return m_Position; }
    const Quaternion& GetRotation() const { return m_Rotation; }
    const Vector3& GetScale() const { return m_Scale; }

    void Translate(const Vector3& iDelta, TransformSpace iSpace = TS_Local);
    void Rotate(const Quaternion& iDelta, TransformSpace iSpace = TS_Local);
    void Scale(float iDelta);
    void Scale(const Vector3& iDelta);

    Matrix4 GetTransform();
    // This takes in cound the parents node
    Matrix4 GetWorldTransform();

    bool IsScene() const { return m_IsScene; }

protected:
    // We cannot use m_pScene == nullptr for this purpose because
    // a node might be created but it does not require to be IN a scene
    // before being used
    bool m_IsScene = false;

private:
    std::shared_ptr<Node> m_pParent;
    std::shared_ptr<Scene> m_pScene;
    std::vector<std::shared_ptr<Drawable>> m_Drawables;
    std::vector<std::shared_ptr<Node>> m_Children;

    bool m_IsDirty = true;

    Vector3 m_Scale{1.0f, 1.0f, 1.0f};
    Vector3 m_Position;
    Quaternion m_Rotation;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_NODE_H_