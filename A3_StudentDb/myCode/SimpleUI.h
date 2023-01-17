/*
 * SimpleUI.h
 *
 *  Created on: 16-Jan-2022
 *      Author: JASON
 */

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_

#include "StudentDb.h"
/**
 *  \brief Pre-processor value to terminate the server connection after a certain number of bad connections.
 */
#define TERMINATE_FOR_BAD_CONNECTION_COUNT 5
/**
 *  \brief Class SimpleUI
 *  \details Interface for a user to the Student Database.
 */
class SimpleUI
{
	/**
	 *  \brief A pointer to the object of type StudentDb
	 */
	StudentDb* dB;

public:
	/**
	 *  \brief Parameterized Constructor.
	 *  
	 *  \param [in] db A reference to the object of type StudentDb
	 */
	SimpleUI(StudentDb& db);
	/**
	 *  \brief Method that allows the user to interact with the Student Database.
	 */
	void run();
};

#endif /* SIMPLEUI_H_ */
