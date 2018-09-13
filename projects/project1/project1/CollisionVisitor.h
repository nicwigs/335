/**
 * \file CollisionVisitor.h
 *
 * \author Ian Guswiler
 *
 * Describes the collision visitor class
 */

#pragma once
#include "ItemVisitor.h"
#include "GameItem.h"


/**
 * Class for handling collisions
 */
class CCollisionVisitor :
	public CItemVisitor
{
public:
	/// Default constructor (disabled)
	CCollisionVisitor() = delete;

	/// Copy constructor (disabled)
	CCollisionVisitor(const CCollisionVisitor &) = delete;

	/**
	* Constructor
	*\param collidingItem The item that is colliding
	*/
	CCollisionVisitor(std::shared_ptr<CGameItem> collidingItem) { mCollidingItem = collidingItem; }
	virtual ~CCollisionVisitor();

	void VisitVillain(CVillain *villain) override;

	void VisitMinion(CMinion *minion) override;

	void VisitGru(CGru *gru) override;

private:
	/// Item that initiated the collision
	std::shared_ptr<CGameItem> mCollidingItem;
};

