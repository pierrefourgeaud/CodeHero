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

    describe("::Split", [] {
        it("should split the string normally", [] {
            std::string test = "This|is|a|test";
            auto result = Split(test, '|');
            std::vector<std::string> expected = {"This", "is", "a", "test"};

            AssertThat(result, Equals(expected));
        });

        it("should split the string normally if no delimiter are passed and use default", [] {
            std::string test = "This is a test";
            auto result = Split(test);
            std::vector<std::string> expected = {"This", "is", "a", "test"};

            AssertThat(result, Equals(expected));
        });

        it("should return empty vector if empty string is passed", [] {
            std::string test = "";
            auto result = Split(test);
            std::vector<std::string> expected;

            AssertThat(result, Equals(expected));
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

    describe("::LowerCased", [] {
        it("should lower case properly a string regardless of special chars", [] {
            std::string test("Th1s 1S pr377Y W31RD !!@#$   ");
            std::string result("th1s 1s pr377y w31rd !!@#$   ");

            test = LowerCased(test);
            AssertThat(test, Equals(result));
        });

        it("should not do anything on an empty string", [] {
            std::string test;
            std::string result;

            test = LowerCased(test);
            AssertThat(test, Equals(result));
        });
    });

    describe("::Join", [] {
        it("should return empty string if the input vector is empty", [] {
            std::string test = Join({});
            std::string result;

            AssertThat(test, Equals(result));
        });

        it("should return the proper string if delimiter wasn't passed", [] {
            std::string test = Join({"This", "is", "a", "test."});
            std::string result = "This is a test.";

            AssertThat(test, Equals(result));
        });

        it("should properly join the vector into a string with correct delimiter", [] {
            std::string test = Join({"This", "is", "a", "test."}, ' ');
            std::string result = "This is a test.";

            AssertThat(test, Equals(result));
        });
    });

    describe("::IsIn", [] {
        it("should return true if the searched term is inside the array", [] {
            std::string toFind = "test";
            std::vector<std::string> list = {"test", "is", "in"};
            AssertThat(IsIn(toFind, list), IsTrue());
        });

        it("should return false if the searched term is not in the array", [] {
            std::string toFind = "test";
            std::vector<std::string> list = {"is", "not", "in"};
            AssertThat(IsIn(toFind, list), IsFalse());
        });

        it("should return false if the array is empty", [] {
            std::string toFind = "test";
            std::vector<std::string> list = {};
            AssertThat(IsIn(toFind, list), IsFalse());
        });
    });
});