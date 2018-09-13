/**
* \file Gru.h
*
* \author Vincent R Pahl
*
* This class defines the player Gru
*/

#pragma once
#include "GameItem.h"

/**
 * Class that defines our main character Gru
 */
class CGru : public CGameItem
{
public:
	CGru(CGame *game);

	/// Default constructor (disabled)
	CGru() = delete;

	/// Copy constructor (disabled)
	CGru(const CGru &) = delete;

	virtual ~CGru();

	void Accept(CItemVisitor *visitor) override;

private:
	std::unique_ptr<Gdiplus::Bitmap> mGruImage; ///< image of Gru
};

