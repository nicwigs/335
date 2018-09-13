#include "stdafx.h"
#include "CppUnitTest.h"
#include "WorkshopWnd.h"
#include "Controller.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CControllerTest)
	{
	public:
        /**
         * Initialization so image loading will work
         */
        TEST_METHOD_INITIALIZE(methodName)
        {
            extern wchar_t g_dir[];
            ::SetCurrentDirectory(g_dir);
        }

		//
		// Notice: It is expected that all tests other than TestCControllerSetController
		// will fail until you complete the state machine.
		//

        /**
         * Test that we can simply set a controller
         */
        TEST_METHOD(TestCControllerSetController)
        {
            // Create a test object
            CWorkshopWnd workshop;
            workshop.Load();

            // Create a mock controller and install it
            auto controller = std::make_shared<CController>();

            workshop.SetController(controller);
            Assert::IsTrue(controller->GetWorkshop() == &workshop);
        }

        /**
         * This tests that you can press Advance and get a Minion
         * loaded onto the conveyer belt and to the shower station. 
		 * This should be the first test you try to pass.
         */
        TEST_METHOD(TestCControllerMinionToShower)
        {
            // Create a test object
            CWorkshopWnd workshop;
            workshop.Load();

            // Create a controller and install it
            auto controller = std::make_shared<CController>();
            workshop.SetController(controller);

			// Initially there is no Minion
			Assert::IsTrue(workshop.GetMinion() == nullptr);

			// Ensure Next Minion button is enabled
			Assert::IsTrue(workshop.GetButtonNext()->IsEnabled());

			// Ensure Advance button is not enabled
			Assert::IsFalse(workshop.GetButtonAdvance()->IsEnabled());

            // Press the Next Minion button
            controller->OnNextPressed();

            // It takes one second for the minion to move in and stop.
            // Run the workshop for a bit more than that.
            workshop.Update(1.1);

            // Is the Minion created and in place at the shower station (1)?
			Assert::IsTrue(workshop.GetMinion() != nullptr);
            Assert::AreEqual(1, controller->GetMinionPosition(), 0.01);
			Assert::IsFalse(workshop.IsShower());
        } 


		/**
		 * This tests the entire process of a Minion moving through 
		 * the shower, wardrobe, and inspection.
		 */
		TEST_METHOD(TestCControllerEntireProcess)
		{
			// Create a test object
			CWorkshopWnd workshop;
			workshop.Load();

			// Create a controller and install it
			auto controller = std::make_shared<CController>();
			workshop.SetController(controller);

			// This test is repeated twice for 1 and 2 eyes.
			// This is important, since it ensures the system
			// returns to the correct initial state after one
			// complete cycle.
			for (int eyes = 1; eyes <= 2; eyes++)
			{
				// Ensure created Minion have the specified number of eyes
				workshop.ForceEyes(eyes);

				// Initially there is no Minion
				Assert::IsTrue(workshop.GetMinion() == nullptr);

				//
				// Correct button states
				//
				Assert::IsTrue(workshop.GetButtonNext()->IsEnabled());
				Assert::IsFalse(workshop.GetButtonAdvance()->IsEnabled());
				Assert::IsFalse(workshop.GetButtonShower()->IsEnabled());

				//
				// Advance to the Shower station (1)
				//

				// Press the Next Minion button
				controller->OnNextPressed();

				// It takes one second for the minion to move in and stop.
				// Run the workshop for a bit more than that.
				workshop.Update(1.1);

				//
				// Correct button states
				//
				Assert::IsFalse(workshop.GetButtonNext()->IsEnabled());
				Assert::IsTrue(workshop.GetButtonAdvance()->IsEnabled());
				Assert::IsTrue(workshop.GetButtonShower()->IsEnabled());

				// Is the Minion created and in place at the shower station (1)?
				Assert::IsTrue(workshop.GetMinion() != nullptr);
				Assert::AreEqual(1, controller->GetMinionPosition(), 0.01);
				Assert::IsFalse(workshop.IsShower());

				// Press the Shower button
				controller->OnShowerPressed();
				Assert::IsTrue(workshop.IsShower());

				// Shower should run for 1 second
				workshop.Update(0.9);
				Assert::IsTrue(workshop.IsShower());
				workshop.Update(0.2);
				Assert::IsFalse(workshop.IsShower());

				//
				// Correct button states
				//
				Assert::IsFalse(workshop.GetButtonNext()->IsEnabled());
				Assert::IsTrue(workshop.GetButtonAdvance()->IsEnabled());

				// Shower button should still be enabled
				Assert::IsTrue(workshop.GetButtonShower()->IsEnabled());

				//
				// Advance to the Wardrobe station (2)
				//
				controller->OnAdvancePressed();

				Assert::IsFalse(workshop.GetButtonNext()->IsEnabled());
				Assert::IsTrue(workshop.GetButtonAdvance()->IsEnabled());

				// Shower button should now be disabled
				Assert::IsFalse(workshop.GetButtonShower()->IsEnabled());

				// It takes 1 second to get to the Wardrobe station
				workshop.Update(1.1);
				Assert::AreEqual(2, controller->GetMinionPosition(), 0.01);

				//
				// Correct button states
				//
				Assert::IsFalse(workshop.GetButtonNext()->IsEnabled());
				Assert::IsTrue(workshop.GetButtonAdvance()->IsEnabled());
				Assert::IsFalse(workshop.GetButtonShower()->IsEnabled());
				Assert::IsTrue(workshop.GetButtonWardrobe()->IsEnabled());

				// Select Goggles
				if (eyes == 1) 
				{
					controller->OnWardrobePressed(CWorkshopController::Goggles1);
				} 
				else 
				{
					controller->OnWardrobePressed(CWorkshopController::Goggles2);
				}

				
				workshop.Update(1.1);
				Assert::IsTrue(workshop.GetButtonWardrobe()->IsEnabled());

				// Select Pants
				controller->OnWardrobePressed(CWorkshopController::BlueJeans);
				workshop.Update(1.1);
				Assert::IsTrue(workshop.GetButtonWardrobe()->IsEnabled());

				// Ensure Minion is dressed properly
				Assert::IsFalse(workshop.GetMinion()->WardrobeMalfunction());

				//
				// Advance to inspection station (4)
				//
				controller->OnAdvancePressed();
				Assert::IsFalse(workshop.GetButtonWardrobe()->IsEnabled());

				workshop.Update(2.1);
				Assert::AreEqual(4, controller->GetMinionPosition(), 0.01);

				//
				// Correct button states
				//
				Assert::IsFalse(workshop.GetButtonNext()->IsEnabled());
				Assert::IsFalse(workshop.GetButtonAdvance()->IsEnabled());
				Assert::IsFalse(workshop.GetButtonShower()->IsEnabled());
				Assert::IsTrue(workshop.GetButtonInspect()->IsEnabled());

				// Press Inspect
				controller->OnInspectPressed();
				Assert::IsTrue(workshop.GetButtonInspect()->IsEnabled());

				// Should not have passed, yet!
				Assert::IsFalse(workshop.GetMinion()->HasPassed());

				// After one second it has passed, but should not be moving, yet
				workshop.Update(1.1);
				Assert::IsTrue(workshop.GetMinion()->HasPassed());
				Assert::IsFalse(workshop.GetButtonInspect()->IsEnabled());
				Assert::AreEqual(4, controller->GetMinionPosition(), 0.01);

				// One second after passed indicated, we should be moving
				workshop.Update(1.0);

				// Should have moved to here by now
				Assert::AreEqual(4.1, controller->GetMinionPosition(), 0.01);

				//
				// Time to finish up and return to Idle
				//
				workshop.Update(1.0);

				//
				// Correct button states
				//
				Assert::IsTrue(workshop.GetButtonNext()->IsEnabled());
				Assert::IsFalse(workshop.GetButtonAdvance()->IsEnabled());
				Assert::IsFalse(workshop.GetButtonShower()->IsEnabled());

				// The workshop deletes the Minion if it goes off the
				// right side of the screen (position >= 5.0), so it
				// should have been destroyed.
				Assert::IsTrue(workshop.GetMinion() == nullptr);
			}
		}

		/**
		* This tests the entire process where a Minion has a wardrobe 
		* malfunction. The malfunctions given depend on the pass:
		*
		* pass 1: Wrong number of eyes in the goggles.
		* pass 2: No clothes at all
		* pass 3: Too many clothes
		*/
		TEST_METHOD(TestCControllerWardrobeMalfunction)
		{
			// Create a test object
			CWorkshopWnd workshop;
			workshop.Load();

			// Create a controller and install it
			auto controller = std::make_shared<CController>();
			workshop.SetController(controller);

			// Only 1-eye minions will be created in this test.
			workshop.ForceEyes(1);

			// Each test pass is a little different
			for (int pass = 1; pass <= 3; pass++)
			{
				//
				// Advance to the Shower station (1)
				//

				// Press the Next Minion button and let it
				// get to the shower station
				controller->OnNextPressed();
				workshop.Update(1.1);

				// Press the Shower button and complete the shower sequence
				controller->OnShowerPressed();
				workshop.Update(1.1);

				//
				// Advance to the Wardrobe station (2)
				//
				controller->OnAdvancePressed();

				// It takes 1 second to get to the Wardrobe station
				workshop.Update(1.1);
				Assert::AreEqual(2, controller->GetMinionPosition(), 0.01);

				//
				// Correct button states
				//
				Assert::IsFalse(workshop.GetButtonNext()->IsEnabled());
				Assert::IsTrue(workshop.GetButtonAdvance()->IsEnabled());
				Assert::IsFalse(workshop.GetButtonShower()->IsEnabled());
				Assert::IsTrue(workshop.GetButtonWardrobe()->IsEnabled());

				int numClothingItems = 0;

				switch (pass)
				{
				case 1:
					// Wrong goggles
					controller->OnWardrobePressed(CWorkshopController::Goggles2);
					workshop.Update(1.1);
					controller->OnWardrobePressed(CWorkshopController::BlueJeans);
					workshop.Update(1.1);
					numClothingItems = 2;
					break;

				case 2:
					// No clothes at all
					break;

				case 3:
					// Too many clothes
					controller->OnWardrobePressed(CWorkshopController::Goggles1);
					workshop.Update(1.1);
					controller->OnWardrobePressed(CWorkshopController::BlueJeans);
					workshop.Update(1.1);
					controller->OnWardrobePressed(CWorkshopController::Goggles1);
					workshop.Update(1.1);
					controller->OnWardrobePressed(CWorkshopController::GreenJeans);
					workshop.Update(1.1);
					numClothingItems = 4;
				}

				// Ensure Minion is dressed improperly
				Assert::IsTrue(workshop.GetMinion()->WardrobeMalfunction());

				//
				// Advance to inspection station (4)
				//
				controller->OnAdvancePressed();
				Assert::IsFalse(workshop.GetButtonWardrobe()->IsEnabled());
				workshop.Update(2.1);
				Assert::AreEqual(4, controller->GetMinionPosition(), 0.01);

				// Press Inspect
				controller->OnInspectPressed();

				// This starts a sequence of events that each
				// require this much time:
				// Inspection: 1 second
				// Moving back to Wardrobe station: 2 seconds
				workshop.Update(3.1);

				//
				// We should now be at the wardrobe station again (2)
				//
				Assert::IsTrue(workshop.GetButtonWardrobe()->IsEnabled());
				Assert::AreEqual(2, controller->GetMinionPosition(), 0.01);

				// Removing all clothing items: numClothingItems seconds
				for (int i = 0; i < numClothingItems; i++)
				{
					// The clothes stripping process should be active right now
					Assert::IsTrue(workshop.IsStripping());
					workshop.Update(1.0);
				}
				
				// Now we should have no clothes on at all and stripping is done
				Assert::IsFalse(workshop.IsStripping());
				Assert::IsFalse(workshop.GetMinion()->AnyClothes());

				// Do it correctly, now
				controller->OnWardrobePressed(CWorkshopController::Goggles1);
				workshop.Update(1.1);
				controller->OnWardrobePressed(CWorkshopController::BlueJeans);
				workshop.Update(1.1);

				//
				// Advance to inspection station (4)
				//
				controller->OnAdvancePressed();
				Assert::IsFalse(workshop.GetButtonWardrobe()->IsEnabled());
				workshop.Update(2.1);
				Assert::AreEqual(4, controller->GetMinionPosition(), 0.01);

				// Press Inspect
				controller->OnInspectPressed();

				// After one second it has passed, but should not be moving, yet
				workshop.Update(1.1);
				Assert::IsTrue(workshop.GetMinion()->HasPassed());
				Assert::AreEqual(4, controller->GetMinionPosition(), 0.01);

				// One second after passed indicated, we should be moving
				workshop.Update(1.0);

				// Should have moved to here by now
				Assert::AreEqual(4.1, controller->GetMinionPosition(), 0.01);

				// Time to finish up and return to Idle
				workshop.Update(1.0);
			}
		}

		/**
		* This tests the entire process where a Minion skips the 
		* shower!
		*/
		TEST_METHOD(TestCControllerDirtyMinion)
		{
			// Create a test object
			CWorkshopWnd workshop;
			workshop.Load();

			// Create a controller and install it
			auto controller = std::make_shared<CController>();
			workshop.SetController(controller);

			// Only 2-eye minions will be created in this test.
			workshop.ForceEyes(2);

			// This does two passes to ensure we can complete
			// the entire sequence correctly.
			for (int pass = 1; pass <= 2; pass++)
			{
				//
				// Advance to the Shower station (1)
				//

				// Press the Next Minion button and let it
				// get to the shower station
				controller->OnNextPressed();
				workshop.Update(1.1);

				//
				// Advance to the Wardrobe station (2)
				//
				controller->OnAdvancePressed();

				// It takes 1 second to get to the Wardrobe station
				workshop.Update(1.1);
				Assert::AreEqual(2, controller->GetMinionPosition(), 0.01);
				Assert::IsTrue(workshop.GetButtonWardrobe()->IsEnabled());

				// Cloth the guy!
				controller->OnWardrobePressed(CWorkshopController::Goggles2);
				workshop.Update(1.1);
				controller->OnWardrobePressed(CWorkshopController::BlueJeans);
				workshop.Update(1.1);

				// Ensure Minion is dressed properly
				Assert::IsFalse(workshop.GetMinion()->WardrobeMalfunction());

				//
				// Advance to inspection station (4)
				//
				controller->OnAdvancePressed();
				Assert::IsFalse(workshop.GetButtonWardrobe()->IsEnabled());
				workshop.Update(2.1);
				Assert::AreEqual(4, controller->GetMinionPosition(), 0.01);

				// Press Inspect
				controller->OnInspectPressed();

				// This starts a sequence of events that each
				// require this much time:
				// Inspection: 1 second
				// Moving back to Wardrobe station: 2 seconds
				workshop.Update(3.1);

				//
				// We should now be at the wardrobe station again (2)
				//
				Assert::IsTrue(workshop.GetButtonWardrobe()->IsEnabled());
				Assert::AreEqual(2, controller->GetMinionPosition(), 0.01);

				//
				// Removing the clothing items
				//

				// The clothes stripping process should be active right now
				Assert::IsTrue(workshop.IsStripping());
				workshop.Update(1.0);

				// The clothes stripping process should be active right now
				Assert::IsTrue(workshop.IsStripping());
				workshop.Update(1.0);

				// Now we should have no clothes on at all and stripping is done
				Assert::IsFalse(workshop.IsStripping());
				Assert::IsFalse(workshop.GetMinion()->AnyClothes());
				
				//
				// One second to move back to the Shower station (1)
				//
				workshop.Update(1.0);

				// We should now be at the shower station again 
				Assert::IsFalse(workshop.GetButtonWardrobe()->IsEnabled());
				Assert::IsTrue(workshop.GetButtonShower()->IsEnabled());
				Assert::AreEqual(1, controller->GetMinionPosition(), 0.01);

				// 
				// Do it correctly, now
				//

				// Press the Shower button and complete the shower sequence
				controller->OnShowerPressed();
				workshop.Update(1.1);

				// Advance to the Wardrobe station (2)
				controller->OnAdvancePressed();
				workshop.Update(1.1);

				Assert::AreEqual(2, controller->GetMinionPosition(), 0.01);
				controller->OnWardrobePressed(CWorkshopController::Goggles2);
				workshop.Update(1.1);
				controller->OnWardrobePressed(CWorkshopController::BlueJeans);
				workshop.Update(1.1);

				//
				// Advance to inspection station (4)
				//
				controller->OnAdvancePressed();
				workshop.Update(2.1);
				Assert::AreEqual(4, controller->GetMinionPosition(), 0.01);

				// Press Inspect
				controller->OnInspectPressed();

				// After one second it has passed, but should not be moving, yet
				workshop.Update(1.1);
				Assert::IsTrue(workshop.GetMinion()->HasPassed());
				Assert::AreEqual(4, controller->GetMinionPosition(), 0.01);

				// One second after passed indicated, we should be moving
				workshop.Update(1.0);

				// Should have moved to here by now
				Assert::AreEqual(4.1, controller->GetMinionPosition(), 0.01);

				// Time to finish up and return to Idle
				workshop.Update(1.0);
			}
		}

	};
}