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
            AssertThat(StartsWith("This is a test", "This is a test"), IsTrue());
        });

        it("should return true if the prefix is empty", [] {
            AssertThat(StartsWith("This is a test", ""), IsTrue());
        });

        it("should return false if the prefix doesn't match the start of the string", [] {
            AssertThat(StartsWith("This is a test", "Wrong"), IsFalse());
            AssertThat(StartsWith("This is a test", "This iz"), IsFalse());
            AssertThat(StartsWith("This is a test", "Zhis is"), IsFalse());
        });
    });

    describe("::EndsWith", [] {
        it("should return true if ends with correct suffix", [] {
            AssertThat(EndsWith("This is a test", "test"), IsTrue());
            AssertThat(EndsWith("This is a test", "This is a test"), IsTrue());
        });

        it("should return true if suffix is empty", [] {
            AssertThat(EndsWith("This is a test", ""), IsTrue());
        });

        it("should return false if the suffix doesn't match the end of the string", [] {
            AssertThat(EndsWith("This is a test", "wrong"), IsFalse());
            AssertThat(EndsWith("This is a test", "tesz"), IsFalse());
            AssertThat(EndsWith("This is a test", "zest"), IsFalse());
        });
    });
});