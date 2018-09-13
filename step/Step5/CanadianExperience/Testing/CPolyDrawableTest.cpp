/**
 * \file CPolyDrawableTest.cpp
 *
 * \author Nic Wiggins
 */

#include "stdafx.h"
#include "CppUnitTest.h"
#include "PolyDrawable.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;

namespace Testing
{
	TEST_CLASS(CPolyDrawableTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCPolyDrawableConstructor)
		{
			CPolyDrawable polyDrawable(L"Harold");
			Assert::AreEqual(std::wstring(L"Harold"), polyDrawable.GetName());
		}
		/** Sees if two colors are the same
		* \param c1 First color 
		* \param c2 second color
		*/
		bool sameColor(Color c1, Color c2)
		{
			return c1.GetValue() == c2.GetValue();
		}
		TEST_METHOD(TestCPolyDrawableColor)
		{
			CPolyDrawable polyDrawable(L"Harold");

			Color defaultColor = Color::Black;
			Assert::IsTrue(sameColor(polyDrawable.GetColor(), defaultColor));

			Color newColor = Color::Green;
			polyDrawable.SetColor(newColor);
			Assert::IsTrue(sameColor(polyDrawable.GetColor(), newColor));
		}
	};
}