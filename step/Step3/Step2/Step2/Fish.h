/**
 * \file Fish.h
 *
 * \author Nic Wiggins
 *
 * A class that describes a fish
 */

#pragma once
#include "Item.h"

 /**
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class CFish : public CItem
{
public:
	

	virtual ~CFish();

	void Update(double elapsed);

	/// Default constructor (disabled)
	CFish() = delete;

	/// Copy constructor (disabled)
	CFish(const CFish &) = delete;

	virtual std::shared_ptr<xmlnode::CXmlNode> 
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;


protected:
	CFish(CAquarium * aquarium, const std::wstring & filename);

	/// Set the x speed of the fish
	/// \param speed New X Speed
	void SetSpeedX(double speed) { mSpeedX = speed; }

	/// Set the Y speed of the fish
	/// \param speed New Y Speed
	void SetSpeedY(double speed) { mSpeedY = speed; }

private:
	/// Fish speed in the X direction
	double mSpeedX;

	/// Fish speed in the Y direction
	double mSpeedY;
};

