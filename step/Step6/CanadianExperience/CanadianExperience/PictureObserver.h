/**
 * \file PictureObserver.h
 *
 * \author Nic Wiggins
 *
 * Observer base class for a picture.
 */

#pragma once

#include <memory>

class CPicture;

 /**
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
class CPictureObserver
{
public:
	virtual ~CPictureObserver();

	/// Copy Constructor (Disabled)
	CPictureObserver(const CPictureObserver &) = delete;
	/// Assignment Operator (Disabled)
	void operator=(const CPictureObserver &) = delete;

	/// This function is called to update any observers
	virtual void UpdateObserver() = 0;

	void SetPicture(std::shared_ptr<CPicture> picture);

	/**
	* Gets Picture object
	*\return mPicture the picture being observed. 
	*/
	std::shared_ptr<CPicture> GetPicture() { return mPicture; };

protected:
	CPictureObserver();

private:
	/// Picture we are observing
	std::shared_ptr<CPicture> mPicture;

};

