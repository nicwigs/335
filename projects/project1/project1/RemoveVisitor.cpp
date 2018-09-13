/**
 * \file RemoveVisitor.cpp
 *
 * \author Ian Guswiler
 */

#include "stdafx.h"
#include "RemoveVisitor.h"
#include "Minion.h"
#include "Gru.h"
#include "Game.h"

using namespace std;

/**
 * Constructor
 */
CRemoveVisitor::CRemoveVisitor()
{
}


/**
 * Destructor
 */
CRemoveVisitor::~CRemoveVisitor()
{
}

/**
 * Remove visit handler for minion objects
 * \param minion Pointer to the minion we are removing
 */
void CRemoveVisitor::VisitMinion(CMinion * minion)
{
	mPointsRemoved = minion->GetPoints();
}

/**
 * Remove visit handler for gru objects
 * \param gru Pointer to the gru we are removing
 */
void CRemoveVisitor::VisitGru(CGru * gru)
{
	mGruVisited = true;
}
