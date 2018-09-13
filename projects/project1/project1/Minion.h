/**
* \file Villain.h
*
* \author Jack Turak
*
* Class to represent a Minion
*/

#pragma once
#include "GameItem.h"

/**
* The Minion superclass that all other minions will be derived from.
*/
class CMinion : public CGameItem
{
public:

	/// Default constructor (deleted)
	CMinion() = delete;

	/// Copy constructor (disabled)
	CMinion(const CMinion &) = delete;

	virtual ~CMinion();
		
	/// New constructor
	CMinion(CGame *game, const std::wstring &filename, double xPos, double yPos);

	void UpdatePos(double elapsed);

	virtual void Update(double elapsed) override;

	void Flock();

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitMinion(this); }

	/**
	* Getter for the scoreboard object
	* \return int
	*/
	virtual int GetPoints() = 0;

	/** The X,Y velocity of the item in a vector
	* \returns mV velocity vector in pixels/second */
	CVector GetV() const { return mV; }

protected:
	///Item velocity in playing area in pixels/sec.
	CVector mV;  ///<Velocity 

};
