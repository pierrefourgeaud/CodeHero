// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_COMPONENT_H_
#define CODEHERO_GRAPHICS_COMPONENT_H_ 

namespace CodeHero {

class Component {
public:
    enum DrawableType {
        DT_Light,
        DT_Geometry
    };

    explicit Component(DrawableType iType)
        : m_Type(iType) {}
    virtual ~Component() {}

    DrawableType GetDrawableType() const { return m_Type; }

private:
    DrawableType m_Type;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_COMPONENT_H_
