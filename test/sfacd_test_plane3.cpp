#include "sfacd_math.hpp"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sfacd
{
	TEST_CLASS(test_plane3)
	{
	public:

		TEST_METHOD(test_constructor)
		{
			const plane3 p1;
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == p1.normal);
			Assert::AreEqual(0.0f, p1.distance);

			const plane3 p2(vector3{ 1.0f, 0.0f, 0.0f }, 2.0f);
			Assert::IsTrue(vector3{ 1.0f, 0.0f, 0.0f } == p2.normal);
			Assert::AreEqual(2.0f, p2.distance);

			const plane3 p3(vector3{ 1.0f, 0.0f, 0.0f }, vector3{ 2.0f, 0.0f, 0.0f });
			Assert::IsTrue(vector3{ 1.0f, 0.0f, 0.0f } == p3.normal);
			Assert::AreEqual(2.0f, p3.distance);

			const plane3 p4(vector3{ 0.0f, 1.0f, 0.0f }, vector3{ 0.0f, 1.0f, 1.0f }, vector3{ 1.0f, 1.0f, 0.0f });
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } == p4.normal);
			Assert::AreEqual(1.0f, p4.distance);
		}

		TEST_METHOD(test_is_equal_approx)
		{
			Assert::IsTrue(plane3().is_equal_approx(plane3()));
			Assert::IsTrue(plane3(vector3{ 1.0f, 0.0f, 0.0f }, 2.0f).is_equal_approx(plane3(vector3{ 1.0f, 0.0f, 0.0f }, 2.0f)));
			Assert::IsFalse(plane3(vector3{ 1.0f, 0.0f, 0.0f }, 2.0f).is_equal_approx(plane3(vector3{ 1.0f, 0.0f, 0.0f }, 2.1f)));
		}

		TEST_METHOD(test_distance_to)
		{
			Assert::AreEqual(-1.0f, plane3(vector3{ 0.0f, 1.0f, 0.0f }, 1.0f).distance_to(vector3{ 0.0f, 0.0f, 0.0f }));
			Assert::AreEqual(0.0f, plane3(vector3{0.0f, 1.0f, 0.0f}, 1.0f).distance_to(vector3{ 0.0f, 1.0f, 0.0f }));
			Assert::AreEqual(1.0f, plane3(vector3{ 0.0f, 1.0f, 0.0f }, 1.0f).distance_to(vector3{ 0.0f, 2.0f, 0.0f }));
		}

		TEST_METHOD(test_side)
		{
			Assert::AreEqual(-1, plane3(vector3{ 0.0f, 1.0f, 0.0f }, 1.0f).side(vector3{ 0.0f, 0.0f, 0.0f }));
			Assert::AreEqual(0, plane3(vector3{ 0.0f, 1.0f, 0.0f }, 1.0f).side(vector3{ 0.0f, 1.0f, 0.0f }));
			Assert::AreEqual(1, plane3(vector3{ 0.0f, 1.0f, 0.0f }, 1.0f).side(vector3{ 0.0f, 2.0f, 0.0f }));
		}

		TEST_METHOD(test_project)
		{
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } == plane3(vector3{ 0.0f, 1.0f, 0.0f }, 1.0f).project(vector3{ 0.0f, 0.0f, 0.0f }));
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } == plane3(vector3{ 0.0f, 1.0f, 0.0f }, 1.0f).project(vector3{ 0.0f, 1.0f, 0.0f }));
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } == plane3(vector3{ 0.0f, 1.0f, 0.0f }, 1.0f).project(vector3{ 0.0f, 2.0f, 0.0f }));
		}

		TEST_METHOD(test_operator_equals)
		{
			Assert::IsTrue(plane3() == plane3());
			Assert::IsTrue(plane3(vector3{ 1.0f, 0.0f, 0.0f }, 2.0f) == plane3(vector3{ 1.0f, 0.0f, 0.0f }, 2.0f));
			Assert::IsFalse(plane3(vector3{ 1.0f, 0.0f, 0.0f }, 2.0f) == plane3(vector3{ 1.0f, 0.0f, 0.0f }, 2.1f));
		}

		TEST_METHOD(test_operator_not_equals)
		{
			Assert::IsFalse(plane3() != plane3());
			Assert::IsFalse(plane3(vector3{ 1.0f, 0.0f, 0.0f }, 2.0f) != plane3(vector3{ 1.0f, 0.0f, 0.0f }, 2.0f));
			Assert::IsTrue(plane3(vector3{ 1.0f, 0.0f, 0.0f }, 2.0f) != plane3(vector3{ 1.0f, 0.0f, 0.0f }, 2.1f));
		}
	};
}
