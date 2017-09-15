// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_VARIANT_H_
#define CODEHERO_CORE_VARIANT_H_

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
            VVT_Vector3
        };

        int m_Int;
        char m_Char;
        float m_Float;
        double m_Double;
        Vector3 m_Vector3;

        Value() {}
        ~Value() {}
        // Cannot be copied
        Value(const Value& value) = delete;
    };

    Variant();
    ~Variant();

    explicit Variant(int iValue);
    explicit Variant(char iValue);
    explicit Variant(float iValue);
    explicit Variant(double iValue);
    explicit Variant(const Vector3& iValue);

    int GetInt() const;
    char GetChar() const;
    float GetFloat() const;
    double GetDouble() const;
    Vector3 GetVector3() const;

    Value& GetValue() { return m_Value; }
    const Value& GetValue() const { return m_Value; }
    Value::Type GetType() const { return m_Type; }

private:
    Value m_Value;
    Value::Type m_Type;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_VARIANT_H_
