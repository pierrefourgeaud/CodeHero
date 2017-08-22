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
            it("should initialize vector with 0s if no arguments", []() {
                Vector2 test;

                AssertThat(test.x(), Equals(0.0f));
            });
        });
    });
});