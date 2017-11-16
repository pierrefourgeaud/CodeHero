// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <bandit/bandit.h>
#include "core/math/utils.h"
#include "core/math/quaternion.h"

using namespace bandit;
using namespace snowhouse;
using namespace CodeHero;

go_bandit([]() {
    describe("Quaternion", []() {
        describe("::LengthSquared", [] {
            it("should properly calculate the length squared", [] {
                Quaternion test(1.0f, 2.0f, 3.0f, 4.0f);

                AssertThat(test.LengthSquared(), Equals(30.0f));
            });
        });

        describe("::Length", [] {
            it("should properly calculate the length", [] {
                Quaternion test(2.0f, 2.0f, 2.0f, 2.0f);

                AssertThat(test.Length(), Equals(4.0f));
            });
        });
    });
});