#include "sfacd_math.hpp"
#include "CppUnitTest.h"
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sfacd
{
	TEST_CLASS(test_float)
	{
	public:
		TEST_METHOD(test_constructor)
		{
			const vector3 v1;
			Assert::AreEqual(0.0f, v1.x);
			Assert::AreEqual(0.0f, v1.y);
			Assert::AreEqual(0.0f, v1.z);

			const vector3 v2(1.0f, 2.0f, 3.0f);
			Assert::AreEqual(1.0f, v2.x);
			Assert::AreEqual(2.0f, v2.y);
			Assert::AreEqual(3.0f, v2.z);

			const vector3 v3(-1000.0f, -2000.0f, -3000.0f);
			Assert::AreEqual(-1000.0f, v3.x);
			Assert::AreEqual(-2000.0f, v3.y);
			Assert::AreEqual(-3000.0f, v3.z);
		}

		TEST_METHOD(test_length2)
		{
			Assert::AreEqual(0.0f, vector3(0.0f, 0.0f, 0.0f).length2());
			Assert::AreEqual(1.0f, vector3(1.0f, 0.0f, 0.0f).length2());
			Assert::AreEqual(1.0f, vector3(0.0f, 1.0f, 0.0f).length2());
			Assert::AreEqual(1.0f, vector3(0.0f, 0.0f, 1.0f).length2());
			Assert::AreEqual(2.0f, vector3(1.0f, 1.0f, 0.0f).length2());
			Assert::AreEqual(2.0f, vector3(0.0f, 1.0f, 1.0f).length2());
			Assert::AreEqual(2.0f, vector3(1.0f, 0.0f, 1.0f).length2());
			Assert::AreEqual(3.0f, vector3(1.0f, 1.0f, 1.0f).length2());
			Assert::AreEqual(14000000.0f, vector3(1000.0f, 2000.0f, 3000.0f).length2());
		}

		TEST_METHOD(test_length)
		{
			Assert::AreEqual(0.0f, vector3(0.0f, 0.0f, 0.0f).length());
			Assert::AreEqual(1.0f, vector3(1.0f, 0.0f, 0.0f).length());
			Assert::AreEqual(1.0f, vector3(0.0f, 1.0f, 0.0f).length());
			Assert::AreEqual(1.0f, vector3(0.0f, 0.0f, 1.0f).length());
			Assert::AreEqual(std::sqrt(2.0f), vector3(1.0f, 1.0f, 0.0f).length());
			Assert::AreEqual(std::sqrt(2.0f), vector3(0.0f, 1.0f, 1.0f).length());
			Assert::AreEqual(std::sqrt(2.0f), vector3(1.0f, 0.0f, 1.0f).length());
			Assert::AreEqual(std::sqrt(3.0f), vector3(1.0f, 1.0f, 1.0f).length());
			Assert::AreEqual(std::sqrt(14000000.0f), vector3(1000.0f, 2000.0f, 3000.0f).length());
		}

		TEST_METHOD(test_dot)
		{
			Assert::AreEqual(0.0f, vector3(0.0f, 0.0f, 0.0f).dot(vector3(0.0f, 0.0f, 0.0f)));
			Assert::AreEqual(0.0f, vector3(1.0f, 0.0f, 0.0f).dot(vector3(0.0f, 1.0f, 0.0f)));
			Assert::AreEqual(0.0f, vector3(0.0f, 1.0f, 0.0f).dot(vector3(0.0f, 0.0f, 1.0f)));
			Assert::AreEqual(0.0f, vector3(0.0f, 0.0f, 1.0f).dot(vector3(1.0f, 0.0f, 0.0f)));
			Assert::AreEqual(1.0f, vector3(1.0f, 0.0f, 0.0f).dot(vector3(1.0f, 0.0f, 0.0f)));
			Assert::AreEqual(1.0f, vector3(0.0f, 1.0f, 0.0f).dot(vector3(0.0f, 1.0f, 0.0f)));
			Assert::AreEqual(1.0f, vector3(0.0f, 0.0f, 1.0f).dot(vector3(0.0f, 0.0f, 1.0f)));
			Assert::AreEqual(2.0f, vector3(1.0f, 1.0f, 0.0f).dot(vector3(1.0f, 1.0f, 0.0f)));
			Assert::AreEqual(2.0f, vector3(0.0f, 1.0f, 1.0f).dot(vector3(0.0f, 1.0f, 1.0f)));
			Assert::AreEqual(2.0f, vector3(1.0f, 0.0f, 1.0f).dot(vector3(1.0f, 0.0f, 1.0f)));
			Assert::AreEqual(3.0f, vector3(1.0f, 1.0f, 1.0f).dot(vector3(1.0f, 1.0f, 1.0f)));
		}

		TEST_METHOD(test_cross)
		{
			Assert::IsTrue(vector3(0.0f, 0.0f, 0.0f) == vector3(0.0f, 0.0f, 0.0f).cross(vector3(0.0f, 0.0f, 0.0f)));
			Assert::IsTrue(vector3(0.0f, 0.0f, 1.0f) == vector3(1.0f, 0.0f, 0.0f).cross(vector3(0.0f, 1.0f, 0.0f)));
			Assert::IsTrue(vector3(1.0f, 0.0f, 0.0f) == vector3(0.0f, 1.0f, 0.0f).cross(vector3(0.0f, 0.0f, 1.0f)));
			Assert::IsTrue(vector3(0.0f, 1.0f, 0.0f) == vector3(0.0f, 0.0f, 1.0f).cross(vector3(1.0f, 0.0f, 0.0f)));
			Assert::IsTrue(vector3(0.0f, 0.0f, 0.0f) == vector3(1.0f, 0.0f, 0.0f).cross(vector3(1.0f, 0.0f, 0.0f)));
			Assert::IsTrue(vector3(0.0f, 0.0f, 0.0f) == vector3(0.0f, 1.0f, 0.0f).cross(vector3(0.0f, 1.0f, 0.0f)));
			Assert::IsTrue(vector3(0.0f, 0.0f, 0.0f) == vector3(0.0f, 0.0f, 1.0f).cross(vector3(0.0f, 0.0f, 1.0f)));
		}

		TEST_METHOD(test_normalized)
		{
			Assert::IsTrue(vector3(0.0f, 0.0f, 0.0f) == vector3(0.0f, 0.0f, 0.0f).normalized());
			Assert::IsTrue(vector3(1.0f, 0.0f, 0.0f) == vector3(1.0f, 0.0f, 0.0f).normalized());
			Assert::IsTrue(vector3(0.0f, 1.0f, 0.0f) == vector3(0.0f, 1.0f, 0.0f).normalized());
			Assert::IsTrue(vector3(0.0f, 0.0f, 1.0f) == vector3(0.0f, 0.0f, 1.0f).normalized());
			Assert::IsTrue(vector3(1.0f, 0.0f, 0.0f) == vector3(100.0f, 0.0f, 0.0f).normalized());
			Assert::IsTrue(vector3(0.0f, 1.0f, 0.0f) == vector3(0.0f, 100.0f, 0.0f).normalized());
			Assert::IsTrue(vector3(0.0f, 0.0f, 1.0f) == vector3(0.0f, 0.0f, 100.0f).normalized());
		}

		TEST_METHOD(test_is_zero_approx)
		{
			Assert::IsTrue(vector3{0.0f, 0.0f, 0.0f}.is_zero_approx());
			Assert::IsTrue(vector3{ 0.0000001f, -0.0000001f, 0.0000001f }.is_zero_approx());
			Assert::IsFalse(vector3{ 0.0001f, 0.0f, 0.0f }.is_zero_approx());
			Assert::IsFalse(vector3{ 0.0f, 0.0001f, 0.0f }.is_zero_approx());
			Assert::IsFalse(vector3{ 0.0f, 0.0f, 0.0001f }.is_zero_approx());
		}

		TEST_METHOD(test_is_equal_approx)
		{
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f }.is_equal_approx(vector3{ 0.0f, 0.0f, 0.0f }));
			Assert::IsTrue(vector3{ 1.0f, 0.0f, 0.0f }.is_equal_approx(vector3{ 1.0f, 0.0f, 0.0f }));
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f }.is_equal_approx(vector3{ 0.0f, 1.0f, 0.0f }));
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 1.0f }.is_equal_approx(vector3{ 0.0f, 0.0f, 1.0f }));
			Assert::IsFalse(vector3{ 0.1f, 0.0f, 0.0f }.is_equal_approx(vector3{ 0.0f, 0.0f, 0.0f }));
			Assert::IsFalse(vector3{ 0.0f, 0.1f, 0.0f }.is_equal_approx(vector3{ 0.0f, 0.0f, 0.0f }));
			Assert::IsFalse(vector3{ 0.0f, 0.0f, 0.1f }.is_equal_approx(vector3{ 0.0f, 0.0f, 0.0f }));
		}

		TEST_METHOD(test_operator_equals)
		{
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 1.0f, 0.0f, 0.0f } == vector3{ 1.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } == vector3{ 0.0f, 1.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 1.0f } == vector3{ 0.0f, 0.0f, 1.0f });
		}

		TEST_METHOD(test_operator_not_equals)
		{
			Assert::IsFalse(vector3{ 0.0f, 0.0f, 0.0f } != vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsFalse(vector3{ 1.0f, 0.0f, 0.0f } != vector3{ 1.0f, 0.0f, 0.0f });
			Assert::IsFalse(vector3{ 0.0f, 1.0f, 0.0f } != vector3{ 0.0f, 1.0f, 0.0f });
			Assert::IsFalse(vector3{ 0.0f, 0.0f, 1.0f } != vector3{ 0.0f, 0.0f, 1.0f });
		}

		TEST_METHOD(test_operator_less_than)
		{
			Assert::IsFalse(vector3{ 0.0f, 0.0f, 0.0f } < vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsFalse(vector3{ 1.0f, 0.0f, 0.0f } < vector3{ 1.0f, 0.0f, 0.0f });
			Assert::IsFalse(vector3{ 0.0f, 1.0f, 0.0f } < vector3{ 0.0f, 1.0f, 0.0f });
			Assert::IsFalse(vector3{ 0.0f, 0.0f, 1.0f } < vector3{ 0.0f, 0.0f, 1.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } < vector3{ 0.0f, 0.0f, 0.1f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } < vector3{ 0.0f, 0.1f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } < vector3{ 0.1f, 0.0f, 0.0f });
		}

		TEST_METHOD(test_operator_greater_than)
		{
			Assert::IsFalse(vector3{ 0.0f, 0.0f, 0.0f } > vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsFalse(vector3{ 1.0f, 0.0f, 0.0f } > vector3{ 1.0f, 0.0f, 0.0f });
			Assert::IsFalse(vector3{ 0.0f, 1.0f, 0.0f } > vector3{ 0.0f, 1.0f, 0.0f });
			Assert::IsFalse(vector3{ 0.0f, 0.0f, 1.0f } > vector3{ 0.0f, 0.0f, 1.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.1f } > vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.1f, 0.0f } > vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.1f, 0.0f, 0.0f } > vector3{ 0.0f, 0.0f, 0.0f });
		}

		TEST_METHOD(test_operator_less_or_equals)
		{
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } <= vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 1.0f, 0.0f, 0.0f } <= vector3{ 1.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } <= vector3{ 0.0f, 1.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 1.0f } <= vector3{ 0.0f, 0.0f, 1.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } <= vector3{ 0.0f, 0.0f, 0.1f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } <= vector3{ 0.0f, 0.1f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } <= vector3{ 0.1f, 0.0f, 0.0f });
		}

		TEST_METHOD(test_operator_greater_or_equals)
		{
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } >= vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 1.0f, 0.0f, 0.0f } >= vector3{ 1.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } >= vector3{ 0.0f, 1.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 1.0f } >= vector3{ 0.0f, 0.0f, 1.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.1f } >= vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.1f, 0.0f } >= vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.1f, 0.0f, 0.0f } >= vector3{ 0.0f, 0.0f, 0.0f });
		}

		TEST_METHOD(test_operator_negate)
		{
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == -vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ -1.0f, 0.0f, 0.0f } == -vector3{ 1.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, -1.0f, 0.0f } == -vector3{ 0.0f, 1.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, -1.0f } == -vector3{ 0.0f, 0.0f, 1.0f });
		}

		TEST_METHOD(test_operator_add)
		{
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == vector3{ 0.0f, 0.0f, 0.0f } + vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 2.0f, 0.0f, 0.0f } == vector3{ 1.0f, 0.0f, 0.0f } + vector3{ 1.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 2.0f, 0.0f } == vector3{ 0.0f, 1.0f, 0.0f } + vector3{ 0.0f, 1.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 2.0f } == vector3{ 0.0f, 0.0f, 1.0f } + vector3{ 0.0f, 0.0f, 1.0f });
		}

		TEST_METHOD(test_operator_subtract)
		{
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == vector3{ 0.0f, 0.0f, 0.0f } - vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == vector3{ 1.0f, 0.0f, 0.0f } - vector3{ 1.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == vector3{ 0.0f, 1.0f, 0.0f } - vector3{ 0.0f, 1.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == vector3{ 0.0f, 0.0f, 1.0f } - vector3{ 0.0f, 0.0f, 1.0f });
			Assert::IsTrue(vector3{ 1.0f, 0.0f, 0.0f } == vector3{ 2.0f, 0.0f, 0.0f } - vector3{ 1.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } == vector3{ 0.0f, 2.0f, 0.0f } - vector3{ 0.0f, 1.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 1.0f } == vector3{ 0.0f, 0.0f, 2.0f } - vector3{ 0.0f, 0.0f, 1.0f });
		}

		TEST_METHOD(test_operator_multiply_vector3)
		{
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == vector3{ 0.0f, 0.0f, 0.0f } * vector3{ 0.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 1.0f, 0.0f, 0.0f } == vector3{ 1.0f, 0.0f, 0.0f } * vector3{ 1.0f, 1.0f, 1.0f });
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } == vector3{ 0.0f, 1.0f, 0.0f } * vector3{ 1.0f, 1.0f, 1.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 1.0f } == vector3{ 0.0f, 0.0f, 1.0f } * vector3{ 1.0f, 1.0f, 1.0f });
			Assert::IsTrue(vector3{ 1.0f, 2.0f, 3.0f } == vector3{ 1.0f, 1.0f, 3.0f } * vector3{ 1.0f, 2.0f, 1.0f });
		}

		TEST_METHOD(test_operator_multiply_float)
		{
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == vector3{ 0.0f, 0.0f, 0.0f } * 0.0f);
			Assert::IsTrue(vector3{ 1.0f, 0.0f, 0.0f } == vector3{ 1.0f, 0.0f, 0.0f } * 1.0f);
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } == vector3{ 0.0f, 1.0f, 0.0f } * 1.0f);
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 1.0f } == vector3{ 0.0f, 0.0f, 1.0f } * 1.0f);
			Assert::IsTrue(vector3{ 2.0f, 4.0f, 6.0f } == vector3{ 1.0f, 2.0f, 3.0f } * 2.0f);
		}

		TEST_METHOD(test_operator_divide_vector3)
		{
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == vector3{ 0.0f, 0.0f, 0.0f } / vector3{ 1.0f, 1.0f, 1.0f });
			Assert::IsTrue(vector3{ 1.0f, 0.0f, 0.0f } == vector3{ 1.0f, 0.0f, 0.0f } / vector3{ 1.0f, 1.0f, 1.0f });
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } == vector3{ 0.0f, 1.0f, 0.0f } / vector3{ 1.0f, 1.0f, 1.0f });
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 1.0f } == vector3{ 0.0f, 0.0f, 1.0f } / vector3{ 1.0f, 1.0f, 1.0f });
			Assert::IsTrue(vector3{ 1.0f, 2.0f, 3.0f } == vector3{ 1.0f, 2.0f, 3.0f } / vector3{ 1.0f, 1.0f, 1.0f });
			Assert::IsTrue(vector3{ 1.0f, 2.0f, 3.0f } == vector3{ 2.0f, 4.0f, 6.0f } / vector3{ 2.0f, 2.0f, 2.0f });
		}

		TEST_METHOD(test_operator_divide_float)
		{
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == vector3{ 0.0f, 0.0f, 0.0f } / 1.0f);
			Assert::IsTrue(vector3{ 1.0f, 0.0f, 0.0f } == vector3{ 1.0f, 0.0f, 0.0f } / 1.0f);
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } == vector3{ 0.0f, 1.0f, 0.0f } / 1.0f);
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 1.0f } == vector3{ 0.0f, 0.0f, 1.0f } / 1.0f);
			Assert::IsTrue(vector3{ 1.0f, 2.0f, 3.0f } == vector3{ 1.0f, 2.0f, 3.0f } / 1.0f);
			Assert::IsTrue(vector3{ 1.0f, 2.0f, 3.0f } == vector3{ 2.0f, 4.0f, 6.0f } / 2.0f);
		}
	};
}
