/**
 * \file ItemVisitor.h
 *
 * \author Ian Guswiler
 * \author Nic Wiggins
 *
 * Describes a visitor class for CGameItems
 */

#pragma once

// Forward references
class CNewButton;
class CGru;
class CMinion;
class CVillain;


/**
 * Visitor class for CGameItems
 */
class CItemVisitor
{
public:
	CItemVisitor();
	virtual ~CItemVisitor();

	/**
	* Visit handler for CButtonNew object
	* \param button Pointer to new button object that is being visited
	*/
	virtual void VisitButton(CNewButton *button) {}

	/**
	* Visit handler for CVillain object
	* \param villain Pointer to villain object that is being visited
	*/
	virtual void VisitVillain(CVillain *villain) {}

	/**
	* Visit handler for CMinion object
	* \param minion Pointer to minion object that is being visited
	*/
	virtual void VisitMinion(CMinion *minion) {}

	/**
	* Visit handler for CGru object
	* \param gru Pointer to gru object that is being visited
	*/
	virtual void VisitGru(CGru *gru) {}
};

