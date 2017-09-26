// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_VARIANT_H_
#define CODEHERO_CORE_VARIANT_H_

#include <string>
#include "core/math/vector3.h"

namespace CodeHero {

// Forward declaration
class EngineContext;

class Variant {
public:
    union Value {
        enum Type {
            VVT_Int = 0,
            VVT_Char,
            VVT_Float,
            VVT_Double,
            VVT_String,
            VVT_Vector3
        };

        int m_Int;
        char m_Char;
        float m_Float;
        double m_Double;
        std::string m_String;
        Vector3 m_Vector3;

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

    explicit Variant(int iValue);
    explicit Variant(char iValue);
    explicit Variant(float iValue);
    explicit Variant(double iValue);
    explicit Variant(const std::string& iValue);
    explicit Variant(const Vector3& iValue);

    int GetInt() const;
    char GetChar() const;
    float GetFloat() const;
    double GetDouble() const;
    std::string GetString() const;
    Vector3 GetVector3() const;

    // Base template method
    template <class T> T Get() const;

    Value& GetValue() { return m_Value; }
    const Value& GetValue() const { return m_Value; }
    Value::Type GetType() const { return m_Type; }

private:
    Value m_Value;
    Value::Type m_Type;
};

// Specialization of template <class T> T Get() const;
template <> int Variant::Get<int>() const;
template <> char Variant::Get<char>() const;
template <> float Variant::Get<float>() const;
template <> double Variant::Get<double>() const;
template <> std::string Variant::Get<std::string>() const;
template <> Vector3 Variant::Get<Vector3>() const;

} // namespace CodeHero

#endif // CODEHERO_CORE_VARIANT_H_
