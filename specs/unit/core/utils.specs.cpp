// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <bandit/bandit.h>
#include "core/utils.h"

using namespace bandit;
using namespace snowhouse;
using namespace CodeHero;

go_bandit([]() {
    describe("::StartsWith", [] {
        it("should return true if starts we correct prefix", [] {
            AssertThat(StartsWith("This is a test", "This"), IsTrue());
        });

        it("should return true if the prefix is empty", [] {
            AssertThat(StartsWith("This is a test", ""), IsTrue());
        });

        it("should return false if the prefix doesn't match the starts of the string", [] {
            AssertThat(StartsWith("This is a test", "Wrong"), IsFalse());
        });
    });
});