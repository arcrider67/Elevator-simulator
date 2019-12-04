#pragma once
#include "ElevatorController.h"
#include "Floor.h"

class CController : public CElevatorController
{
public:

	/// The state machine states
	enum States { Idle, DoorOpening, DoorOpen, DoorClosing, Moving, Stop };

	CController();


	void SetState(States state);
	


	void Service();

	virtual void OnOpenPressed() override;
	
	virtual void OnClosePressed() override;

	virtual void OnPanelFloorPressed(int floor) override;

	virtual void OnCallUpPressed(int floor) override;

	virtual void OnCallDownPressed(int floor) override;

	int WhatFloorToGoTo();

	int WhatFloorUp();

	int WhatFloorDown();

private:
	
	int    mFloor = 1;      ///< The current floor
	States mState = Idle;   ///< The current state

	double mStateTime = 0;  ///< The time in a current state

	bool mGoingUp = true; ///< The current direction of the elevator

	/// An object for each floor
	CFloor mFloors[NumFloors];
};




