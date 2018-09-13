/**
 * \file PictureFactory.h
 *
 * \author Charles B. Owen
 *
 * A factory class that builds our picture.
 */

#pragma once

#include <memory>

#include "Picture.h"

/**
 * A factory class that builds our picture.
 */
class CPictureFactory
{
public:
    CPictureFactory();
    virtual ~CPictureFactory();

    std::shared_ptr<CPicture> Create();

	/** The drawable machine A
	* \returns Pointer to machineDrawable A */
	std::shared_ptr<CMachineDrawable> GetDrawableMachineA() {return mDrawableMachineA;};
	/** The drawable machine B
	* \returns Pointer to machineDrawable B */
	std::shared_ptr<CMachineDrawable> GetDrawableMachineB() {return mDrawableMachineB;};
	/** The actor machine A
	* \returns Pointer to actor machine A */
	std::shared_ptr<CActor> GetActorMachineA() { return mActorMachineA; };
	/** The actor machine B
	* \returns Pointer to actor machine B */
	std::shared_ptr<CActor> GetActorMachineB() { return mActorMachineB; };

private:
	///Pointer to machineA
	std::shared_ptr<CMachineDrawable> mDrawableMachineA;
	///Pointer to machineB
	std::shared_ptr<CMachineDrawable> mDrawableMachineB;
	///Pointer to machineA
	std::shared_ptr<CActor> mActorMachineA;
	///Pointer to machineB
	std::shared_ptr<CActor> mActorMachineB;
};

