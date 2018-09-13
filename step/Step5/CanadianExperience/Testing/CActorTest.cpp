/**
 * \file CActorTest.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "CppUnitTest.h"
#include "Actor.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CActorTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCActorConstructor)
		{
			CActor actor(L"Harold");
			Assert::AreEqual(std::wstring(L"Harold"), actor.GetName());
		}
		TEST_METHOD(TestCActorEnabled)
		{
			CActor actor(L"Harold");
			Assert::IsTrue(actor.IsEnabled()); //default

			actor.SetEnabled(false);
			Assert::IsFalse(actor.IsEnabled());
		}
		TEST_METHOD(TestCActorClickable)
		{
			CActor actor(L"Harold");
			Assert::IsTrue(actor.IsClickable()); //default

			actor.SetClickable(false);
			Assert::IsFalse(actor.IsClickable());
		}
		TEST_METHOD(TestCActorPosition)
		{
			CActor actor(L"Harold");
			//default
			Assert::AreEqual(0, actor.GetPosition().X);
			Assert::AreEqual(0, actor.GetPosition().Y);

			Gdiplus::Point testPoint = Gdiplus::Point(4, 5);
			actor.SetPosition(testPoint);

			Assert::AreEqual(4, actor.GetPosition().X);
			Assert::AreEqual(5, actor.GetPosition().Y);
		}
	};
}