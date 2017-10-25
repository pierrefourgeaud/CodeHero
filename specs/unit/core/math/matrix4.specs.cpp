// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <bandit/bandit.h>
#include "core/math/matrix4.h"
#include "core/math/vector4.h"

using namespace bandit;
using namespace snowhouse;
using namespace CodeHero;

go_bandit([]() {
    describe("Matrix4", []() {
        describe("Constructor", []() {
            it("should initialize matrix4 to identity if no arguments", [] {
                Matrix4 test;

                AssertThat(test.Get(0, 0), Equals(1.0f));
                AssertThat(test.Get(0, 1), Equals(0.0f));
                AssertThat(test.Get(0, 2), Equals(0.0f));
                AssertThat(test.Get(0, 3), Equals(0.0f));

                AssertThat(test.Get(1, 0), Equals(0.0f));
                AssertThat(test.Get(1, 1), Equals(1.0f));
                AssertThat(test.Get(1, 2), Equals(0.0f));
                AssertThat(test.Get(1, 3), Equals(0.0f));

                AssertThat(test.Get(2, 0), Equals(0.0f));
                AssertThat(test.Get(2, 1), Equals(0.0f));
                AssertThat(test.Get(2, 2), Equals(1.0f));
                AssertThat(test.Get(2, 3), Equals(0.0f));

                AssertThat(test.Get(3, 0), Equals(0.0f));
                AssertThat(test.Get(3, 1), Equals(0.0f));
                AssertThat(test.Get(3, 2), Equals(0.0f));
                AssertThat(test.Get(3, 3), Equals(1.0f));
            });
        });

        describe("::operator==", [] {
            it("should return true if 2 matrices are equal", [] {
                Matrix4 lhs(1.0f,  2.0f,  3.0f,  4.0f,
                            5.0f,  6.0f,  7.0f,  8.0f,
                            9.0f,  10.0f, 11.0f, 12.0f,
                            13.0f, 14.0f, 15.0f, 16.0f);
                Matrix4 rhs(1.0f,  2.0f,  3.0f,  4.0f,
                            5.0f,  6.0f,  7.0f,  8.0f,
                            9.0f,  10.0f, 11.0f, 12.0f,
                            13.0f, 14.0f, 15.0f, 16.0f);

                AssertThat(lhs == rhs, Is().True());
            });

            it("should return true if 2 matrices are equal", [] {
                Matrix4 lhs(1.0f,  2.0f,  3.0f,  4.0f,
                            5.0f,  6.0f,  7.0f,  8.0f,
                            9.0f,  10.0f, 11.0f, 12.0f,
                            13.0f, 14.0f, 15.0f, 16.0f);
                Matrix4 rhs(16.0f, 15.0f, 14.0f, 13.0f,
                            12.0f, 11.0f, 10.0f, 9.0f,
                            8.0f,  7.0f,  6.0f,  5.0f,
                            4.0f,  3.0f,  2.0f,  1.0f);

                AssertThat(lhs == rhs, Is().False());
            });
        });

        describe("operator*", [] {
            it("should multiply with a vector4", [] {
                Matrix4 lhs(1.0f,  2.0f,  3.0f,  4.0f,
                            5.0f,  6.0f,  7.0f,  8.0f,
                            9.0f,  10.0f, 11.0f, 12.0f,
                            13.0f, 14.0f, 15.0f, 16.0f);
                Vector4 rhs(1.0f, 2.0f, 3.0f, 4.0f);

                Vector4 result(30.0f, 70.0f, 110.f, 150.0f);
                AssertThat(lhs * rhs, Equals(result));
            });
        });
    });
});