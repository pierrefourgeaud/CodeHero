// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <bandit/bandit.h>
#include "core/variant.h"

using namespace bandit;
using namespace snowhouse;
using namespace CodeHero;

go_bandit([]() {
    describe("Variant", []() {
        describe("Constructor", []() {
            it("should initialize int with proper type and right value", [] {
                int value = 1;
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_Int));
                AssertThat(test.GetValue().m_Int, Equals(value));
            });

            it("should initialize char with proper type and right value", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_Char));
                AssertThat(test.GetValue().m_Char, Equals(value));
            });

            it("should initialize float with proper type and right value", [] {
                float value = 1.0f;
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_Float));
                AssertThat(test.GetValue().m_Float, Equals(value));
            });

            it("should initialize double with proper type and right value", [] {
                double value = 1.0;
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_Double));
                AssertThat(test.GetValue().m_Double, Equals(value));
            });
        });

        describe("::GetInt", [] {
            it("should return the proper value if correct type", [] {
                int value = 1;
                Variant test(value);

                AssertThat(test.GetInt(), Equals(value));
            });

            it("should return 0 if type is not int", [] {
                float value = 1.0f;
                Variant test(value);

                AssertThat(test.GetInt(), Equals(0));
            });
        });

        describe("::GetChar", [] {
            it("should return the proper value if correct type", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetChar(), Equals(value));
            });

            it("should return '\0' if type is not char", [] {
                float value = 1.0f;
                Variant test(value);

                AssertThat(test.GetChar(), Equals('\0'));
            });
        });

        describe("::GetFloat", [] {
            it("should return the proper value if correct type", [] {
                float value = 1.0f;
                Variant test(value);

                AssertThat(test.GetFloat(), Equals(value));
            });

            it("should return the proper value if type is double", [] {
                double value = 1.0;
                Variant test(value);

                AssertThat(test.GetFloat(), Equals(value));
            });

            it("should return 0.0f if type is not float or double", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetFloat(), Equals(0.0f));
            });
        });

        describe("::GetDouble", [] {
            it("should return the proper value if correct type", [] {
                double value = 1.0;
                Variant test(value);

                AssertThat(test.GetDouble(), Equals(value));
            });

            it("should return the proper value if type is float", [] {
                float value = 1.0f;
                Variant test(value);

                AssertThat(test.GetDouble(), Equals(value));
            });

            it("should return 0.0f if type is not float or double", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetDouble(), Equals(0.0));
            });
        });
    });
});