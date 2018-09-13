/**
 * \file Game.cpp
 *
 * \author Nic Wiggins, Mark Elinski
 */

#include "stdafx.h"
#include <algorithm>
#include <memory>
#include <string>

#include "Game.h"
#include "GameItem.h"
#include "NewButton.h"
#include "Arya.h"
#include "Juicer.h"
#include "Pokeball.h"
#include "Stuart.h"
#include "Jerry.h"
#include "MutantMinion.h"
#include "Gru.h"
#include "ClickVisitor.h"
#include "CollisionVisitor.h"

using namespace std;
using namespace Gdiplus;

/// Image of stuart
const wstring StuartImageName = L"images/stuart.png";
 /// Game area width in virtual pixels
const static int Width = 1400;

/// Game area height in virtual pixels
const static int Height = 1100;

/// Minimum time after 0.5 seconds that a minion can be spawned
const double minEmissionTime = 0;

/// Maximum time after 0.5 seconds that a minion can be spawned
const double maxEmissionTime = 0.5;

/// Odds that an emitted minion will be mutant (odds = 1 in this number)
const double mutantOdds = 10;

/// Converts timer value to time in seconds
const double TimerToSeconds = 1000;


/**
 * Constructor. 
 */
CGame::CGame()
{
	InitializeItems();
}


/**
 * Destructor. 
 */
CGame::~CGame()
{
}


/**
* Draw the game area
* \param graphics The GDI+ graphics context to draw on
* \param width Width of the client window
* \param height Height of the client window
*/
void CGame::OnDraw(Gdiplus::Graphics *graphics, int width, int height)
{
	// Fill the background with black
	SolidBrush brush(Color::Black);
	graphics->FillRectangle(&brush, 0, 0, width, height);

	//
	// Automatic Scaling
	//
	float scaleX = float(width) / float(Width);
	float scaleY = float(height) / float(Height);
	mScale = min(scaleX, scaleY);

	mXOffset = width / 2.0f;
	mYOffset = height / 2.0f;

	graphics->TranslateTransform(mXOffset, mYOffset);
	graphics->ScaleTransform(mScale, mScale);

	// From here on you are drawing virtual pixels

	//Draw the play area border 
	Pen pen(Color::Green, 2);
	mPlayingArea.DrawBorder(graphics, &pen);

	//Draw ScoreBoard
	mScoreBoard.Draw(graphics);

	//The following code makes minions spawn every 0.5 to 1 second
	double randEmissionTime = maxEmissionTime + ((double)rand() / RAND_MAX) * (maxEmissionTime - minEmissionTime);

	if (mMinionEmission > 50) {
		if (mScoreBoard.timeSinceLastEmission() / TimerToSeconds >= randEmissionTime)
		{
			double randMinion = ((double)rand() / RAND_MAX) * mutantOdds;
			if (randMinion <= 1)
			{
				Add(make_shared<CMutantMinion>(this));
			}
			else if (((double)rand() / RAND_MAX) <= 0.5)
			{
				Add(make_shared<CStuart>(this));
			}
			else
			{
				Add(make_shared<CJerry>(this));
			}
			mScoreBoard.ResetEmissionTime();
		}
	}
	else {
		mMinionEmission++;
	}
	



	//Add code in CChildView class
	//Add constants to playarea ->see owens thing on virtual pixels 
	
	for (auto item : mItems)
	{
		item->Draw(graphics);
	}

	//Display end of game message if Gru is dead
	if (mGameOver)
	{
		DisplayGameOverMessage(graphics);
	}
	
}


/**
* Add an item to the game
* \param item New item to add
*/
void CGame::Add(std::shared_ptr<CGameItem> item)
{
	mItems.push_back(item);
}

/**
 * Adds a game item to the remove list
 * \param item Item to remove
 */
void CGame::Remove(std::shared_ptr<CGameItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
	}
}

/**
 * Adds a game item to the list of items to remove
 * \param item Item to add to the remove list
 */
void CGame::QueueRemove(std::shared_ptr<CGameItem> item)
{
	mItemsToRemove.push_back(item);
}

/**
* Removes items in the remove list from the game
*/
void CGame::RemoveItems()
{
	for (auto item : mItemsToRemove)
	{
		Remove(item);
	}

	mItemsToRemove.clear();
}


/** Test an x,y click location to see if it clicked
* on some item in the game.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<CGameItem> CGame::HitTest(int x, int y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}

	return  nullptr;
}


/**
* Move an item to the end of the list mItems
* \param item The item to be moved to the end
*/
void CGame::MoveToFront(std::shared_ptr<CGameItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
		mItems.push_back(item);
	}
}


