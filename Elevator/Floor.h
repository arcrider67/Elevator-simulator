#pragma once

class CController;

/**Class to define a floor visitable by the elevator*/
class CFloor
{
public:

	/**assigns the floor to a controller
	\param controller
	*/
	void SetController(CController* controller) { mController = controller; }

	/**sets the current floor
	\param floor the floor level this object is at
	*/
	void SetFloor(int floor) { mFloor = floor; }
	

	void SetUp(bool state);
	void SetPanel(bool p);
	void SetDown(bool s);

	/** returns if panel has been pressed
	\return bool mPanel
	*/
	bool IsPanel() { return mPanel; };
	
	/** returns if up has been pressed
	\return bool mUp
	*/
	bool IsUp() { return mUp; }

	/** returns if down has been pressed
	\return bool mDown
	*/
	bool IsDown() { return mDown; }


private:
	CController* mController = nullptr;   ///< Controller for this object

	///the current state of up on this floor
	bool mUp = false;

	///current state of down on this floor
	bool mDown = false;

	///current state of this floor on the panel
	bool mPanel = false;

	///this floor's floor number
	int mFloor = 0;

};

