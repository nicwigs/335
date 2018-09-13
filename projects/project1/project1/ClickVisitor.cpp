/**
 * \file ClickVisitor.cpp
 *
 * \author Ian Guswiler
 */

#include "stdafx.h"
#include "ClickVisitor.h"
#include "NewButton.h"
#include "Gru.h"


/**
 * Constructor
 */
CClickVisitor::CClickVisitor()
{
}


/**
 * Destructor
 */
CClickVisitor::~CClickVisitor()
{
}

/**
* Click handler for CButtonNew object
* \param button Pointer to new button object that is being visited
*/
void CClickVisitor::VisitButton(CNewButton * button)
{
	button->OnClick();
}

/**
 * Click handler for CGru object
 * \param gru Pointer to gru object that is being visited
 */
void CClickVisitor::VisitGru(CGru * gru)
{
	mGruClicked = true;
}
