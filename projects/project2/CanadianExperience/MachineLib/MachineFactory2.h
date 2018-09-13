/**
 * \file MachineFactory2.h
 *
 * \author Nic Wiggins
 *
 * This is a factory for my custom machine. 
 */

#pragma once
#include <memory>
class CWorkingMachine;
/**
 * Class that describes a factory for my machine. 
 */
class CMachineFactory2
{
public:
	CMachineFactory2();
	virtual ~CMachineFactory2();

	std::shared_ptr<CWorkingMachine> CreateMachine();
};

