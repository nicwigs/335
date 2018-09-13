/**
 * \file NewButton.h
 *
 * \author Ian Guswiler
 *
 * Desctribes the new button class
 */

#pragma once
#include "GameItem.h"

/**
 * Class representing a new game button
 */
class CNewButton :
	public CGameItem
{
public:
	/// Default constructor disabled
	CNewButton() = delete;

	/// Copy constructor disabled
	CNewButton(const CNewButton &) = delete;

	CNewButton(CGame *game);


	virtual ~CNewButton();

	void OnClick();

	void Update(double elapsed);

	/** Accepts our visitor.
	* \param visitor Visitor we are accepting.
	*/
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitButton(this); }
};

