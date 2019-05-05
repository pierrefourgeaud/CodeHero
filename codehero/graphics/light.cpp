// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/light.h"
#include <logger.h>
#include "core/assert.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/type_traits/objectdefinition.h"

namespace CodeHero {

Light::Light(const std::shared_ptr<EngineContext>& iContext, Type iType)
    : Drawable(iContext, Drawable::DrawableType::DT_Light), m_LightType(iType) {}

// This method is static
// This is put at the top because it is really important and informative
void Light::RegisterObject(const std::shared_ptr<EngineContext>& iContext) {
    CH_REGISTER_OBJECT(Light);

    CH_OBJECT_ATTRIBUTE(Light, "Type", std::string, Variant::Value::VVT_String,
                        &Light::GetTypeString, &Light::SetTypeString);
    CH_OBJECT_ATTRIBUTE(Light, "Direction", Vector3, Variant::Value::VVT_Vector3,
                        &Light::GetDirection, &Light::SetDirection);
    CH_OBJECT_ATTRIBUTE(Light, "Ambient Intensity", float, Variant::Value::VVT_Float,
                        &Light::GetAmbientIntensity, &Light::SetAmbientIntensity);
    CH_OBJECT_ATTRIBUTE(Light, "Diffuse Intensity", float, Variant::Value::VVT_Float,
                        &Light::GetDiffuseIntensity, &Light::SetDiffuseIntensity);
    CH_OBJECT_ATTRIBUTE(Light, "Specular Intensity", float, Variant::Value::VVT_Float,
                        &Light::GetSpecularIntensity, &Light::SetSpecularIntensity);
    CH_OBJECT_ATTRIBUTE(Light, "Linear", float, Variant::Value::VVT_Float, &Light::GetLinear,
                        &Light::SetLinear);
    CH_OBJECT_ATTRIBUTE(Light, "Constant", float, Variant::Value::VVT_Float, &Light::GetConstant,
                        &Light::SetConstant);
    CH_OBJECT_ATTRIBUTE(Light, "Quadratic", float, Variant::Value::VVT_Float, &Light::GetQuadratic,
                        &Light::SetQuadratic);
}

std::shared_ptr<Light> Light::Create(const std::shared_ptr<EngineContext>& iContext) {
    return std::make_shared<Light>(iContext, T_Point);
}

void Light::SetTypeString(const std::string& iType) {
    if (iType == "T_Directional") {
        m_LightType = T_Directional;
    } else if (iType == "T_Point") {
        m_LightType = T_Point;
    } else if (iType == "T_Spot") {
        m_LightType = T_Spot;
    } else {
        LOGE << "Light: Wrong light type [" << iType << "]" << std::endl;
        CH_ASSERT(false);
    }
}

std::string Light::GetTypeString() const {
    switch (m_LightType) {
        case T_Directional: return "T_Directional";
        case T_Point: return "T_Point";
        case T_Spot: return "T_Spot";
        default: CH_ASSERT(false); return "";
    }
}

Light& Light::SetDirection(const Vector3& iDirection) {
    // TODO(pierre) assert ?
    m_Direction = iDirection;
    return *this;
}

const Vector3& Light::GetDirection() const {
    // TODO(pierre) assert ?
    return m_Direction;
}

Light& Light::SetAmbientIntensity(float iIntensity) {
    // TODO(pierre) assert ?
    m_AmbientIntensity = iIntensity;
    return *this;
}

float Light::GetAmbientIntensity() const {
    // TODO(pierre) assert ?
    return m_AmbientIntensity;
}

Light& Light::SetDiffuseIntensity(float iIntensity) {
    // TODO(pierre) assert ?
    m_DiffuseIntensity = iIntensity;
    return *this;
}

float Light::GetDiffuseIntensity() const {
    // TODO(pierre) assert ?
    return m_DiffuseIntensity;
}

Light& Light::SetSpecularIntensity(float iIntensity) {
    // TODO(pierre) assert ?
    m_SpecularIntensity = iIntensity;
    return *this;
}

float Light::GetSpecularIntensity() const {
    // TODO(pierre) assert ?
    return m_SpecularIntensity;
}

Light& Light::SetLinear(float iLinear) {
    // TODO(pierre) assert ?
    m_Linear = iLinear;
    return *this;
}

float Light::GetLinear() const {
    // TODO(pierre) assert ?
    return m_Linear;
}

Light& Light::SetConstant(float iConstant) {
    // TODO(pierre) assert ?
    m_Constant = iConstant;
    return *this;
}

float Light::GetConstant() const {
    // TODO(pierre) assert ?
    return m_Constant;
}

Light& Light::SetQuadratic(float iQuadratic) {
    // TODO(pierre) assert ?
    m_Quadratic = iQuadratic;
    return *this;
}

float Light::GetQuadratic() const {
    // TODO(pierre) assert ?
    return m_Quadratic;
}

} // namespace CodeHero