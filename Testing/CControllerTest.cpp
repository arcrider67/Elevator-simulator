#include "pch.h"
#include "CppUnitTest.h"
#include "Controller.h"
#include "Floor.h"
#include "ElevatorWnd.h"
#include "ElevatorController.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CControllerTest)
	{
	public:

		/**
		* Handy test to ensure the process for a floor works correctly
		*
		* This delays long enough for the elevator to go one floor, then
		* tests to ensure the door is closed, opens, then closes again.
		*/
		void TestToFloor(CElevatorWnd * elevator, int floor)
		{
			elevator->Update(4.3);

			// Should not be open, yet
			Assert::IsFalse(elevator->IsDoorOpen(floor));
			elevator->Update(1);

			// Should be open, now
			Assert::IsTrue(elevator->IsDoorOpen(floor));
			elevator->Update(3);

			// Should be closed, again
			Assert::IsTrue(elevator->IsDoorClosed(floor));
		}

		
		TEST_METHOD(TestCControllerSetController)
		{
			// Create a test object
			CElevatorWnd elevator;

			// Create a mock controller and install it
			auto controller = std::make_shared<CController>();

			elevator.SetController(controller);
			Assert::IsTrue(controller->GetElevator() == &elevator);
		}	

		TEST_METHOD(TestCControllerDoorMachine)
		{
			// Create a test object
			CElevatorWnd elevator;

			// Create a mock controller and install it
			auto controller = std::make_shared<CController>();

			elevator.SetController(controller);
			Assert::IsTrue(controller->GetElevator() == &elevator);

			int floor = 1;

			// Do the door sequence twice
			for (int i = 0; i < 2; i++)
			{
				// Door should be initially closed
				Assert::IsTrue(elevator.IsDoorClosed(floor));

				// Press open 
				elevator.PressOpen();

				// It takes about 1 second for the door to open, so 
				// run the elevator for a bit more than that
				elevator.Update(1.1);

				Assert::IsTrue(elevator.IsDoorOpen(floor));

				// Press close
				elevator.PressClose();

				// It takes about 1 second for the door to close, so 
				// run the elevator for a bit more than that
				elevator.Update(1.1);

				Assert::IsTrue(elevator.IsDoorClosed(floor));
			}
		}

		TEST_METHOD(TestCControllerDoorMachine2) {
			// Create a test object
			CElevatorWnd elevator;

			// Create a mock controller and install it
			auto controller = std::make_shared<CController>();

			elevator.SetController(controller);
			Assert::IsTrue(controller->GetElevator() == &elevator);

			int floor = 1;

			elevator.PressOpen();
			elevator.Update(1.1);

			Assert::IsTrue(elevator.IsDoorOpen(floor));

			elevator.Update(3);

			Assert::IsTrue(elevator.IsDoorClosed(floor));
		}

		/*
		* Test the elevator in the up direction, only.
		* This tests the up buttons except the third floor
		*/
		TEST_METHOD(TestCControllerGoingUp)
		{
			// Create a test object
			CElevatorWnd elevator;

			// Create a mock controller and install it
			auto controller = std::make_shared<CController>();

			elevator.SetController(controller);
			Assert::IsTrue(controller->GetElevator() == &elevator);

			// Press the up botton the first floor
			elevator.PressCallUp(1);
			elevator.Update(1.1);

			// Should be open, now
			Assert::IsTrue(elevator.IsDoorOpen(1));
			elevator.Update(3);

			// Should be closed, again
			Assert::IsTrue(elevator.IsDoorClosed(1));

			// Press the up botton on the second floor
			elevator.PressCallUp(2);

			// It takes 3.3 seconds to go one floor up
			// 1 second delay before we open the door
			// 1 second to open the door
			elevator.Update(4.4);

			// Should not be open, yet
			Assert::IsFalse(elevator.IsDoorOpen(2));
			elevator.Update(1);

			// Should be open, now
			Assert::IsTrue(elevator.IsDoorOpen(2));
			elevator.Update(3);

			// Should be closed, again
			Assert::IsTrue(elevator.IsDoorClosed(2));

			// Press the down botton the third floor
			elevator.PressCallDown(3);

			elevator.Update(4.4);

			// Should not be open, yet
			Assert::IsFalse(elevator.IsDoorOpen(3));
			elevator.Update(1);

			// Should be open, now
			Assert::IsTrue(elevator.IsDoorOpen(3));
			elevator.Update(3);

			// Should be closed, again
			Assert::IsTrue(elevator.IsDoorClosed(3));
		}

		/*
* Test the elevator in the up direction, only.
* This tests the buttons on the elevator panel
*/
		TEST_METHOD(TestCControllerGoingUpPanel)
		{
			// Create a test object
			CElevatorWnd elevator;

			// Create a mock controller and install it
			auto controller = std::make_shared<CController>();

			elevator.SetController(controller);
			Assert::IsTrue(controller->GetElevator() == &elevator);

			// Press the up botton the first floor
			elevator.PressCallUp(1);
			elevator.Update(1.1);

			// Should be open, now
			Assert::IsTrue(elevator.IsDoorOpen(1));
			elevator.Update(3);

			// Should be closed, again
			Assert::IsTrue(elevator.IsDoorClosed(1));

			// Select the second and third floor panel buttons
			elevator.PressPanelFloor(2);
			elevator.PressPanelFloor(3);

			// Test that we go to the second floor correctly
			TestToFloor(&elevator, 2);

			// Test that we go to the third floor correctly
			TestToFloor(&elevator, 3);
		}

		/*
	 * Test the elevator both directions
	 */
		TEST_METHOD(TestCControllerBothDirections)
		{
			// Create a test object
			CElevatorWnd elevator;

			// Create a mock controller and install it
			auto controller = std::make_shared<CController>();

			elevator.SetController(controller);
			Assert::IsTrue(controller->GetElevator() == &elevator);

			// Press the down button on the second floor
			elevator.PressCallDown(2);

			// Test that we go to the second floor correctly 
			TestToFloor(&elevator, 2);

			// Press the panel button for the first floor
			elevator.PressPanelFloor(1);

			// Test that we go to the first floor correctly 
			TestToFloor(&elevator, 1); ///fails here

			// Ensure we clear any cumulative timing errors
			elevator.Update(1);

			// Press several buttons
			elevator.PressCallUp(2);
			elevator.PressCallDown(2);
			elevator.PressCallDown(3);

			// Test that we go to the second floor correctly 
			TestToFloor(&elevator, 2);

			elevator.PressPanelFloor(1);

			// Test that we go to the third floor correctly 
			TestToFloor(&elevator, 3);

			// Test that we go to the second floor correctly 
			TestToFloor(&elevator, 2);

			// Test that we go to the first floor correctly 
			TestToFloor(&elevator, 1);

			elevator.PressPanelFloor(3);

			elevator.Update(3.3);

			// Test that we go to the third floor correctly 
			TestToFloor(&elevator, 3);

			elevator.PressPanelFloor(1);

			// Test that we go to the first floor correctly 
			elevator.Update(3.3);
			TestToFloor(&elevator, 1);
		}

	};
}