// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/variant.h"
#include <logger.h>

namespace CodeHero {

Variant::Variant() {
    m_Type = Value::Type::VVT_None;
}

Variant::~Variant() {
    using std::string;
    using std::vector;
    using std::unordered_map;
    using std::shared_ptr;
    switch (m_Type) {
    case Value::VVT_String:
        m_Value.m_String.~string();
        break;
    case Value::VVT_Vector2:
        m_Value.m_Vector2.~Vector2();
        break;
    case Value::VVT_Vector3:
        m_Value.m_Vector3.~Vector3();
        break;
    case Value::VVT_Quaternion:
        m_Value.m_Quaternion.~Quaternion();
        break;
    case Value::VVT_Array:
        m_Value.m_Array.~vector();
        break;
    case Value::VVT_HashMap:
        m_Value.m_HashMap.~unordered_map();
        break;
    case Value::VVT_SerializablePtr:
        m_Value.m_SerializablePtr.~shared_ptr();
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
    case Value::VVT_Vector2:
        m_Value.m_Vector2 = iRhs.m_Value.m_Vector2;
        break;
    case Value::VVT_Vector3:
        m_Value.m_Vector3 = iRhs.m_Value.m_Vector3;
        break;
    case Value::VVT_Quaternion:
        m_Value.m_Quaternion = iRhs.m_Value.m_Quaternion;
        break;
    case Value::VVT_Array:
        m_Value.m_Array = iRhs.m_Value.m_Array;
        break;
    case Value::VVT_HashMap:
        m_Value.m_HashMap = iRhs.m_Value.m_HashMap;
        break;
    case Value::VVT_SerializablePtr:
        m_Value.m_SerializablePtr = iRhs.m_Value.m_SerializablePtr;
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

Variant::Variant(const Vector2& iValue) {
    m_Value.m_Vector2 = iValue;
    m_Type = Value::Type::VVT_Vector2;
}

Variant::Variant(const Vector3& iValue) {
    m_Value.m_Vector3 = iValue;
    m_Type = Value::Type::VVT_Vector3;
}

Variant::Variant(const Quaternion& iValue) {
    m_Value.m_Quaternion = iValue;
    m_Type = Value::Type::VVT_Quaternion;
}

Variant::Variant(const VariantArray& iValue) {
    new (&m_Value.m_Array) VariantArray();
    m_Value.m_Array = iValue;
    m_Type = Value::Type::VVT_Array;
}

Variant::Variant(const VariantHashMap& iValue) {
    new (&m_Value.m_HashMap) VariantHashMap();
    m_Value.m_HashMap = iValue;
    m_Type = Value::Type::VVT_HashMap;
}

Variant::Variant(const std::shared_ptr<Serializable>& iValue) {
    new (&m_Value.m_SerializablePtr) std::shared_ptr<Serializable>();
    m_Value.m_SerializablePtr = iValue;
    m_Type = Value::Type::VVT_SerializablePtr;
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

Vector2 Variant::GetVector2() const {
    if (m_Type == Value::Type::VVT_Vector2) {
        return m_Value.m_Vector2;
    }

    // Default to 0 vector
    return Vector2();
}

Vector3 Variant::GetVector3() const {
    if (m_Type == Value::Type::VVT_Vector3) {
        return m_Value.m_Vector3;
    }

    // Default to 0 vector
    return Vector3();
}

Quaternion Variant::GetQuaternion() const {
    if (m_Type == Value::Type::VVT_Quaternion) {
        return m_Value.m_Quaternion;
    }

    // Default to 0 quaternion
    return Quaternion();
}

VariantArray Variant::GetArray() const {
    if (m_Type == Value::Type::VVT_Array) {
        return m_Value.m_Array;
    }

    // Default to empty hashmap
    return VariantArray();
}

VariantHashMap Variant::GetHashMap() const {
    if (m_Type == Value::Type::VVT_HashMap) {
        return m_Value.m_HashMap;
    }

    // Default to empty hashmap
    return VariantHashMap();
}

std::shared_ptr<Serializable> Variant::GetSerializablePtr() const {
    if (m_Type == Value::Type::VVT_SerializablePtr) {
        return m_Value.m_SerializablePtr;
    }

    // Default to nullptr
    return nullptr;
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

template <> Vector2 Variant::Get<Vector2>() const {
    return GetVector2();
}

template <> Vector3 Variant::Get<Vector3>() const {
    return GetVector3();
}

template <> Quaternion Variant::Get<Quaternion>() const {
    return GetQuaternion();
}

template <> VariantArray Variant::Get<VariantArray>() const {
    return GetArray();
}

template <> VariantHashMap Variant::Get<VariantHashMap>() const {
    return GetHashMap();
}

template <> std::shared_ptr<Serializable> Variant::Get<std::shared_ptr<Serializable>>() const {
    return GetSerializablePtr();
}

} // namespace CodeHero