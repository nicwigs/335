/**
 * \file MachineDrawableDlg.h
 *
 * \author Nic Wiggins
 *
 * The machine drawable parameters dialog box.
 */

#pragma once

#include "MachineDrawable.h"

// CMachineDrawableDlg dialog

/**
 * Class that describes a machinedrawable parameters dialog
 */
class CMachineDrawableDlg : public CDialog
{
	DECLARE_DYNAMIC(CMachineDrawableDlg)

public:
	CMachineDrawableDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMachineDrawableDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MACHINEDRAWABLEDLG };
#endif

	void SetMachineDrawable(std::shared_ptr<CMachineDrawable> drawable);
	void SetActor(std::shared_ptr<CActor> actor);
	void Take();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	int mStartFrame; ///< Start frame of machine

	std::shared_ptr<CMachineDrawable> mMachineDrawable; ///< Drawable of machine
	std::shared_ptr<CActor> mActor; ///< Actor of machine
	double mXPosition; ///<X Position in pixels
	double mYPosition; ///< Y position in pixels
};
