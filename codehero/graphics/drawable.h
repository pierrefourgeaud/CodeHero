// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_DRAWABLE_H_
#define CODEHERO_GRAPHICS_DRAWABLE_H_ 

#include "core/object.h"

namespace CodeHero {

// Forward declaration
class Node;

class Drawable : public Object {
public:
    enum DrawableType {
        DT_Light,
        DT_Geometry
    };

    Drawable(const std::shared_ptr<EngineContext>& iContext, DrawableType iType)
        : Object(iContext)
        , m_Type(iType) {}
    virtual ~Drawable() {}

    DrawableType GetDrawableType() const { return m_Type; }

    void SetNode(const std::shared_ptr<Node>& iNode) { m_pNode = iNode; }

protected:
    std::weak_ptr<Node> m_pNode;

private:
    DrawableType m_Type;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_DRAWABLE_H_
