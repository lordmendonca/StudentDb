/*
 * SimpleUI.cpp
 *
 *  Created on: 16-Jan-2022
 *      Author: JASON
 */

#include <iostream>
#include <fstream>
#include "SimpleUI.h"

SimpleUI::SimpleUI(StudentDb& dB)
{
	this->dB = &dB;
}

void SimpleUI::run()
{
	unsigned int select;
	/* Object of stream class 'ofstream' to write on files. */
	std::ofstream fileWrite;
	/* Object of stream class 'ifstream' to read from files. */
	std::ifstream fileRead;
	std::string fileName;

	/* Host that must be connected to, in order to fetch the student data. */
	std::string hostAddress = "mnl.de";
	/* Port number of the host. */
	Poco::UInt16 portNumber = 4242;
	unsigned int entriesFromHostCount;
	unsigned int badConnectionCount;
	dataFromServer_st dataEntry_st;

	bool quit = false;

	while(!quit)
	{
		std::cout << "WELCOME TO STUDENT DATABASE" << std::endl;
		std::cout << "[0]	Exit."<< std::endl;
		std::cout << "[1]	Add New Course."<< std::endl;
		std::cout << "[2]	List Courses."<< std::endl;
		std::cout << "[3]	Add New Student."<< std::endl;
		std::cout << "[4]	Add Enrollment."<< std::endl;
		std::cout << "[5]	Print Student."<< std::endl;
		std::cout << "[6]	Search Student."<< std::endl;
		std::cout << "[7]	Update Student."<< std::endl;
		std::cout << "[8]	Write Data into a file."<< std::endl;
		std::cout << "[9]	Read Data from a file."<< std::endl;
		std::cout << "[10]	Add student from Server."<< std::endl;
		std::cout << "(select)>> ";
		std::cin >> select;
		std::cin.ignore();
		switch(select)
		{
		case 0:
			quit = true;
			break;
		case 1:
			this->dB->addNewCourse();
			break;
		case 2:
			this->dB->listCourses();
			break;
		case 3:
			this->dB->addNewStudent();
			break;
		case 4:
			this->dB->addEnrollment();
			break;
		case 5:
			this->dB->printStudent();
			break;
		case 6:
			this->dB->searchStudent();
			break;
		case 7:
			this->dB->updateStudent();
			break;
		case 8:
			std::cout << std::endl;
			std::cout << "Enter the CSV-File Name : ";
			std::getline(std::cin, fileName);
			if(fileName.find(".csv") == std::string::npos)
				fileName.append(".csv");
			try
			{
				/* Open the file for writing while deleting the content previously present. */
				fileWrite.open(fileName, std::ios::out | std::ios::trunc);
				if(fileWrite.is_open())
				{
					this->dB->write(fileWrite);
					std::cout << "File " << fileName << " was successfully written." << std::endl;
				}
				else
					std::cout << "File '" << fileName << "' is already opened. Close the existing instances for the file update." << std::endl;
				fileWrite.close(); /* Close the file. */
			}
			catch(std::exception& e)
			{
				std::cout << "Corrupted data entry found to be exported to a file." << std::endl;
				fileRead.close(); /* Close the file. */
			}
			break;
		case 9:
			std::cout << std::endl;
			std::cout << "Enter the CSV-File Name : ";
			std::getline(std::cin, fileName);
			if(fileName.find(".csv") == std::string::npos)
				fileName.append(".csv");
			try
			{
				/* Open the file for reading. */
				fileRead.open(fileName, std::ios::in);
				if(fileRead.is_open())
				{
					this->dB->read(fileRead);
					std::cout << "File " << fileName << " was successfully read." << std::endl;
				}
				else
					std::cout << "File '" << fileName << "' is not available in your directory." << std::endl;
				fileRead.close(); /* Close the file. */
			}
			catch(std::exception& e)
			{
				std::cout << "File to be imported has corrupted entry/entries." << std::endl;
				fileRead.close(); /* Close the file. */
			}
			break;
		case 10:
			std::cout << std::endl;
			std::cout << "Enter Number of Student Entries :";
			std::cin >> select;
			entriesFromHostCount = 0;
			badConnectionCount = 0;
			std::cout << "SERVER LOG : " << std::endl;
			while(entriesFromHostCount < select)
			{
				dataEntry_st = this->dB->readDataFromServer(hostAddress, portNumber);
				if(VALID_DATA_RECEIVED == dataEntry_st)
				{
					entriesFromHostCount++;
				}
				else if(BAD_SERVER_CONNECTION == dataEntry_st)
				{
					badConnectionCount++;
				}

				if(badConnectionCount == TERMINATE_FOR_BAD_CONNECTION_COUNT)
				{
					std::cout << "Terminated after " << badConnectionCount << " bad server connections" << std::endl;
					break;
				}
			}
			std::cout << entriesFromHostCount << " students were successfully added from the database." << std::endl;
			break;
		default: 
			std::cout << "Invalid Selection." << std::endl;
			break;
		}
		std::cout << std::endl;
	}
}
