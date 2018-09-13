/**
 * \file HeadTop.h
 *
 * \author Nic Wiggins
 *
 * Class that describes the top of a head. 
 */

#pragma once

#include "ImageDrawable.h"

/**
 * Class that describes the top of a head. 
 */
class CHeadTop : public CImageDrawable
{
public:
	CHeadTop(const std::wstring &name, const std::wstring &filename);
	virtual ~CHeadTop();

	/** \brief Default constructor disabled */
	CHeadTop() = delete;
	/** \brief Copy constructor disabled */
	CHeadTop(const CHeadTop &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CHeadTop &) = delete;

	/**
	* Head top can move on its own
	*\return true since head top is free to move. 
	*/
	bool IsMovable() override { return true; }

	virtual void Draw(Gdiplus::Graphics *graphics) override;

	Gdiplus::Point TransformPoint(Gdiplus::Point p);

	void DrawEyeBrow(Gdiplus::Graphics * graphics, Gdiplus::Point in, Gdiplus::Point out);

	void DrawEye(Gdiplus::Graphics * graphics, Gdiplus::Point center);

	/** The right eye center
	* \param pos The new drawable position */
	void SetRightEyeCenter(Gdiplus::Point pos) { mRightEye = pos; }

	/** The left eye center
	* \param pos The new drawable position */
	void SetLeftEyeCenter(Gdiplus::Point pos) { mLeftEye = pos; }

	/** The right eyebrow points 
	* \param inPos The new drawable position
	* \param outPos The new drawable position */
	void SetRightEyeBrow(Gdiplus::Point inPos, Gdiplus::Point outPos) { mInRightEyeBrow = inPos; mOutRightEyeBrow = outPos;}

	/** The left eyebrow points 
	* \param inPos The new drawable position 
	* \param outPos The new drawable position */
	void SetLeftEyeBrow(Gdiplus::Point inPos, Gdiplus::Point outPos) { mInLeftEyeBrow = inPos; mOutLeftEyeBrow = outPos; }


private:
	/// Center of right eye
	Gdiplus::Point mRightEye = Gdiplus::Point(0,0);
	/// Center of left eye
	Gdiplus::Point mLeftEye = Gdiplus::Point(0, 0);

	/// In point of right eyebrow
	Gdiplus::Point mInRightEyeBrow = Gdiplus::Point(0, 0);
	/// Out point of right eyebrow
	Gdiplus::Point mOutRightEyeBrow = Gdiplus::Point(0, 0);

	/// In point of left eyebrow
	Gdiplus::Point mInLeftEyeBrow = Gdiplus::Point(0, 0);
	/// Out point of left eyebrow
	Gdiplus::Point mOutLeftEyeBrow = Gdiplus::Point(0, 0);

};

