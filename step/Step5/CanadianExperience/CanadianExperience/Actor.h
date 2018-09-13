/**
 * \file Actor.h
 *
 * \author Nic Wiggins
 *
 * Class for actors in our drawings.
 */

#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Drawable.h"

class CPicture;

 /**
 * Class for actors in our drawings.
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */
class CActor
{
public:
	CActor(const std::wstring &name);
	virtual ~CActor();

	/** Default constructor disabled */
	CActor() = delete;
	/** Copy constructor disabled */
	CActor(const CActor &) = delete;
	/** Assignment operator disabled */
	void operator=(const CActor &) = delete;

	void SetRoot(std::shared_ptr<CDrawable> root);
	void Draw(Gdiplus::Graphics *graphics);
	std::shared_ptr<CDrawable> HitTest(Gdiplus::Point pos);
	void AddDrawable(std::shared_ptr<CDrawable> drawable);

	/** Get the actor name
	* \returns Actor name */
	std::wstring GetName() const { return mName; }

	/** The actor position
	* \returns The actor position as a point */
	Gdiplus::Point GetPosition() const { return mPosition; }

	/** The actor position
	* \param pos The new actor position */
	void SetPosition(Gdiplus::Point pos) { mPosition = pos; }

	/** Actor is enabled
	* \returns enabled status */
	bool IsEnabled() const { return mEnabled; }

	/** Set Actor Enabled
	* \param enabled New enabled status */
	void SetEnabled(bool enabled) { mEnabled = enabled; }

	/** Actor is clickable
	* \returns true if actor is clickable */
	bool IsClickable() const { return mClickable; }

	/** Actor clickable
	* \param clickable New clickable status */
	void SetClickable(bool clickable) { mClickable = clickable; }

	/** Set picture
	* \param picture New actor picture */
	void SetPicture(CPicture* picture) { mPicture = picture; }
	
	/** The actor picture
	* \returns The actor picture as a pointer  */
	CPicture* GetPicture() const { return mPicture; }

private:
	///Name of actor. 
	std::wstring mName;
	///If actor is enabled
	bool mEnabled = true;
	///Position of actor
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);
	///If actor is clickable
	bool mClickable = true;

	/// The root drawable
	std::shared_ptr<CDrawable> mRoot;
	/// The drawables in drawing order
	std::vector<std::shared_ptr<CDrawable>> mDrawablesInOrder;

	///Picture of actor
	CPicture *mPicture = nullptr;
};

