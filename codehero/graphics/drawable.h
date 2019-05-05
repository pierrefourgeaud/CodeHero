// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_DRAWABLE_H_
#define CODEHERO_GRAPHICS_DRAWABLE_H_

#include "core/serializable.h"

namespace CodeHero {

// Forward declaration
class Node;

class Drawable : public Serializable {
   public:
    OBJECT(Drawable, Serializable);

    enum DrawableType {
        DT_Light,
        DT_Geometry,
        DT_Camera // TODO(pierre) Should probably not be there. Should have a Components class on
                  // top of drawable
    };

    Drawable(const std::shared_ptr<EngineContext>& iContext, DrawableType iType)
        : Serializable(iContext), m_Type(iType) {}
    virtual ~Drawable() {}

    DrawableType GetDrawableType() const { return m_Type; }

    void SetNode(const std::shared_ptr<Node>& iNode) { m_pNode = iNode; }
    std::shared_ptr<Node> GetNode();
    void SetIsDirty(bool iIsDirty) { m_IsDirty = iIsDirty; }

   protected:
    std::weak_ptr<Node> m_pNode;

    bool m_IsDirty;

   private:
    DrawableType m_Type;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_DRAWABLE_H_
