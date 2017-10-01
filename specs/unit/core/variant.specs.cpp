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

            it("should initialize string with proper type and right value", [] {
                std::string value("test");
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_String));
                AssertThat(test.GetValue().m_String, Equals(value));
            });

            it("should initialize vector3 with proper type and right value", [] {
                Vector3 value(1.0f, 2.0f, 3.0f);
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_Vector3));
                AssertThat(test.GetValue().m_Vector3, Equals(value));
            });

            it("should initialize hashmap with proper type and right value", [] {
                VariantHashMap value({{"test", "value"}});
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_HashMap));
                AssertThat(test.GetValue().m_HashMap, Equals(value));
            });
        });

        describe("::GetInt", [] {
            it("should return the proper value if correct type", [] {
                int value = 1;
                Variant test(value);

                AssertThat(test.GetInt(), Equals(value));
                AssertThat(test.Get<int>(), Equals(value));
            });

            it("should return 0 if type is not int", [] {
                float value = 1.0f;
                Variant test(value);

                AssertThat(test.GetInt(), Equals(0));
                AssertThat(test.Get<int>(), Equals(0));
            });
        });

        describe("::GetChar", [] {
            it("should return the proper value if correct type", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetChar(), Equals(value));
                AssertThat(test.Get<char>(), Equals(value));
            });

            it("should return '\0' if type is not char", [] {
                float value = 1.0f;
                Variant test(value);

                AssertThat(test.GetChar(), Equals('\0'));
                AssertThat(test.Get<char>(), Equals('\0'));
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
                AssertThat(test.Get<float>(), Equals(value));
            });

            it("should return 0.0f if type is not float or double", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetFloat(), Equals(0.0f));
                AssertThat(test.Get<float>(), Equals(0.0f));
            });
        });

        describe("::GetDouble", [] {
            it("should return the proper value if correct type", [] {
                double value = 1.0;
                Variant test(value);

                AssertThat(test.GetDouble(), Equals(value));
                AssertThat(test.Get<double>(), Equals(value));
            });

            it("should return the proper value if type is float", [] {
                float value = 1.0f;
                Variant test(value);

                AssertThat(test.GetDouble(), Equals(value));
                AssertThat(test.Get<double>(), Equals(value));
            });

            it("should return 0.0f if type is not float or double", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetDouble(), Equals(0.0));
                AssertThat(test.Get<double>(), Equals(0.0));
            });
        });

        describe("::GetString", [] {
            it("should return the proper value if correct type", [] {
                std::string value("test");
                Variant test(value);

                AssertThat(test.GetString(), Equals(value));
                AssertThat(test.Get<std::string>(), Equals(value));
            });

            it("should return empty string if type is not string", [] {
                int value = 0;
                Variant test(value);

                AssertThat(test.GetString(), Equals(""));
                AssertThat(test.Get<std::string>(), Equals(""));
            });
        });

        describe("::GetVector3", [] {
            it("should return the proper value if correct type", [] {
                Vector3 value(1.0f, 2.0f, 3.0f);
                Variant test(value);

                AssertThat(test.GetVector3(), Equals(value));
                AssertThat(test.Get<Vector3>(), Equals(value));
            });

            it("should return 0 vector3 if type is not vector3", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetVector3(), Equals(Vector3(0.0f, 0.0f, 0.0f)));
                AssertThat(test.Get<Vector3>(), Equals(Vector3(0.0f, 0.0f, 0.0f)));
            });
        });

        describe("::GetHashMap", [] {
            it("should return the proper value if correct type", [] {
                VariantHashMap value({{"test", "value"}});
                Variant test(value);

                AssertThat(test.GetHashMap(), Equals(value));
                AssertThat(test.Get<VariantHashMap>(), Equals(value));
            });

            it("should return empth hashmap if type is not hashmap", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetHashMap(), Equals(VariantHashMap()));
                AssertThat(test.Get<VariantHashMap>(), Equals(VariantHashMap()));
            });
        });
    });
});