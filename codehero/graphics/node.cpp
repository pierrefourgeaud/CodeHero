// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/node.h"
#include "graphics/drawable.h"

namespace CodeHero {

void Node::AddDrawable(Drawable* iDrawable) {
    m_Drawables.push_back(iDrawable);

    iDrawable->SetNode(shared_from_this());
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

} // namespace CodeHero

