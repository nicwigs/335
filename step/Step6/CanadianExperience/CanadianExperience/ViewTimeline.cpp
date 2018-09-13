/**
 * \file ViewTimeline.cpp
 *
 * \author Nic Wiggins
 */


#include "stdafx.h"
#include "CanadianExperience.h"
#include "ViewTimeline.h"
#include "DoubleBufferDC.h"
#include "Timeline.h"
#include "Picture.h"
#include <sstream>

#include "MainFrm.h"

using namespace std;
using namespace Gdiplus;


IMPLEMENT_DYNCREATE(CViewTimeline, CScrollView)

/// The window height in pixels
const int WindowHeight = 60;

/// The spacing from the top of the 
/// window to the top of the tick marks in pixels
const int BorderTop = 20;

/// Space to the left of the scale in pixels
const int BorderLeft = 10;

/// Space to the right of the scale in pixels
const int BorderRight = 10;

/// The spacing between ticks on the timeline in pixels
const int TickSpacing = 3;

/// The length of a short tick mark in pixels
const int TickShort = 10;

/// The length of a long tick mark in pixels
const int TickLong = 20;

/// Divisor to cut height and width in half. 
const int half = 2;

/** Constructor */
CViewTimeline::CViewTimeline()
{
	mPointer = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/pointer-down.png"));
	assert(mPointer->GetLastStatus() == Ok);
}

/** Destructor */
CViewTimeline::~CViewTimeline()
{
}

/** Force an update of this window when the picture changes.
*/
void CViewTimeline::UpdateObserver()
{
	Invalidate();
	UpdateWindow();
}


/** Handle the initial update for this window */
void CViewTimeline::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    int sbHeight = GetSystemMetrics(SM_CXHSCROLL);
    CSize sizeTotal(200, Height - sbHeight - 20);
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/** Draw this window 
 * \param pDC Device context */
void CViewTimeline::OnDraw(CDC* pDC)
{
	// Get the timeline
	CTimeline *timeline = GetPicture()->GetTimeline();

	// Set the scroll system correctly
	CSize sizeTotal(timeline->GetNumFrames() * TickSpacing + BorderLeft + BorderRight, WindowHeight);
	SetScrollSizes(MM_TEXT, sizeTotal);

    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context
	
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 10);

	//Timeline
	Pen tickpen(Color(0, 0, 0), 1);
	int xLocation = BorderLeft;
	for (int tickNum = 0; tickNum <= timeline->GetNumFrames(); tickNum++)
	{		
		bool onSecond = (tickNum % timeline->GetFrameRate()) == 0;
		if (onSecond)
		{
			graphics.DrawLine(&tickpen, xLocation, BorderTop, xLocation, BorderTop + TickLong);

			// Convert the tick number to seconds in a string
			std::wstringstream str;
			str << tickNum / timeline->GetFrameRate();
			std::wstring wstr = str.str();

			RectF size;
			PointF origin(0.0f, 0.0f);
			graphics.MeasureString(wstr.c_str(), wstr.size(),
				&font, origin, &size);

			SolidBrush brush(Color(0, 0, 0));
			graphics.DrawString(wstr.c_str(),  // String to draw
				-1,         // String length, -1 means it figures it out on its own
				&font,      // The font to use
				PointF(xLocation - size.Width/half, BorderTop+TickLong),   // Where to draw
				&brush);    // The brush to draw the text with
		}
		else
		{
			graphics.DrawLine(&tickpen, xLocation, BorderTop, xLocation, BorderTop + TickShort);
		}
		xLocation += TickSpacing;
	}

	//Draw the pointer. 
	graphics.DrawImage(mPointer.get(),
		float(timeline->GetCurrentTime()*timeline->GetFrameRate()*TickSpacing + BorderLeft-mPointer->GetWidth()/half),
		float(BorderTop),
		(float)mPointer->GetWidth(),
		(float)mPointer->GetHeight());
}


/** Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context 
 * \return FALSE */
BOOL CViewTimeline::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

/** Handle a press of the keyframe set button on the toolbar
*/
void CViewTimeline::OnEditSetkeyframe()
{
	for (auto actor : *GetPicture())
	{
		actor->SetKeyframe();
	}
}


 /** Handle the Edit>Delete Keyframe menu option */
 void CViewTimeline::OnEditDeletekeyframe()
 {
	 for (auto actor : *GetPicture())
	 {
		 actor->DeleteKeyframe();
	 }
	 GetPicture()->SetAnimationTime(GetPicture()->GetTimeline()->GetCurrentTime());
 }


 // Doxygen sometimes gets confused by these message 
 // maps, since they look like functions. I've found
 // it helps to move them to the end of the file.
 BEGIN_MESSAGE_MAP(CViewTimeline, CScrollView)
	 ON_WM_CREATE()
	 ON_WM_ERASEBKGND()
	 ON_COMMAND(ID_EDIT_SETKEYFRAME, &CViewTimeline::OnEditSetkeyframe)
	 ON_COMMAND(ID_EDIT_DELETEKEYFRAME, &CViewTimeline::OnEditDeletekeyframe)
	 ON_WM_LBUTTONDOWN()
	 ON_WM_MOUSEMOVE()
 END_MESSAGE_MAP()

 /** Handle a left button mouse press event
 * \param nFlags flags associated with the mouse press
 * \param point The location of the mouse press
 */
 void CViewTimeline::OnLButtonDown(UINT nFlags, CPoint point)
 {
	 // Convert mouse coordinates to logical coordinates
	 CClientDC dc(this);
	 OnPrepareDC(&dc);
	 dc.DPtoLP(&point);

	 int x = point.x;

	 // Get the timeline
	 CTimeline *timeline = GetPicture()->GetTimeline();
	 int pointerX = (int)(timeline->GetCurrentTime() *
		 timeline->GetFrameRate() * TickSpacing + BorderLeft);

	 mMovingPointer = x >= pointerX - (int)mPointer->GetWidth() / 2 &&
		 x <= pointerX + (int)mPointer->GetWidth() / 2;

	 __super::OnLButtonDown(nFlags, point);
 }


/**
 * Handles when mouse is moving
 * \param nFlags Flags from mouse move
 * \param point Point where the mouse is. 
 */
 void CViewTimeline::OnMouseMove(UINT nFlags, CPoint point)
 {
	 // Convert mouse coordinates to logical coordinates
	 CClientDC dc(this);
	 OnPrepareDC(&dc);
	 dc.DPtoLP(&point);

	 int x = point.x;

	 if (mMovingPointer)
	 {
		 // Get the timeline
		 CTimeline *timeline = GetPicture()->GetTimeline();

		 // If an item is being moved, we only continue to 
		 // move it while the left button is down.
		 if (nFlags & MK_LBUTTON)
		 {
			 double newX = (x - BorderLeft) / ((double)TickSpacing*timeline->GetFrameRate());
			 if (newX >= 0 && newX <= timeline->GetDuration())
			 {
				 GetPicture()->SetAnimationTime(newX);
			 }
		 }
		 else
		 {
			 // When the left button is released, we release the
			 // item.
			 mMovingPointer = false;
		 }
	 }
 }
