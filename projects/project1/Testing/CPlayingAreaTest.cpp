/**
 * \file CPlayingAreaTest.cpp
 *
 * \author Mark Elinski
 */

#include "stdafx.h"
#include "CppUnitTest.h"
#include "PlayingArea.h"

 /// The range from the center to an edge for the playing area
 /// in virtual pixels
const double GridRadius = 500.0;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	/*
	* Class for testing CPlayingArea 
	*/
	TEST_CLASS(CPlayingAreaTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		/*
		* Test the GetGridRadius() method 
		*/
		TEST_METHOD(TestCPlayingAreaGetGridRadius)
		{
			CPlayingArea playArea;
			Assert::IsTrue(playArea.GetGridRadius() == GridRadius);
		}

	};
}