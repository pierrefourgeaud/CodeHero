// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <bandit/bandit.h>
#include "core/math/vector4.h"

using namespace bandit;
using namespace snowhouse;
using namespace CodeHero;

go_bandit([]() {
    describe("Vector4", []() {
        describe("Constructor", []() {
            it("should initialize vector with 0s if no arguments", [] {
                Vector4 test;

                AssertThat(test.x(), Equals(0.0f));
                AssertThat(test.y(), Equals(0.0f));
                AssertThat(test.z(), Equals(0.0f));
                AssertThat(test.w(), Equals(0.0f));
            });

            it("should initialize vector with correct x, y, z and w if provided", [] {
                float x = 1.5f;
                float y = 2.5f;
                float z = 3.5f;
                float w = 4.5f;
                Vector4 test(x, y, z, w);

                AssertThat(test.x(), Equals(x));
                AssertThat(test.y(), Equals(y));
                AssertThat(test.z(), Equals(z));
                AssertThat(test.w(), Equals(w));
            });

            it("should initialize vector with correct x, y, z and w if provided as array", [] {
                float x = 1.5f;
                float y = 2.5f;
                float z = 3.5f;
                float w = 4.5f;
                const float vec[] = {x, y, z, w};
                Vector4 test(vec);

                AssertThat(test.x(), Equals(x));
                AssertThat(test.y(), Equals(y));
                AssertThat(test.z(), Equals(z));
                AssertThat(test.w(), Equals(w));
            });
        });

        describe("::operator==", [] {
            it("should return true if condition is valid", [] {
                Vector4 lhs(1.0f, 2.0f, 3.0f, 4.0f);
                Vector4 rhs(1.0f, 2.0f, 3.0f, 4.0f);

                AssertThat(lhs == rhs, Is().True());
            });

            it("should return false if condition is invalid", [] {
                Vector4 lhs(1.0f, 2.0f, 3.0f, 4.0f);
                Vector4 rhs(5.0f, 6.0f, 7.0f, 8.0f);

                AssertThat(lhs == rhs, Is().False());
            });
        });

        describe("::operator+", [] {
            it("should add properly two vectors", [] {
                Vector4 lhs(1.0f, 2.0f, 3.0f, 4.0f);
                Vector4 rhs(5.0f, 6.0f, 7.0f, 8.0f);
                Vector4 result(6.0f, 8.0f, 10.0f, 12.0f);

                AssertThat(lhs + rhs, Equals(result));
            });
        });

        describe("::operator*", [] {
            it("should multiply properly by a scalar value", [] {
                Vector4 lhs(1.0f, 2.0f, 3.0f, 4.0f);
                float rhs = 2.0f;
                Vector4 result(2.0f, 4.0f, 6.0f, 8.0f);

                AssertThat(lhs * rhs, Equals(result));
            });
        });

        describe("::operator+=", [] {
            it("should add properly two vectors and modify the origin", [] {
                Vector4 lhs(1.0f, 2.0f, 3.0f, 4.0f);
                Vector4 rhs(5.0f, 6.0f, 7.0f, 8.0f);
                Vector4 result(6.0f, 8.0f, 10.0f, 12.0f);

                lhs += rhs;
                AssertThat(lhs, Equals(result));
            });
        });

        describe("::operator*=", [] {
            it("should multiply assign properly with scalar", [] {
                Vector4 lhs(1.0f, 2.0f, 3.0f, 4.0f);
                float rhs = 2.0f;
                Vector4 result(2.0f, 4.0f, 6.0f, 8.0f);

                lhs *= rhs;
                AssertThat(lhs, Equals(result));
            });
        });

        describe("::operator[]", [] {
            it("should return the right property", [] {
                float x = 1.5f;
                float y = 2.5f;
                float z = 3.5f;
                float w = 4.5f;
                Vector4 test(x, y, z, w);

                AssertThat(test[0], Equals(x));
                AssertThat(test[1], Equals(y));
                AssertThat(test[2], Equals(z));
                AssertThat(test[3], Equals(w));
            });
        });
    });
});