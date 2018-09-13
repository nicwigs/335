/**
 * \file CGameItemTest.cpp
 *
 * \author Mark Elinski
 */

#include "stdafx.h"
#include "CppUnitTest.h"

#include "GameItem.h"
#include "Game.h"
#include "Vector.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/// Juicer filename 
const std::wstring JuicerImageName(L"images/juicer.png");

namespace Testing
{
	/** Mock class for testing CGameItem */
	class CItemMock : public CGameItem
	{
	public:
		/** Constructor
		* \param game The game this is a member of */
		CItemMock(CGame *game) : CGameItem(game, JuicerImageName, 0, 0) {}

		/** Draw the item
		* \param graphics The graphics context to draw on */
		virtual void Draw(Gdiplus::Graphics *graphics) {}

		virtual void Accept(CItemVisitor *visitor) override {}
	};

	/**
	* Class for testing CGameItem
	*/
	TEST_CLASS(CGameItemTest)
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
		TEST_METHOD(TestCGameItemConstruct)
		{
			CGame game;
			CItemMock item(&game);
		}

		/**
		* Test the CGameItem getters and setters
		*/
		TEST_METHOD(TestCGameItemGettersSetters)
		{
			// Construct an item to test
			CGame game;
			CItemMock item(&game);

			// Test initial values
			Assert::AreEqual(0, item.GetX(), 0);
			Assert::AreEqual(0, item.GetY(), 0);

			// Test SetLocation, GetX, and GetY
			item.SetLocation(10.5, 17.2);
			Assert::AreEqual(10.5, item.GetX(), 0.0001);
			Assert::AreEqual(17.2, item.GetY(), 0.0001);

			// Test a second with with different values
			item.SetLocation(-72, -107);
			Assert::AreEqual(-72, item.GetX(), 0.0001);
			Assert::AreEqual(-107, item.GetY(), 0.0001);
		}

		/**
		* Test the CGameItem HitTest method
		*/
		TEST_METHOD(TestCGameItemHitTest)
		{
			// Create an item to test
			CGame game;
			CItemMock item(&game);

			// Give it a location
			// Always make the numbers different, in case they are mixed up
			item.SetLocation(100, 200);

			// Center of the item should be a true
			Assert::IsTrue(item.HitTest(100, 200));

			// Left of the item
			Assert::IsFalse(item.HitTest(10, 200));

			// Right of the item
			Assert::IsFalse(item.HitTest(200, 200));

			// Above the item
			Assert::IsFalse(item.HitTest(100, 0));

			// Below the item
			Assert::IsFalse(item.HitTest(100, 300));

			// Of item transparent pixel
			Assert::IsFalse(item.HitTest(100 - 125 / 2 + 17, 200 - 117 / 2 + 16));
		}
		/**
		* Test the CGameItem get position in vector form
		*/
		TEST_METHOD(TestCGameItemGetP)
		{
			// Construct an item to test
			CGame game;
			CItemMock item(&game);

			// Test initial values			
			Assert::AreEqual(0, item.GetP().X(), 0);
			Assert::AreEqual(0, item.GetP().Y(), 0);

			// Test getP
			item.SetLocation(10.5, 17.2);
			Assert::AreEqual(10.5, item.GetP().X(), 0.0001);
			Assert::AreEqual(17.2, item.GetP().Y(), 0.0001);

			// Test a second with with different values
			item.SetLocation(-72, -107);
			Assert::AreEqual(-72, item.GetP().X(), 0.0001);
			Assert::AreEqual(-107, item.GetP().Y(), 0.0001);
		}
	};
}