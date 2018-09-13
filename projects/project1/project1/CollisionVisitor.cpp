/**
 * \file CollisionVisitor.cpp
 *
 * \author Ian Guswiler
 */

#include "stdafx.h"
#include "CollisionVisitor.h"
#include "Villain.h"
#include "Minion.h"
#include "Game.h"
#include "RemoveVisitor.h"


 /**
  * Destructor
  */
CCollisionVisitor::~CCollisionVisitor()
{
}

/**
 * Villain collision visit handler
 * \param villain Pointer to the villain that is being collided with
 */
void CCollisionVisitor::VisitVillain(CVillain * villain)
{
	auto game = villain->GetGame();

	if (!game->IsGameOver())
	{
		CRemoveVisitor visitor;
		mCollidingItem->Accept(&visitor);

		game->QueueRemove(mCollidingItem);

		if (visitor.GruVisited())
		{
			game->EndGame();
		}
		else
		{
			//Villain needs a public function to add points to its corresponding counter
			villain->AddPoints(visitor.GetPoints());
		}
	}
}

/**
 * Minion collision visit handler
 * \param minion Pointer to the minion that is being collided with
 */
void CCollisionVisitor::VisitMinion(CMinion * minion)
{

	auto game = minion->GetGame();

	if (!game->IsGameOver())
	{
		CRemoveVisitor visitor;
		mCollidingItem->Accept(&visitor);

		if (visitor.GruVisited())
		{
			game->QueueRemove(game->GetGru());
			game->EndGame();
		}
	}
}

/**
 * Gru collision visit handler
 * \param gru Pointer to the gru that is being collided with
 */
void CCollisionVisitor::VisitGru(CGru * gru)
{

	auto game = gru->GetGame();

	if (!game->IsGameOver())
	{
		CRemoveVisitor visitor;
		mCollidingItem->Accept(&visitor);

		if (visitor.GetPoints() > 0)
		{
			game->QueueRemove(game->GetGru());
			game->EndGame();
		}
	}
}
