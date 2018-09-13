/**
 * \file Drawable.h
 *
 * \author Nic Wiggins
 *
 * Abstract base class for drawable elements of our picture.
 */

#pragma once

#include <string>
#include <memory>
#include <vector>
#include "AnimChannelAngle.h"

class CActor;
class CTimeline;

 /**
 * Abstract base class for drawable elements of our picture.
 *
 * A drawable is one part of an actor. Drawable parts can be moved
 * independently.
 */
class CDrawable
{
public:
	virtual ~CDrawable();

	/** \brief Default constructor disabled */
	CDrawable() = delete;
	/** \brief Copy constructor disabled */
	CDrawable(const CDrawable &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CDrawable &) = delete;


	void virtual SetActor(CActor * actor);
	/** Get the drawable name
	* \param graphics Graphics to draw */
	virtual void Draw(Gdiplus::Graphics *graphics) = 0;
	void Place(Gdiplus::Point offset,double rotate);
	void AddChild(std::shared_ptr<CDrawable> child);
	/** See if click on drawable
	* \param pos Point of mouse
	*\return true if click on enabled drawable*/
	virtual bool HitTest(Gdiplus::Point pos) = 0;
	/** See if drawable is movable
	* \return true if is moveable */
	virtual bool IsMovable() {return false;}
	void Move(Gdiplus::Point delta);

	void virtual SetTimeline(CTimeline * timeline);

	void virtual SetKeyframe();

	void virtual GetKeyframe();

	void virtual DeleteKeyframe();

	/** Get the drawable name
	* \returns Drawable name */
	std::wstring GetName() const { return mName; }

	/** The Drawable position
	* \returns The drawable position as a point */
	Gdiplus::Point GetPosition() const { return mPosition; }

	/** The drawable position
	* \param pos The new drawable position */
	void SetPosition(Gdiplus::Point pos) { mPosition = pos; }

	/** Get the rotation angle in radians
	* \returns The rotation angle in radians*/
	double GetRotation() const { return mRotation; }

	/** Set the rotation angle in radians
	* \param rot The new rotation angle in radians*/
	void SetRotation(double rot) { mRotation = rot; }

	/** Set Parent
	* \param parent New parent of drawable */
	void SetParent(CDrawable* parent) { mParent = parent; }

	/** The drawables parent
	* \returns The parentof drawable as a pointer  */
	CDrawable* GetParent() const { return mParent; }

	/** The angle animation channel
	* \returns Pointer to animation channel */
	CAnimChannelAngle *GetAngleChannel() { return &mChannel; }

protected:
	CDrawable(const std::wstring &name);
	Gdiplus::Point RotatePoint(Gdiplus::Point point, double angle);

	/// The actual postion in the drawing
	Gdiplus::Point mPlacedPosition= Gdiplus::Point(0, 0);
	/// The actual rotation in the drawing
	double mPlacedR = 0;

private:
	/// The position of this drawable relative to its parent
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);
	///name of drawable
	std::wstring mName;
	/// The rotation of this drawable relative to its parent
	double mRotation = 0;

	/// The actor using this drawable
	CActor *mActor = nullptr;

	/// The children of drawable
	std::vector<std::shared_ptr<CDrawable>> mChildren;
	/// The parent of this drawable
	CDrawable *mParent = nullptr;

	/// The animation channel for animating the angle of this drawable
	CAnimChannelAngle mChannel;
};

