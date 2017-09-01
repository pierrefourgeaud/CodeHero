// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <bandit/bandit.h>
#include "core/math/utils.h"

using namespace bandit;
using namespace snowhouse;
using namespace CodeHero;

go_bandit([]() {
    describe("::Clamp", []() {
        it("should not do anything if in the range", [] {
            AssertThat(Clamp(5.0f, 0.0f, 10.0f), Equals(5.0f));
            AssertThat(Clamp(5, 0, 10), Equals(5));
        });

        it("should Clamp the value back in the range is value is smaller than min", [] {
            AssertThat(Clamp(-5.0f, 0.0f, 10.0f), Equals(0.0f));
            AssertThat(Clamp(-5, 0, 10), Equals(0));
        });

        it("should Clamp the value back in the range is value is bigger than max", [] {
            AssertThat(Clamp(15.0f, 0.0f, 10.0f), Equals(10.0f));
            AssertThat(Clamp(15, 0, 10), Equals(10));
        });
    });
});