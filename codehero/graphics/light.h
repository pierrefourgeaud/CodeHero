// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_LIGHT_H_
#define CODEHERO_GRAPHICS_LIGHT_H_ 

#include "graphics/component.h"

namespace CodeHero {

// Light class based of the Phong lighting model.
// Phong being defined as the combination of:
// - Ambiance lighting
// - Diffuse lighting
// - Specular lighting
class Light : public Component {
public:
    enum Type {
        T_Point,
        T_Directional,
        T_Spot
    };

private:
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_LIGHT_H_
