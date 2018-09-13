/**
* \file CGameTest.cpp
*
* \author Zoinul Choudhury
*/

#include "stdafx.h"
#include "CppUnitTest.h"
#include "Villain.h"
#include "Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/// Juicer filename 
const std::wstring JuicerImageName(L"images/juicer.png");

namespace Testing
{

	/** Mock class for testing CGameItem */
	class CItemMock : public CVillain
	{
	public:
		/** Constructor
		* \param game The game this is a member of */
		CItemMock(CGame *game) : CVillain(game, JuicerImageName, 0, 0) {}

		/** Draw the item
		* \param graphics The graphics context to draw on */
		virtual void Draw(Gdiplus::Graphics *graphics) {}

		virtual void Accept(CItemVisitor *visitor) override {}
	};

	TEST_CLASS(CVillainTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		/**
		* Test the CGameItem constructor
		*/
		TEST_METHOD(TestCVillainConstruct)
		{
			CGame game;
			CItemMock item(&game);
		}
	};
}