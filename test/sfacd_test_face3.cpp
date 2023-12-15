#include "sfacd_math.hpp"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sfacd
{
	TEST_CLASS(test_face3)
	{
	public:

		TEST_METHOD(test_constructor)
		{
			const face3 f1;
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == f1.vertex[0]);
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == f1.vertex[1]);
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 0.0f } == f1.vertex[2]);

			const face3 f2(vector3{ 1.0f, 0.0f, 0.0f }, vector3{ 0.0f, 1.0f, 0.0f }, vector3{ 0.0f, 0.0f, 1.0f });
			Assert::IsTrue(vector3{ 1.0f, 0.0f, 0.0f } == f2.vertex[0]);
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } == f2.vertex[1]);
			Assert::IsTrue(vector3{ 0.0f, 0.0f, 1.0f } == f2.vertex[2]);
		}

		TEST_METHOD(test_is_degenerate)
		{
			Assert::IsTrue(face3().is_degenerate());
			Assert::IsTrue(face3(vector3{ 0.0f, 0.0f, 0.0f }, vector3{ 0.0f, 0.0f, 0.0f }, vector3{ 0.0f, 0.0f, 0.0f }).is_degenerate());
			Assert::IsTrue(face3(vector3{ 1.0f, 0.0f, 0.0f }, vector3{ 1.0f, 0.0f, 0.0f }, vector3{ 1.0f, 0.0f, 0.0f }).is_degenerate());
			Assert::IsTrue(face3(vector3{ 0.0f, 0.0f, 0.0f }, vector3{ 0.0f, 1.0f, 0.0f }, vector3{ 0.0f, 2.0f, 0.0f }).is_degenerate());
			Assert::IsFalse(face3(vector3{ 1.0f, 0.0f, 0.0f }, vector3{ 0.0f, 1.0f, 0.0f }, vector3{ 0.0f, 0.0f, 1.0f }).is_degenerate());
		}

		TEST_METHOD(test_plane)
		{
			const plane3 p = face3(vector3{ 0.0f, 1.0f, 0.0f }, vector3{ 0.0f, 1.0f, 1.0f }, vector3{ 1.0f, 1.0f, 0.0f }).plane();
			Assert::IsTrue(vector3{ 0.0f, 1.0f, 0.0f } == p.normal);
			Assert::AreEqual(1.0f, p.distance);
		}

		TEST_METHOD(test_slice)
		{
			const face3 f1(vector3{ 0.0f, 0.0f, 0.0f }, vector3{ 0.0f, 2.0f, 0.0f }, vector3{ 0.0f, 2.0f, 2.0f });
			const plane3 p1(vector3{ 0.0f, 1.0f, 0.0f }, 1.0f);

			face3 faces[3];
			const int count = f1.slice(p1, faces);
			Assert::AreEqual(3, count);
		}
	};
}
