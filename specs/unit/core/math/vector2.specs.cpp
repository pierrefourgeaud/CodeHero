// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <bandit/bandit.h>
#include "core/math/vector2.h"

using namespace bandit;
using namespace snowhouse;
using namespace CodeHero;

go_bandit([]() {
    describe("Vector2", []() {
        describe("Constructor", []() {
            it("should initialize vector with 0s if no arguments", [] {
                Vector2 test;

                AssertThat(test.x(), Equals(0.0f));
                AssertThat(test.y(), Equals(0.0f));
            });

            it("should initialize vector with correct x and y if provided", [] {
                float x = 1.5f;
                float y = 1.5f;
                Vector2 test(x, y);

                AssertThat(test.x(), Equals(x));
                AssertThat(test.y(), Equals(y));
            });
        });

        describe("::Length", [] {
            it("should compute the proper length", [] {
                float x = 2.0f;
                float y = 2.0f;
                Vector2 test(x, y);

                float res = 2.8284271247461903f;
                AssertThat(test.Length(), Equals(res));
            });
        });

        describe("::Normalize / :Normalized", [] {
            it("should compute the normalized vector", [] {
                Vector2 test(1.0f, 1.0f);

                float res = 0.70710678118f;
                test.Normalize();
                AssertThat(test.x(), Equals(res));
                AssertThat(test.y(), Equals(res));
            });

            it("should compute a new normalize network and not touch the initial one", [] {
                float base = 1.0f;
                Vector2 test(base, base);

                float res = 0.70710678118f;
                Vector2 result = test.Normalized();
                AssertThat(test.x(), Equals(base));
                AssertThat(test.y(), Equals(base));
                AssertThat(result.x(), Equals(res));
                AssertThat(result.y(), Equals(res));
            });
        });

        describe("::operator==", [] {
            it("should return true if condition is valid", [] {
                Vector2 lhs(1.0f, 2.0f);
                Vector2 rhs(1.0f, 2.0f);

                AssertThat(lhs == rhs, Is().True());
            });

            it("should return false if condition is invalid", [] {
                Vector2 lhs(1.0f, 2.0f);
                Vector2 rhs(3.0f, 4.0f);

                AssertThat(lhs == rhs, Is().False());
            });
        });

        describe("::operator-", [] {
            it("should substract properly two vectors", [] {
                Vector2 lhs(1.0f, 2.0f);
                Vector2 rhs(3.0f, 4.0f);
                Vector2 result(-2.0f, -2.0f);

                AssertThat(lhs - rhs, Equals(result));
            });
        });
    });
});