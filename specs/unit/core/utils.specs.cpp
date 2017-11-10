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

    describe("::Trim", [] {
        it("should trim on the left side", [] {
            std::string test("  \t This is a test");
            std::string result("This is a test");

            Trim(test);
            AssertThat(test, Equals(result));
        });

        it("should trim on the right side", [] {
            std::string test("This is a test    \t   ");
            std::string result("This is a test");

            Trim(test);
            AssertThat(test, Equals(result));
        });

        it("should trim on the both side", [] {
            std::string test("  \t This is a test    \t   ");
            std::string result("This is a test");

            Trim(test);
            AssertThat(test, Equals(result));
        });

        it("should not modify the string if not needed", [] {
            std::string test("This is a test");
            std::string result = test;

            Trim(test);
            AssertThat(test, Equals(result));
        });
    });

    describe("::ToLowerCase", [] {
        it("should lower case properly a string regardless of special chars", [] {
            std::string test("Th1s 1S pr377Y W31RD !!@#$   ");
            std::string result("th1s 1s pr377y w31rd !!@#$   ");

            ToLowerCase(test);
            AssertThat(test, Equals(result));
        });

        it("should not do anything on an empty string", [] {
            std::string test;
            std::string result;

            ToLowerCase(test);
            AssertThat(test, Equals(result));
        });
    });
});