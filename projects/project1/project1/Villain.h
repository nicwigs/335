/**
 * \file Villain.h
 *
 * \author Zoinul Choudhury
 *
 * Class to represent a villain
 */

#pragma once
#include "GameItem.h"

/**
 * The Villain superclass that all other villains will be derived from.
 */
class CVillain : public CGameItem
{
public:
	/// Default constructor (deleted)
	CVillain() = delete;

	/// Copy constructor (disabled)
	CVillain(const CVillain &) = delete;

	virtual ~CVillain();

	/// New constructor
	CVillain(CGame *game, const std::wstring &filename, double xPos, double yPos);

	/** Accept handler for visitors
	* \param visitor Pointer to the visiter being accepted by this class
	*/
	void Accept(CItemVisitor *visitor) override { visitor->VisitVillain(this); };


	/** Increments the accumulated points of a villain
	*	\param points The number of points that are to be added to a villains total points
	*/
	virtual void AddPoints(int points);
};

