// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/node.h"
#include "graphics/drawable.h"
#include "graphics/scene.h"

namespace CodeHero {

void Node::AddDrawable(const std::shared_ptr<Drawable>& iDrawable) {
    m_Drawables.push_back(iDrawable);

    iDrawable->SetNode(shared_from_this());
}

std::shared_ptr<Node> Node::CreateChild() {
    std::shared_ptr<Node> node = std::make_shared<Node>();
    node->SetParent(shared_from_this());

    if (m_pScene.get()) {
        node->SetScene(m_pScene);
    } else {
        // TODO(pierre) This is virtually safe. A Node without scene is a scene.
        //              BUT: We can safely assume that we could create a node without parent.
        //              THEN: Disallowing creation of Node unless via CreateChild would be a fair solution.
        std::shared_ptr<Scene> s = std::static_pointer_cast<Scene>(shared_from_this());
        node->SetScene(s);
    }

    m_Children.push_back(node);
    return node;
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
    case TS_Local:
        m_Position += m_Rotation * iDelta;
        break;

    case TS_Parent:
        m_Position += iDelta;
        break;

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
    case TS_Local:
        m_Rotation = (m_Rotation * iDelta).Normalized();
        break;

    case TS_Parent:
        m_Rotation = (iDelta * m_Rotation).Normalized();
        break;

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

