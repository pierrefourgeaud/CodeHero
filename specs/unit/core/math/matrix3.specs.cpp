// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <bandit/bandit.h>
#include "core/math/matrix3.h"

using namespace bandit;
using namespace snowhouse;
using namespace CodeHero;

go_bandit([]() {
    describe("Matrix3", []() {
        describe("Constructor", []() {
            it("should initialize matrix3 to identity if no arguments", [] {
                Matrix3 test;

                AssertThat(test.Get(0, 0), Equals(1.0f));
                AssertThat(test.Get(0, 1), Equals(0.0f));
                AssertThat(test.Get(0, 2), Equals(0.0f));

                AssertThat(test.Get(1, 0), Equals(0.0f));
                AssertThat(test.Get(1, 1), Equals(1.0f));
                AssertThat(test.Get(1, 2), Equals(0.0f));

                AssertThat(test.Get(2, 0), Equals(0.0f));
                AssertThat(test.Get(2, 1), Equals(0.0f));
                AssertThat(test.Get(2, 2), Equals(1.0f));
            });
        });

        describe("::operator==", [] {
            it("should return true if 2 matrices are equal", [] {
                Matrix3 lhs(1.0f, 2.0f, 3.0f,
                            4.0f, 5.0f, 6.0f,
                            7.0f, 8.0f, 9.0f);
                Matrix3 rhs(1.0f, 2.0f, 3.0f,
                            4.0f, 5.0f, 6.0f,
                            7.0f, 8.0f, 9.0f);

                AssertThat(lhs == rhs, Is().True());
            });

            it("should return true if 2 matrices are equal", [] {
                Matrix3 lhs(1.0f, 2.0f, 3.0f,
                            4.0f, 5.0f, 6.0f,
                            7.0f, 8.0f, 9.0f);
                Matrix3 rhs(9.0f, 8.0f, 7.0f,
                            6.0f, 5.0f, 4.0f,
                            3.0f, 2.0f, 1.0f);

                AssertThat(lhs == rhs, Is().False());
            });
        });

        describe("::operator-", [] {
            it("should negate all members of the matrix", [] {
                Matrix3 lhs(1.0f, 2.0f, 3.0f,
                            4.0f, 5.0f, 6.0f,
                            7.0f, 8.0f, 9.0f);
                Matrix3 rhs(-1.0f, -2.0f, -3.0f,
                            -4.0f, -5.0f, -6.0f,
                            -7.0f, -8.0f, -9.0f);

                AssertThat(-lhs == rhs, Is().True());
            });
        });
    });
});