/**
* Clear the game data.
*
* Deletes all known items in the game.
*/
void CGame::Clear()
{
	mItems.clear();
	mItemsToRemove.clear();
}


/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CGame::Update(double elapsed)
{
	for (auto item : mItems)
	{
		item->Update(elapsed);
	}

	CheckCollisions();
}

/**
* Handle a click on the playing area
* \param x X location clicked on
* \param y Y location clicked on
*/
void CGame::OnLButtonDown(int x, int y)
{
	mMouseVirtualX = (x - mXOffset) / mScale;
	mMouseVirtualY = (y - mYOffset) / mScale;

	auto item = HitTest((int)mMouseVirtualX, (int)mMouseVirtualY);
	if (item != nullptr)
	{
		CClickVisitor visitor;
		item->Accept(&visitor);

		if (visitor.GruClicked())
		{
			mGrabbedItem = item;
		}
	}
}

/**
 * Called when the mouse is moved
 * \param nFlags Flags associated with the mouse movement
 * \param point Where the button was pressed
 */
void CGame::OnMouseMove(UINT nFlags, CPoint point)
{
	mMouseVirtualX = (point.x - mXOffset) / mScale;
	mMouseVirtualY = (point.y - mYOffset) / mScale;

	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			// Prevent Gru from leaving the playing area 
			if (abs(mMouseVirtualX) <= (mPlayingArea.GetGridRadius() - mGru->GetImageWidth()/2) && 
				abs(mMouseVirtualY) <= (mPlayingArea.GetGridRadius() - mGru->GetImageHeight()/2))
			{
				mGrabbedItem->SetLocation(mMouseVirtualX, mMouseVirtualY);
			}
			else if (abs(mMouseVirtualX) >= (mPlayingArea.GetGridRadius() - mGru->GetImageWidth() / 2) &&
				abs(mMouseVirtualY) <= (mPlayingArea.GetGridRadius() - mGru->GetImageHeight() / 2))
			{
				mGrabbedItem->SetLocation(mGrabbedItem->GetX(), mMouseVirtualY);
			}
			else if (abs(mMouseVirtualX) <= (mPlayingArea.GetGridRadius() - mGru->GetImageWidth() / 2) &&
				abs(mMouseVirtualY) >= (mPlayingArea.GetGridRadius() - mGru->GetImageHeight() / 2))
			{
				mGrabbedItem->SetLocation(mMouseVirtualX, mGrabbedItem->GetY());
			}
		}
		else
		{
			// When the left button is released, we release the
			// item.
			mGrabbedItem = nullptr;
		}
	}
}

/**
 * Resets the game to a new game
 */
void CGame::NewGame()
{
	mGameOver = false;
	mMinionEmission = 1;

	// Clear existing game items
	Clear();

	// Initialize starting game items
	InitializeItems();

	mScoreBoard.Reset();
}

/**
 * Private helper to initialize starting game items
 */
void CGame::InitializeItems()
{
	shared_ptr<CNewButton> button = make_shared<CNewButton>(this);
	Add(button);

	//These are the villain images in the play area
	shared_ptr<CArya> arya = make_shared<CArya>(this);
	Add(arya);

	shared_ptr<CJuicer> juicer = make_shared<CJuicer>(this);
	Add(juicer);

	shared_ptr<CPokeball> pokeball = make_shared<CPokeball>(this);
	Add(pokeball);

	shared_ptr<CGru> gru = make_shared<CGru>(this);
	Add(gru);
	mGru = gru;
}


/**
 * Private helper to check collisions of game items
 */
void CGame::CheckCollisions()
{
	for (auto i = mItems.begin(); i != mItems.end(); i++)
	{
		CCollisionVisitor visitor(*i);
		for (auto j = mItems.begin(); j != mItems.end(); j++)
		{
			if (j != i && (*j)->HitTest(int((*i)->GetX()),int((*i)->GetY())))
			{
				(*j)->Accept(&visitor);
			}
		}
	}

	RemoveItems();
}

/**
* Ends the game
*/
void CGame::EndGame()
{
	mScoreBoard.StopTimer();

	mGameOver = true;
}


/**  Draw the ScoreBoard
* \param graphics The graphics context to draw on
*/
void CGame::DisplayGameOverMessage(Gdiplus::Graphics *graphics)
{
	WCHAR string[] = L"Gru is dead!";

	Gdiplus::Font font(L"Arial", 100);
	RectF layoutRect(-500.0f, -100.0f, 1000.0f, 200.0f);
	StringFormat format;
	format.SetAlignment(StringAlignmentCenter);
	SolidBrush yellow(Color(255, 255, 0));

	graphics->DrawString(string, 12, &font, layoutRect, &format, &yellow);
}