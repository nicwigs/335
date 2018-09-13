/**
 * \file ClickVisitor.h
 *
 * \author Ian Guswiler
 *
 * Describes the click visitor class
 */

#pragma once
#include "ItemVisitor.h"


/**
 * Class to handle clicks on different game items
 */
class CClickVisitor :
	public CItemVisitor
{
public:
	CClickVisitor();
	virtual ~CClickVisitor();

	void VisitButton(CNewButton *button) override;
	void VisitGru(CGru *gru) override;

	/**
	* Sees if Gru was clicked
	* \return true if he was clicked
	*/
	bool GruClicked() { return mGruClicked; };

private:
	/// True if gru was the object visited
	bool mGruClicked = false;
};

