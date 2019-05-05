// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/node.h"
#include "core/assert.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/type_traits/objectdefinition.h"
#include "graphics/drawable.h"
#include "graphics/light.h"
#include "graphics/scene.h"

namespace CodeHero {

Node::Node(const std::shared_ptr<EngineContext>& iContext) : Serializable(iContext) {}

void Node::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(Node);

    CH_OBJECT_ATTRIBUTE_CAST(Node, "Node", std::shared_ptr<Serializable>, Node,
                             Variant::Value::VVT_SerializablePtr, nullptr, &Node::AddChild);
    CH_OBJECT_ATTRIBUTE_CAST(Node, "Components", std::shared_ptr<Serializable>, Drawable,
                             Variant::Value::VVT_SerializablePtr, nullptr, &Node::AddDrawable);
    CH_OBJECT_ATTRIBUTE(Node, "Position", Vector3, Variant::Value::VVT_Vector3, &Node::GetPosition,
                        &Node::SetPosition);
    CH_OBJECT_ATTRIBUTE(Node, "Rotation", Quaternion, Variant::Value::VVT_Quaternion,
                        &Node::GetRotation, &Node::SetRotation);
    CH_OBJECT_ATTRIBUTE(Node, "Scale", Vector3, Variant::Value::VVT_Vector3, &Node::GetScale,
                        static_cast<void (Node::*)(const Vector3&)>(&Node::SetScale));
}

std::shared_ptr<Node> Node::Create(const std::shared_ptr<EngineContext>& iContext) {
    return std::make_shared<Node>(iContext);
}

void Node::AddDrawable(const std::shared_ptr<Drawable>& iDrawable) {
    // You should not be able to add drawables directly on the scene, use child nodes for it
    CH_ASSERT(IsScene() == false);

    m_Drawables.push_back(iDrawable);

    // We might not have a scene yet, in that case we skip the light registration and
    // push it to when we add the node to a scene
    if (iDrawable->GetDrawableType() == Drawable::DT_Light && m_pScene) {
        // Here we can safely downcast
        m_pScene->RegisterSceneLight(std::static_pointer_cast<Light>(iDrawable));
    }

    iDrawable->SetNode(shared_from_this());
}

std::shared_ptr<Node> Node::CreateChild() {
    std::shared_ptr<Node> node = std::make_shared<Node>(m_pContext);

    AddChild(node);

    return node;
}

void Node::SetScene(const std::shared_ptr<Scene>& iScene) {
    m_pScene = iScene;

    // Make sure all the children get a reference to the scene
    for (auto& c : m_Children) {
        // We should make sure that we don't loop
        if (c->GetScene() != iScene) {
            c->SetScene(iScene);
        }
    }

    // Since the node didn't have a scene until now, we register the lights
    // (cf. AddDrawables)
    for (auto& d : m_Drawables) {
        if (d->GetDrawableType() == Drawable::DT_Light) {
            m_pScene->RegisterSceneLight(std::static_pointer_cast<Light>(d));
        }
    }
}

void Node::AddChild(const std::shared_ptr<Node>& iChild) {
    m_Children.push_back(iChild);
    iChild->SetParent(shared_from_this());

    if (!IsScene()) {
        iChild->SetScene(m_pScene);
    } else {
        // TODO(pierre) This is virtually safe. A Node without scene is a scene.
        //              BUT: We can safely assume that we could create a node without parent.
        //              THEN: Disallowing creation of Node unless via CreateChild would be a fair
        //              solution.
        std::shared_ptr<Scene> s = std::static_pointer_cast<Scene>(shared_from_this());
        iChild->SetScene(s);
    }
}

void Node::Update() {
    m_IsDirty = false;
}

void Node::MarkDirty() {
    // Already marked as dirty...
    if (m_IsDirty) {
        return;
    }
    m_IsDirty = true;

    // First mark all the components as dirty
    for (auto& it : m_Drawables) {
        it->SetIsDirty(true);
    }

    // Then repeat this operation on all the child nodes
    for (auto& it : m_Children) {
        it->MarkDirty();
    }
}

void Node::SetScale(float iScale) {
    SetScale({iScale, iScale, iScale});
}

void Node::SetScale(const Vector3& iScale) {
    m_Scale = iScale;

    MarkDirty();
}

void Node::SetPosition(const Vector3& iPosition) {
    m_Position = iPosition;

    MarkDirty();
}

void Node::SetRotation(const Quaternion& iRotation) {
    m_Rotation = iRotation;

    MarkDirty();
}

void Node::Translate(const Vector3& iDelta, TransformSpace iSpace /*= TS_Local*/) {
    switch (iSpace) {
        case TS_Local: m_Position += m_Rotation * iDelta; break;

        case TS_Parent: m_Position += iDelta; break;

        case TS_World:
            // TODO(pierre) To add when we have the GetWorldTransform available from Node
            //              for the parent.
            break;

        default:
            // Will never reach here
            break;
    }

    MarkDirty();
}

void Node::Rotate(const Quaternion& iDelta, TransformSpace iSpace /*= TS_Local*/) {
    switch (iSpace) {
        case TS_Local: m_Rotation = (m_Rotation * iDelta).Normalized(); break;

        case TS_Parent: m_Rotation = (iDelta * m_Rotation).Normalized(); break;

        case TS_World:
            // TODO(pierre) To add when we have the GetWorldTransform available from Node
            //              for the parent.
            break;

        default:
            // Will never reach here
            break;
    }

    MarkDirty();
}

void Node::Scale(float iDelta) {
    Scale({iDelta, iDelta, iDelta});
}

void Node::Scale(const Vector3& iDelta) {
    m_Scale *= iDelta;

    MarkDirty();
}

Matrix4 Node::GetTransform() {
    return Matrix4(m_Position, m_Rotation, m_Scale);
}

Matrix4 Node::GetWorldTransform() {
    // TODO(pierre) We should cache the transform and recalculate only if needed
    Matrix4 transform = GetTransform();

    if (!m_pParent) {
        return transform;
    } else {
        return m_pParent->GetWorldTransform() * transform;
    }
}

} // namespace CodeHero
