/**
 * \file MainFrm.h
 *
 * \author 
 *
 * The program main frame.
 */

#pragma once
#include "ViewEdit.h"
#include "ViewTimeline.h"
#include "MachineDrawable.h"

#include <memory>

class CPicture;

/** Program main frame */
class CMainFrame : public CFrameWndEx
{
	
public:
	CMainFrame();

    /** Enumerations for the possible manipulation modes */
    enum MotionModes { Move, Rotate };

    /** The selected manipulation mode 
     * \returns Currently selected manipulation mode */
    MotionModes GetMode() const { return mMode; }
	/** The drawable machine A
	* \returns Pointer to machineDrawable A */
	std::shared_ptr<CMachineDrawable> GetDrawableMachineA() { return mDrawableMachineA; };
	/** The drawable machine B
	* \returns Pointer to machineDrawable B */
	std::shared_ptr<CMachineDrawable> GetDrawableMachineB() { return mDrawableMachineB; };

protected: 
	DECLARE_DYNAMIC(CMainFrame)

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCToolBar     m_wndToolBar;
	CMFCStatusBar   m_wndStatusBar;
	CSplitterWnd    mWndSplitter;

private:
    void Initialize();

    /// The timeline window
    CViewTimeline  *mViewTimeline;

    /// The editing window
    CViewEdit      *mViewEdit;

    /// The current manipulation mode
    MotionModes mMode = Move;

    /// The picture object we are viewing/editing
    std::shared_ptr<CPicture> mPicture;

	///Pointer to machineA
	std::shared_ptr<CMachineDrawable> mDrawableMachineA;
	///Pointer to machineB
	std::shared_ptr<CMachineDrawable> mDrawableMachineB;
	///Pointer to machineA
	std::shared_ptr<CActor> mActorMachineA;
	///Pointer to machineB
	std::shared_ptr<CActor> mActorMachineB;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnEditMove();
    afx_msg void OnUpdateEditMove(CCmdUI *pCmdUI);
    afx_msg void OnEditRotate();
    afx_msg void OnUpdateEditRotate(CCmdUI *pCmdUI);
    afx_msg void OnEditTimelineproperties();
	afx_msg void OnMachineMachineasetnumber();
	afx_msg void OnMachineMachinebsetnumber();
	afx_msg void OnMachineaProperties();
	afx_msg void OnMachinebProperties();
};


