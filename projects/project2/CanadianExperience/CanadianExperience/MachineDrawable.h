/**
 * \file MachineDrawable.h
 *
 * \author Nic Wiggins
 *
 * Class that describes a machine drawable
 */

#pragma once
#include "Drawable.h"
#include "Machine.h"

/**
 * Class that describs a machine in the canadian experience
 */
class CMachineDrawable : public CDrawable
{
public:
	CMachineDrawable(const std::wstring &name);
	virtual ~CMachineDrawable();

	/** \brief Default constructor disabled */
	CMachineDrawable() = delete;
	/** \brief Copy constructor disabled */
	CMachineDrawable(const CMachineDrawable &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CMachineDrawable &) = delete;

	virtual void Draw(Gdiplus::Graphics *graphics) override;
	virtual bool HitTest(Gdiplus::Point pos) override;
	void Place(Gdiplus::Point offset, double rotate) override;
	void SetMachineNumber(int number);
	void ShowMachineSeedDialogBox();
	void SetFrameRate(double rate);
	void SetMachineStartFrame(int frame);
	int GetStartFrame();
	virtual void GetKeyframe() override;


	void Save(std::shared_ptr<xmlnode::CXmlNode> root, const std::wstring &name);
	void Load(std::shared_ptr<xmlnode::CXmlNode> root, const std::wstring &name);


private:
	std::shared_ptr<CMachine> mMachine; ///< Machine
	int mStartFrame = 0; ///< time after this start machine

};

