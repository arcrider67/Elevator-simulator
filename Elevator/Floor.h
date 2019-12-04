#pragma once

class CController;


class CFloor
{
public:

	void SetController(CController* controller) { mController = controller; }


	void SetFloor(int floor) { mFloor = floor; }
	void SetUp(bool state);
	void SetPanel(bool p);
	void SetDown(bool s);

private:
	CController* mController = nullptr;   ///< Controller for this object

	bool mUp = false;
	bool mDown = false;
	bool mPanel = false;
	int mFloor = 0;

};
