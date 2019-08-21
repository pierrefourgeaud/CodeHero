// Copyright (c) 2019 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/boundingbox.h"

#include <limits>

#include <logger.h>

const float FLOAT_MAX = std::numeric_limits<float>::max();
const float FLOAT_MIN = std::numeric_limits<float>::lowest();

namespace CodeHero {

// Min and Max are initialized with opposite boundaries (min gets the max values and max gets the
// min values) so when we try to create the bounding box by "merging" points, the first point will
// start the bounding box
BoundingBox::BoundingBox()
    : m_Min(FLOAT_MAX, FLOAT_MAX, FLOAT_MAX), m_Max(FLOAT_MIN, FLOAT_MIN, FLOAT_MIN) {}

BoundingBox::~BoundingBox() = default;

void BoundingBox::Merge(const Vector3& iPoint) {
    // Min
    if (iPoint.x() < m_Min.x()) {
        m_Min.SetX(iPoint.x());
    }
    if (iPoint.y() < m_Min.y()) {
        m_Min.SetY(iPoint.y());
    }
    if (iPoint.z() < m_Min.z()) {
        m_Min.SetZ(iPoint.z());
    }

    // Max
    if (iPoint.x() > m_Max.x()) {
        m_Max.SetX(iPoint.x());
    }
    if (iPoint.y() > m_Max.y()) {
        m_Max.SetY(iPoint.y());
    }
    if (iPoint.z() > m_Max.z()) {
        m_Max.SetZ(iPoint.z());
    }
}

Vector3 BoundingBox::Center() const {
    return (m_Min + m_Max) * 0.5f;
}

} // namespace CodeHero