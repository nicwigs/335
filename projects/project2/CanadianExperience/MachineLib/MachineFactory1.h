/**
 * \file MachineFactory1.h
 *
 * \author Nic Wiggins
 *
 * Class that creates machine1 - Dr.Owens Machine
 */
#pragma once
#include <memory>
class CWorkingMachine;
/**
 * Factory that makes Machine1.
 */
class CMachineFactory1
{
public:
	CMachineFactory1();
	virtual ~CMachineFactory1();

	std::shared_ptr<CWorkingMachine> CreateMachine();
};

