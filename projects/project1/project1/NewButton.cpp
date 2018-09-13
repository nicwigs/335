/**
 * \file NewButton.cpp
 *
 * \author Ian Guswiler
 */

#include "stdafx.h"
#include "NewButton.h"
#include "Game.h"

using namespace std;

/// Filename for the new button image
const wstring NewButtonImageName = L"images/new-game.png";

/// X draw position for the new button
const double ButtonX = -620;

/// Y draw position for the new button
const double ButtonY = -447;

/**
 * Constructor
 * \param game Pointer to the game object the button is part of 
 */
 CNewButton::CNewButton(CGame * game) : CGameItem(game, NewButtonImageName, ButtonX, ButtonY)
 {
 }

/**
 * Destructor
 */
 CNewButton::~CNewButton()
{
}

/**
 * Click event handler
 */
 void CNewButton::OnClick()
 {
	 auto game = GetGame();
	 game->NewGame();
 }

 /**
 * Called before the button is drawn
 * This empty class is needed so the button can be drawn outside
 * of the playing area (game items are restricted from doing that)
 * \param elapsed Time since last draw.
 */
 void CNewButton::Update(double elapsed)
 {
	 
 }