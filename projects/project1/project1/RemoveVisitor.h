/**
 * \file RemoveVisitor.h
 *
 * \author Ian Guswiler
 *
 * Describes the remove visitor class
 */

#pragma once
#include "ItemVisitor.h"


/**
 * Visitor class that handles items about to be removed
 */
class CRemoveVisitor :
	public CItemVisitor
{
public:
	CRemoveVisitor();
	virtual ~CRemoveVisitor();

	void VisitMinion(CMinion *minion) override;

	void VisitGru(CGru *gru) override;

	/**
	* Gets the point value of the item removed
	* \return Returns integer number of points
	*/
	int GetPoints() { return mPointsRemoved; }

	/**
	* Checks if gru was visited
	* \return True if gru was visited
	*/
	bool GruVisited() { return mGruVisited; }

private:
	/// Number of points the removed item had
	int mPointsRemoved = 0;

	/// Boolean that returns whether Gru has been visited or not
	bool mGruVisited = false;
};

