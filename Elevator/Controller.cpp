#include "pch.h"
#include "Controller.h"





/// The time the door remains open
const double DoorOpenTime = 2.0;

/**
 * Constructor
 */
CController::CController()
{
	for (int f = 1; f <= NumFloors; f++)
	{
		mFloors[f - 1].SetController(this);
		mFloors[f - 1].SetFloor(f);
	}
}


/** This function is called when the open button is pressed.
 */
void CController::OnOpenPressed()
{
	switch (mState)
	{
	case Idle:
		// Transition to the DoorOpening state
		SetState(DoorOpening);
		break;

	case DoorOpen:
		SetState(DoorOpen);
		break;

	case DoorClosing:
		SetState(DoorOpening);
		break;

	default:
		break;
	}
}

/** Set a state
 * \param state The new state to set
 */
void CController::SetState(States state)
{
	mState = state;
	mStateTime = 0;

	// Entry activities for states
	switch (mState)
	{
	case DoorOpening:
		SetDoorMotor(mFloor, 1);
		break;

	case DoorOpen:
		SetDoorMotor(mFloor, 0);
		break;

	case DoorClosing:
		SetDoorMotor(mFloor, -1);
		break;

	default:
		break;
	}
}

/** Elevator service function
 *
 * This function is called once every 0.001 seconds and
 * allows us to control elevator functionality.
 */
void CController::Service()
{

	// Increment state time by 1 millisecond
	mStateTime += 0.001;


	switch (mState)
	{
	case DoorOpening:
		if (IsDoorOpen(mFloor))
		{
			SetState(DoorOpen);
		}
		break;

	case DoorClosing:
		if (IsDoorClosed(mFloor)) 
		{
			SetState(Idle);
		}

	case DoorOpen:
		if (mStateTime >= DoorOpenTime)
		{
			SetState(DoorClosing);
		}
		break;

	default:
		break;
	}
}

/** This function is called when the door close button is pressed.
 */
void CController::OnClosePressed()
{
	switch (mState)

	{
	case DoorOpen:
		SetState(DoorClosing);
		break;

	case DoorOpening:
		SetState(DoorClosing);
		break;

	default:
		break;
	}
}

void CController::OnPanelFloorPressed(int floor)
{
}

/** This function is called when the up button is pressed
 * on a floor.
 * \param floor The floor we are called to 1-3
 */
void CController::OnCallUpPressed(int floor)
{
	mFloors[floor - 1].SetUp(true);
}

void CController::OnCallDownPressed(int floor)
{
}

int CController::WhatFloorToGoTo()
{
	return 0;
}

int CController::WhatFloorUp()
{
	return 0;
}

int CController::WhatFloorDown()
{
	return 0;
}
