/**
 * \file ChildView.h
 *
 * \author Jack L. Turak,Nic Wiggins
 *
 * interface of the CChildView class
 */



#pragma once

#include <memory>

#include "Game.h"



/// Frame duration in milliseconds
const int FrameDuration = 30;

// CChildView window


/**
 * Class for main window
 */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:

	/// Any item we are currently dragging
	//std::shared_ptr<CItem> mGrabbedItem;

	/// True until the first time we draw
	bool mFirstDraw = true;

	long long mLastTime;    ///< Last time we read the timer
	double mTimeFreq;       ///< Rate the timer updates

	/// the game
	CGame mGame;

	/// Any item we are currently dragging
	std::shared_ptr<CGameItem> mGrabbedItem;		

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

