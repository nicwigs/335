/**
 * \file CAnimChannelAngleTest.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "CppUnitTest.h"
#include "AnimChannelAngle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CAnimChannelAngleTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCAnimChannelAngleName)
		{
			CAnimChannelAngle animChannelAngle;
			//default
			Assert::AreEqual(std::wstring(L""), animChannelAngle.GetName());

			animChannelAngle.SetName(L"Nic");
			Assert::AreEqual(std::wstring(L"Nic"), animChannelAngle.GetName());
			animChannelAngle.SetName(L"Adam");
			Assert::AreEqual(std::wstring(L"Adam"), animChannelAngle.GetName());
		}

	};
}