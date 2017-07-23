// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/light.h"

namespace CodeHero {

Light::Light(Type iType)
    : Component(Component::DrawableType::DT_Light)
    , m_LightType(iType) {}

Light& Light::SetDirection(const Vector3& iDirection) {
    // TODO(pierre) assert ?
    m_Direction = iDirection;
    return *this;
}

const Vector3& Light::GetDirection() const {
    // TODO(pierre) assert ?
    return m_Direction;
}

Light& Light::SetPosition(const Vector3& iPosition) {
    // TODO(pierre) assert ?
    m_Position = iPosition;
    return *this;
}

const Vector3& Light::GetPosition() const {
    // TODO(pierre) assert ?
    return m_Position;
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