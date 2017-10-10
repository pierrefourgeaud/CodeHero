// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <bandit/bandit.h>
#include "core/serializable.h"
#include "core/variant.h"

using namespace bandit;
using namespace snowhouse;
using namespace CodeHero;

go_bandit([]() {
    describe("Variant", []() {
        describe("Constructor", []() {
            it("should initialize to none if default ctor is used", [] {
                Variant test;

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_None));
                AssertThat(test.IsNone(), Is().True());
            });

            it("should initialize int with proper type and right value", [] {
                int value = 1;
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_Int));
                AssertThat(test.GetValue().m_Int, Equals(value));
                AssertThat(test.IsNone(), Is().False());
            });

            it("should initialize char with proper type and right value", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_Char));
                AssertThat(test.GetValue().m_Char, Equals(value));
                AssertThat(test.IsNone(), Is().False());
            });

            it("should initialize float with proper type and right value", [] {
                float value = 1.0f;
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_Float));
                AssertThat(test.GetValue().m_Float, Equals(value));
                AssertThat(test.IsNone(), Is().False());
            });

            it("should initialize double with proper type and right value", [] {
                double value = 1.0;
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_Double));
                AssertThat(test.GetValue().m_Double, Equals(value));
                AssertThat(test.IsNone(), Is().False());
            });

            it("should initialize string with proper type and right value", [] {
                std::string value("test");
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_String));
                AssertThat(test.GetValue().m_String, Equals(value));
                AssertThat(test.IsNone(), Is().False());
            });

            it("should initialize vector3 with proper type and right value", [] {
                Vector3 value(1.0f, 2.0f, 3.0f);
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_Vector3));
                AssertThat(test.GetValue().m_Vector3, Equals(value));
                AssertThat(test.IsNone(), Is().False());
            });

            it("should initialize quaternion with proper type and right value", [] {
                Quaternion value(1.0f, 2.0f, 3.0f);
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_Quaternion));
                AssertThat(test.GetValue().m_Quaternion, Equals(value));
                AssertThat(test.IsNone(), Is().False());
            });

            it("should initialize array with proper type and right value", [] {
                VariantArray value({"test", "value"});
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_Array));
                AssertThat(test.GetValue().m_Array, Equals(value));
                AssertThat(test.IsNone(), Is().False());
            });

            it("should initialize hashmap with proper type and right value", [] {
                VariantHashMap value({{"test", "value"}});
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_HashMap));
                AssertThat(test.GetValue().m_HashMap, Equals(value));
                AssertThat(test.IsNone(), Is().False());
            });

            it("should initialize shared_ptr<Serializable> with proper type and right value", [] {
                auto value = std::make_shared<Serializable>(nullptr);
                Variant test(value);

                AssertThat(test.GetType(), Equals(Variant::Value::Type::VVT_SerializablePtr));
                AssertThat(test.GetValue().m_SerializablePtr, Equals(value));
                AssertThat(test.IsNone(), Is().False());
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

        describe("::GetQuaternion", [] {
            it("should return the proper value if correct type", [] {
                Quaternion value(1.0f, 2.0f, 3.0f);
                Variant test(value);

                AssertThat(test.GetQuaternion(), Equals(value));
                AssertThat(test.Get<Quaternion>(), Equals(value));
            });

            it("should return 0 vector3 if type is not vector3", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetQuaternion(), Equals(Quaternion(0.0f, 0.0f, 0.0f)));
                AssertThat(test.Get<Quaternion>(), Equals(Quaternion(0.0f, 0.0f, 0.0f)));
            });
        });

        describe("::GetArray", [] {
            it("should return the proper value if correct type", [] {
                VariantArray value({"test", "value"});
                Variant test(value);

                AssertThat(test.GetArray(), Equals(value));
                AssertThat(test.Get<VariantArray>(), Equals(value));
            });

            it("should return empty array if type is not array", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetArray(), Equals(VariantArray()));
                AssertThat(test.Get<VariantArray>(), Equals(VariantArray()));
            });
        });

        describe("::GetHashMap", [] {
            it("should return the proper value if correct type", [] {
                VariantHashMap value({{"test", "value"}});
                Variant test(value);

                AssertThat(test.GetHashMap(), Equals(value));
                AssertThat(test.Get<VariantHashMap>(), Equals(value));
            });

            it("should return empty hashmap if type is not hashmap", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetHashMap(), Equals(VariantHashMap()));
                AssertThat(test.Get<VariantHashMap>(), Equals(VariantHashMap()));
            });
        });

        describe("::GetSerializablePtr", [] {
            it("should return the proper value if correct type", [] {
                auto value = std::make_shared<Serializable>(nullptr);
                Variant test(value);

                AssertThat(test.GetSerializablePtr(), Equals(value));
                AssertThat(test.Get<std::shared_ptr<Serializable>>(), Equals(value));
            });

            it("should return nullptr if type is not serializable pointer", [] {
                char value = 'a';
                Variant test(value);

                AssertThat(test.GetSerializablePtr(), Equals(nullptr));
                AssertThat(test.Get<std::shared_ptr<Serializable>>(), Equals(nullptr));
            });
        });
    });
});