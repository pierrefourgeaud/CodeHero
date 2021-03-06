// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <bandit/bandit.h>
#include "core/math/matrix3.h"
#include "core/math/vector3.h"

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
                Matrix3 lhs(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
                Matrix3 rhs(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

                AssertThat(lhs == rhs, Is().True());
            });

            it("should return true if 2 matrices are equal", [] {
                Matrix3 lhs(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
                Matrix3 rhs(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);

                AssertThat(lhs == rhs, Is().False());
            });
        });

        describe("::operator*", [] {
            it("should multiply with another Matrix3", [] {
                Matrix3 lhs(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
                Matrix3 rhs(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);

                Matrix3 result(30.0f, 36.0f, 42.0f, 66.0f, 81.0f, 96.0f, 102.0f, 126.0f, 150.0f);

                AssertThat(lhs * rhs, Equals(result));
            });

            it("should multiply with vector3", [] {
                Matrix3 lhs(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
                Vector3 rhs(1.0f, 2.0f, 3.0f);

                Vector3 result(14.0f, 32.0f, 50.0f);

                AssertThat(lhs * rhs, Equals(result));
            });
        });

        describe("::operator-", [] {
            it("should negate all members of the matrix", [] {
                Matrix3 lhs(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
                Matrix3 rhs(-1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f, -7.0f, -8.0f, -9.0f);

                AssertThat(-lhs == rhs, Is().True());
            });
        });

        describe("::Transpose", [] {
            it("should transpose the matrix in place and return a reference", [] {
                Matrix3 input(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
                Matrix3 output(1.0f, 4.0f, 7.0f, 2.0f, 5.0f, 8.0f, 3.0f, 6.0f, 9.0f);

                Matrix3 res = input.Transpose();

                AssertThat(input, Equals(output));
                AssertThat(res, Equals(output));
            });
        });

        describe("::Transposed", [] {
            it("should transpose the matrix and return a new object. Input not modified.", [] {
                Matrix3 input(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
                Matrix3 save = input; // Copy to make sure that the source is not modified
                Matrix3 output(1.0f, 4.0f, 7.0f, 2.0f, 5.0f, 8.0f, 3.0f, 6.0f, 9.0f);

                Matrix3 res = input.Transposed();

                AssertThat(input, Equals(save));
                AssertThat(res, Equals(output));
            });
        });
    });
});