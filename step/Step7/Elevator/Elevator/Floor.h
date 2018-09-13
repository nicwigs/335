/**
 * \file Floor.h
 *
 * \author Nic Wiggins
 *
 * Class that describes the floor of the building
 */

#pragma once

class CController;
/**
 * Class that describes a floor in a building
 */
class CFloor
{
public:
	CFloor();
	virtual ~CFloor();

	void SetUp(bool up);
	void SetDown(bool down);
	void SetPanel(bool panel);
	void SetFloor(int floor);
	void SetController(CController * controller);

	bool IsUp();
	bool IsDown();
	bool IsPanel();
	int GetFloor();

private:
	bool mUp = false; ///< is up
	bool mDown = false; ///< is down
	bool mPanel = false; ///< panel on floor
	int mFloor = 0; ///< what floor is this
	CController *mController = nullptr;   ///< Controller for this object

};

