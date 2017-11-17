// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_VARIANT_H_
#define CODEHERO_CORE_VARIANT_H_

#include <memory>
#include <string>
#include <map>
#include <vector>
#include "core/math/vector2.h"
#include "core/math/vector3.h"
#include "core/math/quaternion.h"

namespace CodeHero {

// Forward declaration
class EngineContext;
class Serializable;

// TODO(pierre) Should the value be a Variant ?
// TODO(pierre) Should we reconcider the name for this ?
using VariantHashMap = std::map<std::string, std::string>;
// TODO(pierre) Should the elements be Variant ?
using VariantArray = std::vector<std::string>;

class Variant {
public:
    union Value {
        enum Type {
            VVT_None = 0,
            VVT_Bool,
            VVT_Int,
            VVT_Char,
            VVT_Float,
            VVT_Double,
            VVT_String,
            VVT_Vector2,
            VVT_Vector3,
            VVT_Quaternion,
            VVT_Array,
            VVT_HashMap,
            VVT_SerializablePtr
        };

        bool m_Bool;
        int m_Int;
        char m_Char;
        float m_Float;
        double m_Double;
        std::string m_String;
        Vector2 m_Vector2;
        Vector3 m_Vector3;
        Quaternion m_Quaternion;
        VariantArray m_Array;
        VariantHashMap m_HashMap;
        std::shared_ptr<Serializable> m_SerializablePtr;

        Value() {}
        ~Value() {}
        // Cannot be copied
        Value(const Value& value) = delete;
    };

    Variant();
    ~Variant();

    // Copy
    Variant(const Variant& iRhs);
    // Passing by value is intentional here
    Variant& operator=(Variant iRhs);

    explicit Variant(bool iValue);
    explicit Variant(int iValue);
    explicit Variant(char iValue);
    explicit Variant(float iValue);
    explicit Variant(double iValue);
    explicit Variant(const std::string& iValue);
    explicit Variant(const Vector2& iValue);
    explicit Variant(const Vector3& iValue);
    explicit Variant(const Quaternion& iValue);
    explicit Variant(const VariantArray& iValue);
    explicit Variant(const VariantHashMap& iHashMap);
    explicit Variant(const std::shared_ptr<Serializable>& iValue);

    bool GetBool() const;
    int GetInt() const;
    char GetChar() const;
    float GetFloat() const;
    double GetDouble() const;
    std::string GetString() const;
    Vector2 GetVector2() const;
    Vector3 GetVector3() const;
    Quaternion GetQuaternion() const;
    VariantArray GetArray() const;
    VariantHashMap GetHashMap() const;
    std::shared_ptr<Serializable> GetSerializablePtr() const;

    // Base template method
    template <class T> T Get() const;

    Value& GetValue() { return m_Value; }
    const Value& GetValue() const { return m_Value; }
    Value::Type GetType() const { return m_Type; }

    bool IsNone() const {
        return m_Type == Value::Type::VVT_None;
    }

    bool IsMapType() const {
        return m_Type == Value::Type::VVT_HashMap;
    }

private:
    Value m_Value;
    Value::Type m_Type;
};

// Specialization of template <class T> T Get() const;
template <> bool Variant::Get<bool>() const;
template <> int Variant::Get<int>() const;
template <> char Variant::Get<char>() const;
template <> float Variant::Get<float>() const;
template <> double Variant::Get<double>() const;
template <> std::string Variant::Get<std::string>() const;
template <> Vector2 Variant::Get<Vector2>() const;
template <> Vector3 Variant::Get<Vector3>() const;
template <> Quaternion Variant::Get<Quaternion>() const;
template <> VariantArray Variant::Get<VariantArray>() const;
template <> VariantHashMap Variant::Get<VariantHashMap>() const;
template <> std::shared_ptr<Serializable> Variant::Get<std::shared_ptr<Serializable>>() const;

} // namespace CodeHero

#endif // CODEHERO_CORE_VARIANT_H_
