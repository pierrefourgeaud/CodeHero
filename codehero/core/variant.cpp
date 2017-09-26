// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/variant.h"
#include <logger.h>

namespace CodeHero {

Variant::Variant() {}
Variant::~Variant() {
    using std::string;
    switch (m_Type) {
    case Value::VVT_String:
        m_Value.m_String.~string();
        break;
    case Value::VVT_Vector3:
        m_Value.m_Vector3.~Vector3();
        break;
    default:
        break;
    }
}

Variant::Variant(const Variant& iRhs) {
    m_Type = iRhs.m_Type;
    switch (iRhs.m_Type) {
    case Value::VVT_Int:
        m_Value.m_Int = iRhs.m_Value.m_Int;
        break;
    case Value::VVT_Char:
        m_Value.m_Char = iRhs.m_Value.m_Char;
        break;
    case Value::VVT_Float:
        m_Value.m_Float = iRhs.m_Value.m_Float;
        break;
    case Value::VVT_Double:
        m_Value.m_Double = iRhs.m_Value.m_Double;
        break;
    case Value::VVT_String:
        m_Value.m_String = iRhs.m_Value.m_String;
        break;
    case Value::VVT_Vector3:
        m_Value.m_Vector3 = iRhs.m_Value.m_Vector3;
        break;
    default:
        // Default to int
        LOGW << "Variant: Attempted to copy variant that wasn't initialized... Default to Int" << std::endl;
        m_Value.m_Int = 0;
        m_Type = Value::VVT_Int;
        break;
    }
}

Variant& Variant::operator=(Variant iRhs) {
    std::swap(*this, iRhs);
    return *this;
}

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

Variant::Variant(const std::string& iValue) {
    new (&m_Value.m_String) std::string();
    m_Value.m_String = iValue;
    m_Type = Value::Type::VVT_String;
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

std::string Variant::GetString() const {
    if (m_Type == Value::Type::VVT_String) {
        return m_Value.m_String;
    }

    // Default to ""
    return "";
}

Vector3 Variant::GetVector3() const {
    if (m_Type == Value::Type::VVT_Vector3) {
        return m_Value.m_Vector3;
    }

    // Default to 0 vector
    return Vector3();
}

template <> int Variant::Get<int>() const {
    return GetInt();
}

template <> char Variant::Get<char>() const {
    return GetChar();
}

template <> float Variant::Get<float>() const {
    return GetFloat();
}

template <> double Variant::Get<double>() const {
    return GetDouble();
}

template <> std::string Variant::Get<std::string>() const {
    return GetString();
}

template <> Vector3 Variant::Get<Vector3>() const {
    return GetVector3();
}

} // namespace CodeHero