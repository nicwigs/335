#pragma once

class CTimeline;

// CTimelineDlg dialog

/**
 * handles timeline dlg box
 */
class CTimelineDlg : public CDialog
{
	DECLARE_DYNAMIC(CTimelineDlg)

public:
	CTimelineDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTimelineDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMELINEDLG };
#endif

	void SetTimeline(CTimeline * timeline);

	void Take();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	///Number of frames
	int mNumFrames;

	/// The timeline we are editing
	CTimeline *mTimeline = nullptr;
	/// frame rate 
	int mFrameRate;
};
