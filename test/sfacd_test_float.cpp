#include "sfacd_math.hpp"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sfacd
{
    TEST_CLASS(test_float)
    {
    public:
        TEST_METHOD(test_is_zero_approx)
        {
            Assert::IsTrue(is_zero_approx(0.0f));
            Assert::IsTrue(is_zero_approx(0.0000001f));
            Assert::IsTrue(is_zero_approx(-0.0000001f));
            Assert::IsFalse(is_zero_approx(0.1f));
            Assert::IsFalse(is_zero_approx(-0.1f));
        }

        TEST_METHOD(test_is_equal_approx)
        {
            Assert::IsTrue(is_equal_approx(0.0f, 0.0f));
            Assert::IsTrue(is_equal_approx(1.0f, 1.0f));
            Assert::IsTrue(is_equal_approx(1000000.0f, 1000000.0f));
            Assert::IsTrue(is_equal_approx(-1000000.0f, -1000000.0f));
            Assert::IsFalse(is_equal_approx(1000.0f, 1000.1f));
            Assert::IsFalse(is_equal_approx(-1000.0f, -1000.1f));
        }

        TEST_METHOD(test_get_sign)
        {
            Assert::AreEqual(0, get_sign(0.0f));
            Assert::AreEqual(0, get_sign(0.0000001f));
            Assert::AreEqual(0, get_sign(-0.0000001f));
            Assert::AreEqual(1, get_sign(0.1f));
            Assert::AreEqual(-1, get_sign(-0.1f));
            Assert::AreEqual(1, get_sign(1000000.0f));
            Assert::AreEqual(-1, get_sign(-1000000.0f));
        }

        TEST_METHOD(test_lerp)
        {
            Assert::AreEqual(0.0f, lerp(0.0f, 1.0f, 0.0f));
            Assert::AreEqual(0.5f, lerp(0.0f, 1.0f, 0.5f));
            Assert::AreEqual(1.0f, lerp(0.0f, 1.0f, 1.0f));
            Assert::AreEqual(0.0f, lerp(0.0f, 100.0f, 0.0f));
            Assert::AreEqual(50.0f, lerp(0.0f, 100.0f, 0.5f));
            Assert::AreEqual(100.0f, lerp(0.0f, 100.0f, 1.0f));
            Assert::AreEqual(-1.0f, lerp(0.0f, 1.0f, -1.0f));
            Assert::AreEqual(2.0f, lerp(0.0f, 1.0f, 2.0f));
        }
    };
}
