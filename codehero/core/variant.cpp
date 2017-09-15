// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/variant.h"

namespace CodeHero {

Variant::Variant() {}

Variant::~Variant() {}

Variant::Variant(int iValue) {
    m_Value.m_Int = iValue;
    m_Type = Value::Type::VVT_Int;
}

Variant::Variant(char iValue) {
    m_Value.m_Char = iValue;
    m_Type = Value::Type::VVT_Char;
}

Variant::Variant(float iValue) {
    m_Value.m_Float = iValue;
    m_Type = Value::Type::VVT_Float;
}

Variant::Variant(double iValue) {
    m_Value.m_Double = iValue;
    m_Type = Value::Type::VVT_Double;
}

Variant::Variant(const Vector3& iValue) {
    m_Value.m_Vector3 = iValue;
    m_Type = Value::Type::VVT_Vector3;
}

int Variant::GetInt() const {
    if (m_Type == Value::Type::VVT_Int) {
        return m_Value.m_Int;
    }

    // Default to 0
    return 0;
}

char Variant::GetChar() const {
    if (m_Type == Value::Type::VVT_Char) {
        return m_Value.m_Char;
    }

    // Default to 0
    return '\0';
}

float Variant::GetFloat() const {
    if (m_Type == Value::Type::VVT_Float) {
        return m_Value.m_Float;
    } else if (m_Type == Value::Type::VVT_Double) {
        return static_cast<float>(m_Value.m_Double);
    }

    // Default to 0.0f
    return 0.0f;
}

double Variant::GetDouble() const {
    if (m_Type == Value::Type::VVT_Float) {
        return m_Value.m_Float;
    } else if (m_Type == Value::Type::VVT_Double) {
        return m_Value.m_Double;
    }

    // Default to 0.0
    return 0.0;
}

Vector3 Variant::GetVector3() const {
    if (m_Type == Value::Type::VVT_Vector3) {
        return m_Value.m_Vector3;
    }

    // Default to 0 vector
    return Vector3();
}

} // namespace CodeHero