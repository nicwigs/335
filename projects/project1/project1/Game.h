/**
 * \file Game.h
 *
 * \author Nic Wiggins
 * \author Mark Elinski
 *
 *  Class that implements a game in which we can move players
 */

#pragma once

#include <memory>
#include <vector>
#include "GameItem.h"
#include "PlayingArea.h"
#include "Scoreboard.h"

// #include "ScoreBoard.h"
#include "Gru.h"

/**
 * Implements a game in which we can play
 */
class CGame
{
public:
	CGame();
	virtual ~CGame();

	void OnDraw(Gdiplus::Graphics * graphics, int width, int height);

	void Add(std::shared_ptr<CGameItem> item);

	void Remove(std::shared_ptr<CGameItem> item);

	void QueueRemove(std::shared_ptr<CGameItem> item);

	void RemoveItems();

	std::shared_ptr<CGameItem> HitTest(int x, int y);

	void MoveToFront(std::shared_ptr<CGameItem> item);

	void Clear();

	void Update(double elapsed);

	void OnLButtonDown(int x, int y);

	void OnMouseMove(UINT nFlags, CPoint point);

	void NewGame();

	/** Get Grus position
	* \returns mGruPos position of Gru*/
	CVector GetGruPos() const { return mGru->GetP(); }

	/** See if game is over
	* \returns mGaeOver true is game is over*/
	bool GetGameOver() const { return mGameOver; }

	/**
	* Get the gru object pointer
	* \return Shared pointer to the gru object for this game
	*/
	std::shared_ptr<CGru> GetGru() { return mGru; }
	
	/** Accept a visitor for the collection
	* \param visitor The visitor for the collection
	*/
	void CGame::Accept(CItemVisitor *visitor)
	{
		for (auto item : mItems)
		{
			item->Accept(visitor);
		}
	}

	void EndGame();

	void DisplayGameOverMessage(Gdiplus::Graphics * graphics);

	/**
	* Checks if the game is over
	* \return True if the game is over
	*/
	bool IsGameOver() { return mGameOver; }

	/**
	* Getter for the scoreboard object
	* \return CScoreboard*
	*/
	CScoreboard *GetScoreboard() { return &mScoreBoard; }

	/**
	* Getter for the playarea object
	* \return mPlayingArea*
	*/
	CPlayingArea *GetPlayingArea() { return &mPlayingArea; }

private:

	/// Scale of window for virtual pixels/resizing
	float mScale;

	/// Offset in the X direction the game moves due to window scaling
	float mXOffset;

	/// Offset in the Y direction the game moves due to window scaling
	float mYOffset;

	/// All of the game items that make up our game
	std::vector<std::shared_ptr<CGameItem> > mItems;

	/// Iterators for items that need to be removed
	std::vector<std::shared_ptr<CGameItem>> mItemsToRemove;

	/// Item grabbed by the mouse after LBDown
	std::shared_ptr<CGameItem> mGrabbedItem;

	///Playing Area
	CPlayingArea mPlayingArea;

	///Virtual X location of mouse
	double mMouseVirtualX;

	///Virtual Y location of mouse
	double mMouseVirtualY;

	/// The Stuart spawn timer
	long mStuartSpawn = 1;

	/// The Jerry spawn timer
	long mJerrySpawn = 1;

	/// The mutant spawn timer
	long mMutantSpawn = 1;

	/// Wait for minion emission
	long mMinionEmission = 1;

	/// Gru item - main player of game
	std::shared_ptr<CGru> mGru; 

	/// Score Board - keeps track of score of our game
	CScoreboard mScoreBoard;

	/// True if Gru is dead 
	bool mGameOver = false;

	void InitializeItems();

	void CheckCollisions();

};

