/**
 * \file CGameTest.cpp
 *
 * \author Mark Elinski
 */

#include "stdafx.h"
#include "CppUnitTest.h"
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include "Game.h"
#include "GameItem.h"
#include "Juicer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	/**
	* Class for testing CGame
	*/
	TEST_CLASS(CGameTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		/**
		* Test the CGame constructor
		*/
		TEST_METHOD(TestCGameConstruct)
		{
			CGame game;
		}

		/**
		* Test the CGame HitTest method
		*/
		TEST_METHOD(TestCGameHitTest)
		{
			CGame game;

			Assert::IsTrue(game.HitTest(100, 200) == nullptr,
				L"Testing empty game");

			shared_ptr<CJuicer> juicer = make_shared<CJuicer>(&game);
			juicer->SetLocation(100, 200);
			game.Add(juicer);

			Assert::IsTrue(game.HitTest(100, 200) == juicer,
				L"Testing juicer at 100, 200");

			// test that HitTest will find the image on top
			shared_ptr<CJuicer> juicer2 = make_shared<CJuicer>(&game);
			juicer2->SetLocation(100, 200);
			game.Add(juicer2);

			Assert::IsTrue(game.HitTest(100, 200) == juicer2,
				L"Testing that top juicer is selected at 100, 200");

			// test that HitTest returns nullptr where there is no image
			Assert::IsTrue(game.HitTest(800, 800) == nullptr,
				L"Testing location with no items");
		}

		/**
		* Test the CGame NewGame method
		*/
		TEST_METHOD(TestCGameNewGame)
		{
			CGame game;

			game.GetGru()->SetLocation(100, 100);

			game.NewGame();

			Assert::IsTrue(game.HitTest(0, 0) == game.GetGru());
		}

	};
}