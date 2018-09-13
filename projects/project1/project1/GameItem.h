/**
 * \file GameItem.h
 *
 * \author Ian Guswiler, Mark Elinski
 *
 * Describes the base GameItem class
 */

#pragma once

#include <memory>
#include <string>
#include "ItemVisitor.h"
#include "Vector.h"


class CGame;


/**
 * Class representing a general game item
 */
class CGameItem
{
public:
	/// Default constructor (disabled)
	CGameItem() = delete;

	/// Copy constructor (disabled)
	CGameItem(const CGameItem &) = delete;

	virtual ~CGameItem();

	/** The X location of the item
	* \returns X location in pixels */
	double GetX() const { return mP.X(); }

	/** The Y location of the item
	* \returns Y location in pixels */
	double GetY() const { return mP.Y(); }

	/** The X,Y location of the item in a vector
	* \returns mP position vector in pixels */
	CVector GetP() const { return mP; }

	/// Set the game item location
	/// \param x X location
	/// \param y Y location
	void SetLocation(double x, double y) { mP.SetX(x); mP.SetY(y); }

	virtual void Draw(Gdiplus::Graphics *graphics);

	bool HitTest(int x, int y);

	/// Handle updates for animation
	/// \param elapsed The time since the last update
	virtual void Update(double elapsed) {};

	/// Get the game this item is in
	/// \returns Game pointer
	CGame *GetGame() { return mGame; }

	/// Get the width of the item
	/// \returns Item width in pixels
	double GetImageWidth() { return mItemImage->GetWidth(); };

	/// Get the height of the item
	/// \returns Item height in pixels
	double GetImageHeight() { return mItemImage->GetHeight(); };

	/** Accepts our visitor.
	* \param visitor Visitor we are accepting. 
	*/
	virtual void Accept(CItemVisitor *visitor) {};

protected:
	CGameItem(CGame * game, const std::wstring & filename, double xPos, double yPos);
		
	/// The game this item is contained in
	CGame *mGame;

	/// The image for the item
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;

private:

	///Item location in playing area.
	CVector mP;  ///<Position. 

};

