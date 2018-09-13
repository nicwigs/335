/**
* \file Gru.cpp
*
* \author Vincent R Pahl
*/

#include "stdafx.h"
#include <string>
#include "Gru.h"
#include "GameItem.h"
#include "Game.h"

using namespace Gdiplus;
using namespace std;

/// Gru filename
const wstring GruImageName = L"images/gru.png";

/// Gru X Position at the start of the game
const int GruPosX = 0;

/// Gru Y Position at the start of the game
const int GruPosY = 0;

/**
 * Constructor. 
 * \param game Pointer to the game Gru is a part of
 */
CGru::CGru(CGame *game) :
	CGameItem::CGameItem(game, GruImageName, GruPosX, GruPosY)
{
	mGruImage = unique_ptr<Bitmap>(Bitmap::FromFile(GruImageName.c_str()));
	if (mGruImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += GruImageName;
		AfxMessageBox(msg.c_str());
	}
}

/**
* Destructor
*/
CGru::~CGru()
{
}

/**
 * Handler for visitors
 * \param visitor Pointer to the visitor being handled
 */
void CGru::Accept(CItemVisitor * visitor)
{
	visitor->VisitGru(this);
}
