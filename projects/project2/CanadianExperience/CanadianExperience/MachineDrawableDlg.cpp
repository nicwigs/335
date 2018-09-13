// MachineDrawableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CanadianExperience.h"
#include "MachineDrawableDlg.h"
#include "afxdialogex.h"
#include "MachineDrawable.h"
#include "Actor.h"

// CMachineDrawableDlg dialog

IMPLEMENT_DYNAMIC(CMachineDrawableDlg, CDialog)

/**
 * COnstructor. 
 * \param pParent Window
 */
CMachineDrawableDlg::CMachineDrawableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MACHINEDRAWABLEDLG, pParent)
	, mStartFrame(0)
	, mXPosition(0)
	, mYPosition(0)
{

}

/**
 * Destructor. 
 */
CMachineDrawableDlg::~CMachineDrawableDlg()
{
}

/**
 * Pass a machine drawable object
 * \param drawable THe machine drawable object
 */
void CMachineDrawableDlg::SetMachineDrawable(std::shared_ptr<CMachineDrawable> drawable)
{
	mMachineDrawable = drawable;
	mStartFrame = mMachineDrawable->GetStartFrame();
}

/**
 * Pass the actor of the machine
 * \param actor The actor that has the machine
 */
void CMachineDrawableDlg::SetActor(std::shared_ptr<CActor> actor)
{
	mActor = actor;
	mXPosition = mActor->GetPosition().X;
	mYPosition = mActor->GetPosition().Y;
}

/**
 * Transfer dialog values to the machinedrawable object
 */
void CMachineDrawableDlg::Take()
{
	mMachineDrawable->SetMachineStartFrame(mStartFrame);
	mActor->SetPosition(Gdiplus::Point((int)mXPosition, (int)mYPosition));
}

/**
 * Moves data
 * \param pDX Pointer to data exchange class
 */
void CMachineDrawableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STARTFRAME, mStartFrame);
	DDV_MinMaxInt(pDX, mStartFrame, 0, 10000);
	DDX_Text(pDX, IDC_XPOS, mXPosition);
	DDX_Text(pDX, IDC_YPOS, mYPosition);
}


BEGIN_MESSAGE_MAP(CMachineDrawableDlg, CDialog)
END_MESSAGE_MAP()


// CMachineDrawableDlg message handlers
