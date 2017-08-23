// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <bandit/bandit.h>
#include "core/math/vector3.h"

using namespace bandit;
using namespace snowhouse;
using namespace CodeHero;

go_bandit([]() {
    describe("Vector3", []() {
        describe("Constructor", []() {
            it("should initialize vector with 0s if no arguments", [] {
                Vector3 test;

                AssertThat(test.x(), Equals(0.0f));
                AssertThat(test.y(), Equals(0.0f));
                AssertThat(test.z(), Equals(0.0f));
            });

            it("should initialize vector with correct x and y if provided", [] {
                float x = 1.5f;
                float y = 2.5f;
                float z = 3.5f;
                Vector3 test(x, y, z);

                AssertThat(test.x(), Equals(x));
                AssertThat(test.y(), Equals(y));
                AssertThat(test.z(), Equals(z));
            });
        });

        describe("::Length", [] {
            it("should compute the proper length", [] {
                float x = 2.0f;
                float y = 2.0f;
                float z = 2.0f;
                Vector3 test(x, y, z);

                float res = 3.4641016151377544f;
                AssertThat(test.Length(), Equals(res));
            });
        });

        describe("::Normalize / ::Normalized", [] {
            it("should compute the normalized vector", [] {
                Vector3 test(1.0f, 1.0f, 1.0f);

                float res = 0.57735026919f;
                test.Normalize();
                AssertThat(test.x(), Equals(res));
                AssertThat(test.y(), Equals(res));
                AssertThat(test.z(), Equals(res));
            });

            it("should compute a new normalize network and not touch the initial one", [] {
                float base = 1.0f;
                Vector3 test(base, base, base);

                float res = 0.57735026919f;
                Vector3 result = test.Normalized();
                AssertThat(test.x(), Equals(base));
                AssertThat(test.y(), Equals(base));
                AssertThat(test.z(), Equals(base));
                AssertThat(result.x(), Equals(res));
                AssertThat(result.y(), Equals(res));
                AssertThat(result.z(), Equals(res));
            });
        });

        describe("::Cross", [] {
            it("should return the right vector", [] {
                Vector3 lhs(1.0f, 2.0f, 3.0f);
                Vector3 rhs(4.0f, 5.0f, 6.0f);
                Vector3 result(-3.0f, 6.0f, -3.0f);

                Vector3 test = lhs.Cross(rhs);
                AssertThat(test.x(), Equals(result.x()));
                AssertThat(test.y(), Equals(result.y()));
                AssertThat(test.z(), Equals(result.z()));
            });
        });

        describe("::Dot", [] {
            it("should return the right value", [] {
                Vector3 lhs(1.0f, 2.0f, 3.0f);
                Vector3 rhs(4.0f, 5.0f, 6.0f);
                float result = 32.0f;

                AssertThat(lhs.Dot(rhs), Equals(result));
            });
        });

        describe("::operator==", [] {
            it("should return true if condition is valid", [] {
                Vector3 lhs(1.0f, 2.0f, 3.0f);
                Vector3 rhs(1.0f, 2.0f, 3.0f);

                AssertThat(lhs == rhs, Is().True());
            });

            it("should return false if condition is invalid", [] {
                Vector3 lhs(1.0f, 2.0f, 3.0f);
                Vector3 rhs(4.0f, 5.0f, 6.0f);

                AssertThat(lhs == rhs, Is().False());
            });
        });

        describe("::operator+", [] {
            it("should add properly two vectors", [] {
                Vector3 lhs(1.0f, 2.0f, 3.0f);
                Vector3 rhs(4.0f, 5.0f, 6.0f);
                Vector3 result(5.0f, 7.0f, 9.0f);

                AssertThat(lhs + rhs, Equals(result));
            });
        });

        describe("::operator-", [] {
            it("should substract properly two vectors", [] {
                Vector3 lhs(1.0f, 2.0f, 3.0f);
                Vector3 rhs(4.0f, 5.0f, 6.0f);
                Vector3 result(-3.0f, -3.0f, -3.0f);

                AssertThat(lhs - rhs, Equals(result));
            });

            it("should properly negate the vector", [] {
                Vector3 test(1.0f, 2.0f, 3.0f);
                Vector3 result(-1.0f, -2.0f, -3.0f);

                AssertThat(-test, Equals(result));
            });
        });

        describe("::operator*", [] {
            it("should multiply properly by a scalar value", [] {
                Vector3 lhs(1.0f, 2.0f, 3.0f);
                float rhs = 2.0f;
                Vector3 result(2.0f, 4.0f, 6.0f);

                AssertThat(lhs * rhs, Equals(result));
            });
        });

        describe("::operator+=", [] {
            it("should add properly two vectors and modify the origin", [] {
                Vector3 lhs(1.0f, 2.0f, 3.0f);
                Vector3 rhs(4.0f, 5.0f, 6.0f);
                Vector3 result(5.0f, 7.0f, 9.0f);

                lhs += rhs;
                AssertThat(lhs, Equals(result));
            });
        });

        describe("::operator*=", [] {
            it("should multiply assign properly with scalar", [] {
                Vector3 lhs(1.0f, 2.0f, 3.0f);
                float rhs = 2.0f;
                Vector3 result(2.0f, 4.0f, 6.0f);

                lhs *= rhs;
                AssertThat(lhs, Equals(result));
            });

            it("should multiply assign properly with vector", [] {
                Vector3 lhs(1.0f, 2.0f, 3.0f);
                Vector3 rhs(4.0f, 5.0f, 6.0f);
                Vector3 result(4.0f, 10.0f, 18.0f);

                lhs *= rhs;
                AssertThat(lhs, Equals(result));
            });
        });

        describe("#operator*", [] {
            it("should multiply properly with a scalar as left hand side", [] {
                float lhs = 2.0f;
                Vector3 rhs(1.0f, 2.0f, 3.0f);
                Vector3 result(2.0f, 4.0f, 6.0f);

                AssertThat(lhs * rhs, Equals(result));
            });
        });
    });
});