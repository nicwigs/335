/**
 * \file Button2.h
 *
 * \author Charles Owen
 *
 * Simple 2-image button
 * \cond
 */

#pragma once

#include <memory>

/**
 * Simple 2-image button
 */
class AFX_EXT_CLASS CButton2
{
public:
	CButton2();
	virtual ~CButton2();

	bool ButtonDown(CPoint point);

	void ButtonUp();

	void Draw(Gdiplus::Graphics *graphics);

	bool Load(const wchar_t * up, const wchar_t * down);

	int GetHeight() const { return mUp->GetHeight(); }

	/**
	 * Set the position of the center of the button
	 */
	void SetPosition(int x, int y) { mPosition = Gdiplus::Point(x, y); }

	/** Set the enabled status for the button
	 * \param enabled Enabled status */
	void SetEnabled(bool enabled) { mEnabled = enabled; mPressed = false; }

	/// Is the button enabled?
	/// \return true if enabled
	bool IsEnabled() const { return mEnabled; }

private:
	bool mLoaded = false;
	bool mEnabled = false;
	bool mPressed = false;

	Gdiplus::Point mPosition;

	std::shared_ptr<Gdiplus::Bitmap>  mUp;
	std::shared_ptr<Gdiplus::Bitmap>  mDown;
};

/// \endcond
