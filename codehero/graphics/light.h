// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_GRAPHICS_LIGHT_H_
#define CODEHERO_GRAPHICS_LIGHT_H_ 

#include "graphics/drawable.h"
#include "core/math/vector3.h"

namespace CodeHero {

// Light class based of the Phong lighting model.
// Phong being defined as the combination of:
// - Ambiance lighting
// - Diffuse lighting
// - Specular lighting
class Light : public Drawable {
public:
    enum Type {
        T_Point,
        T_Directional,
        T_Spot
    };

    OBJECT(Light)

    Light(const std::shared_ptr<EngineContext>& iContext, Type iType);
    virtual ~Light() {}

    // Getter/Setter
    Light& SetDirection(const Vector3& iDirection);
    const Vector3& GetDirection() const;

    Type GetType() const { return m_LightType; }

    Light& SetAmbientIntensity(float iIntensity);
    float GetAmbientIntensity() const;
    Light& SetDiffuseIntensity(float iIntensity);
    float GetDiffuseIntensity() const;
    Light& SetSpecularIntensity(float iIntensity);
    float GetSpecularIntensity() const;

    Light& SetLinear(float iLinear);
    float GetLinear() const;
    Light& SetConstant(float iConstant);
    float GetConstant() const;
    Light& SetQuadratic(float iQuadratic);
    float GetQuadratic() const;
    // End Getter/Setter

private:
    Type m_LightType;

    // Directional lights only
    Vector3 m_Direction;

    float m_AmbientIntensity;
    float m_DiffuseIntensity;
    float m_SpecularIntensity;

    // Attenuation
    float m_Linear;
    float m_Constant;
    float m_Quadratic;
};

} // namespace CodeHero

#endif // CODEHERO_GRAPHICS_LIGHT_H_
