// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/camera.h"

namespace CodeHero {

Camera::Camera() {}

Camera::Camera(const Vector3& iPosition, const Vector3& iTarget)
    : m_Position(iPosition)
    , m_Target(iTarget) {}

Camera::~Camera() {}

const Matrix4& Camera::GetView() {
    if (m_ViewDirty) {
        _ComputeViewMatrix();
        m_ViewDirty = false;
    }

    return m_View;
}

void Camera::SetPosition(const Vector3& iPosition) {
    m_Position = iPosition;
    m_ViewDirty = true;
}

void Camera::SetTarget(const Vector3& iTarget) {
    m_Target = iTarget;
    m_ViewDirty = true;
}

void Camera::_ComputeViewMatrix() {
    Vector3 direction = (m_Target - m_Position).Normalize();
    Vector3 cameraRight = direction.Cross({0.0f, 1.0f, 0.0f}).Normalize();
    Vector3 cameraUp = cameraRight.Cross(direction);

    m_View = Matrix4(
        cameraRight.x()             , cameraUp.x()             , -direction.x()           , 0.0f,
        cameraRight.y()             , cameraUp.y()             , -direction.y()           , 0.0f,
        cameraRight.z()             , cameraUp.z()             , -direction.z()           , 0.0f,
        -cameraRight.Dot(m_Position), -cameraUp.Dot(m_Position), direction.Dot(m_Position), 1.0f);
}

} // namespace CodeHero

