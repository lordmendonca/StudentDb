/*
 * StudentDb.cpp
 *
 *  Created on: 16-Jan-2022
 *      Author: JASON
 */

#include <iostream>
#include <typeinfo>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/StreamCopier.h>
#include "StudentDb.h"

StudentDb::StudentDb()
{

}

StudentDb::~StudentDb()
{

}

void StudentDb::extractStrPckdData(std::string strData, unsigned int noOfSplits, int* arrStrExtractedData)
{
	unsigned int idxArr = 0;
    arrStrExtractedData[idxArr] = 0;
    for (unsigned int idxStr = 0; (idxStr < strData.length()); idxStr++)
    {
        if (isdigit(strData[idxStr]))
        {
        	/* Decimal conversion of extracted numbers. */
			arrStrExtractedData[idxArr] = arrStrExtractedData[idxArr] * 10 + (strData[idxStr] - 48);
        }
        else
        {
        	idxArr++;
        	if(idxArr < noOfSplits) /* Extract only required number of character separated numerical chunks.*/
        		arrStrExtractedData[idxArr] = 0;
        	else
        		break; /* Extract only required number of character separated numerical chunks.*/
        }
    }
}

void StudentDb::setStudents(std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth,
		std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo)
{
	unsigned int nextMatrikelNumber = Student::getNextMatrikelNumber();
	this->students.emplace(nextMatrikelNumber,
			Student{firstName,lastName,dateOfBirth,street,postalCode,cityName,additionalInfo});
}

void StudentDb::setCourses(unsigned int courseType, unsigned int courseKey, std::string title, std::string major, float creditPoints,
		Poco::Data::Date startDate, Poco::Data::Date endDate, Poco::DateTime::DaysOfWeek dayOfWeek,
		Poco::Data::Time startTime, Poco::Data::Time endTime)
{
	if('B' == courseType || 'b' == courseType)
	{
		/* Course is a block course. */
		BlockCourse* blockCoursePtr = new BlockCourse(courseKey, title, major, creditPoints, startDate, endDate, startTime, endTime);
		const Course* coursePtr = dynamic_cast<const Course*> (blockCoursePtr);
		this->courses.insert(std::pair<int,std::unique_ptr<const Course>>(courseKey,coursePtr));
	}
	else if('W' == courseType || 'w' == courseType)
	{
		/* Course is a weekly course. */
		WeeklyCourse* weeklyCoursePtr = new WeeklyCourse(courseKey, title, major, creditPoints, dayOfWeek, startTime, endTime);
		const Course* coursePtr = dynamic_cast<const Course*> (weeklyCoursePtr);
		this->courses.insert(std::pair<int,std::unique_ptr<const Course>>(courseKey,coursePtr));
	}
}

void StudentDb::addNewCourse()
{
	std::cout << std::endl;
	unsigned char courseType;
	unsigned int courseKey;
	std::string title;
	std::string major;
	float creditPoints;

	std::cout << "[BlockCourse] / [WeeklyCourse] " << std::endl;
	std::cout << "Enter Course Type [B/W]: ";
	std::cin >> courseType;

	std::cout << "Enter the Course Key : ";
	std::cin >> courseKey;

	std::cin.ignore();

	std::cout << "Enter the Course Title : ";
	std::getline(std::cin, title);

	std::cout << "Offered majors are : Automation, Communication, Embedded Systems and Microelectronics, and Power." << std::endl;
	std::cout << "Enter the major : ";
	std::getline(std::cin, major);

	std::cout << "Enter the credit points of the course : ";
	std::cin >> creditPoints;

	std::cin.ignore();

	std::string strCourseTimingsData;
	int arrCourseTimingsData[3];
	int dayOfTheWeek;
	Poco::Data::Date startDate;
	Poco::Data::Date endDate;
	Poco::DateTime::DaysOfWeek dayOfWeek;

	if('B' == courseType || 'b' == courseType)
	{
		/* Course is a block course. */
		std::cout << "Enter the Start Date of the Course (dd.mm.yyyy): " << std::endl;
		std::getline(std::cin, strCourseTimingsData);
		this->extractStrPckdData(strCourseTimingsData,3,arrCourseTimingsData);
		try
		{
			/* Extracted and then assigned in the order of year, month, day as per the syntax. */
			startDate.assign(arrCourseTimingsData[2], arrCourseTimingsData[1], arrCourseTimingsData[0]);
		}
		catch(std::exception& e)
		{
			std::cout << "Date invalid. Non-zero entry expected with digit limit provided in the parenthesis." << std::endl;
			std::cout << "Enter the Start Date of the Course ([1,28/29/30/31].[1,12].[1,9999]): " << std::endl;
			std::getline(std::cin, strCourseTimingsData);
			this->extractStrPckdData(strCourseTimingsData,3,arrCourseTimingsData);
			/* Extracted and then assigned in the order of year, month, day as per the syntax. */
			startDate.assign(arrCourseTimingsData[2], arrCourseTimingsData[1], arrCourseTimingsData[0]);
		}
		std::cout << "Enter the End Date of the Course (dd.mm.yyyy): " << std::endl;
		std::getline(std::cin, strCourseTimingsData);
		this->extractStrPckdData(strCourseTimingsData,3,arrCourseTimingsData);
		try
		{
			/* Extracted and then assigned in the order of year, month, day as per the syntax. */
			endDate.assign(arrCourseTimingsData[2], arrCourseTimingsData[1], arrCourseTimingsData[0]);
		}
		catch(std::exception& e)
		{
			std::cout << "Date invalid. Non-zero entry expected with digit limit provided in the parenthesis." << std::endl;
			std::cout << "Enter the End Date of the Course ([1,28/29/30/31].[1,12].[1,9999]): " << std::endl;
			std::getline(std::cin, strCourseTimingsData);
			this->extractStrPckdData(strCourseTimingsData,3,arrCourseTimingsData);
			/* Extracted and then assigned in the order of year, month, day as per the syntax. */
			endDate.assign(arrCourseTimingsData[2], arrCourseTimingsData[1], arrCourseTimingsData[0]);
		}
	}
	else if('W' == courseType || 'w' == courseType)
	{
		/* Course is a weekly course. */
		std::cout << "Enter the Week of the Day of the Course : " << std::endl;
		std::cout << "(dayOfWeek)<<";
		std::cin >> dayOfTheWeek;
		try
		{
			dayOfWeek = static_cast<Poco::DateTime::DaysOfWeek> (dayOfTheWeek);
		}
		catch(std::exception& e)
		{
			std::cout << "Day of the Week invalid. (Sunday = 0), (Monday = 1), ...., (Saturday = 6) " << std::endl;
			std::cout << "Enter the Week of the Day of the Course : " << std::endl;
			std::cout << "(dayOfWeek)<<";
			std::cin >> dayOfTheWeek;
			dayOfWeek = static_cast<Poco::DateTime::DaysOfWeek> (dayOfTheWeek);
		}
		std::cin.ignore();
	}
	else
	{
		std::cout << "Invalid Selection." << std::endl;
	}

	Poco::Data::Time startTime;
	Poco::Data::Time endTime;
	std::cout << "Enter the Start Time of the Course (HH:MM): " << std::endl;
	std::getline(std::cin, strCourseTimingsData);
	this->extractStrPckdData(strCourseTimingsData,2,arrCourseTimingsData);
	try
	{
		/* Extracted and then assigned in the order of hours and minutes as per the syntax. */
		startTime.assign(arrCourseTimingsData[0], arrCourseTimingsData[1], 0);
	}
	catch(std::exception& e)
	{
		std::cout << "Time invalid. Entry expected with digit limit provided in the parenthesis." << std::endl;
		std::cout << "Enter the Start Time of the Course ([0,23]:[0,59]): " << std::endl;
		std::getline(std::cin, strCourseTimingsData);
		this->extractStrPckdData(strCourseTimingsData,2,arrCourseTimingsData);
		/* Extracted and then assigned in the order of hours and minutes as per the syntax. */
		startTime.assign(arrCourseTimingsData[0], arrCourseTimingsData[1], 0);
	}
	std::cout << "Enter the End Time of the Course (HH:MM): " << std::endl;
	std::getline(std::cin, strCourseTimingsData);
	this->extractStrPckdData(strCourseTimingsData,2,arrCourseTimingsData);
	try
	{
		/* Extracted and then assigned in the order of hours and minutes as per the syntax. */
		endTime.assign(arrCourseTimingsData[0], arrCourseTimingsData[1], 0);
	}
	catch(std::exception& e)
	{
		std::cout << "Time invalid. Entry expected with digit limit provided in the parenthesis." << std::endl;
		std::cout << "Enter the Start Time of the Course ([0,23]:[0,59]): " << std::endl;
		std::getline(std::cin, strCourseTimingsData);
		this->extractStrPckdData(strCourseTimingsData,2,arrCourseTimingsData);
		/* Extracted and then assigned in the order of hours and minutes as per the syntax. */
		endTime.assign(arrCourseTimingsData[0], arrCourseTimingsData[1], 0);
	}

	this->setCourses(courseType, courseKey, title, major, creditPoints, startDate, endDate, dayOfWeek, startTime, endTime);

}

void StudentDb::listCourses()
{
	std::cout << std::endl;
	std::map<int, std::unique_ptr<const Course>>::iterator coursesIterator;
	for(coursesIterator = this->courses.begin(); coursesIterator != this->courses.end(); coursesIterator++)
	{
		std::cout << "Course Key : " << coursesIterator->second->getCourseKey() << std::endl;
		std::cout << "Course Title : " << coursesIterator->second->getTitle() << std::endl;
		std::cout << "Course Major : " << coursesIterator->second->getMajor() << std::endl;
		std::cout << "Course Credit Points : " << coursesIterator->second->getCreditPoints() << std::endl;
		coursesIterator->second->printCourseTimings();
		std::cout << std::endl;
	}
}

void StudentDb::addNewStudent()
{
	std::cout << std::endl;
	std::string firstName;
	std::string lastName;
	std::string strDateOfBirth;
	int arrDateOfBirth[3] = {0};
	Poco::Data::Date dateOfBirth;
	std::string street;
	unsigned int inputPostalCode;
	unsigned short postalCode;
	std::string cityName;
	std::string additionalInfo;

	std::cout << "Enter Student's First Name : ";
	std::getline(std::cin, firstName);

	std::cout << "Enter Student's Last Name : ";
	std::getline(std::cin, lastName);

	std::cout << "Enter Student's Date of Birth (dd.mm.yyyy): " << std::endl;
	std::getline(std::cin, strDateOfBirth);
	this->extractStrPckdData(strDateOfBirth,3,arrDateOfBirth);
	/* Extracted and then assigned in the order of year, month, day as per the syntax. */
	try
	{
		dateOfBirth.assign(arrDateOfBirth[2], arrDateOfBirth[1], arrDateOfBirth[0]);
	}
	catch(std::exception& e)
	{
		std::cout << "Date invalid. Non-zero entry expected with digit limit provided in the parenthesis." << std::endl;
		std::cout << "Enter Student's Date of Birth ([1,28/29/30/31].[1,12].[1,9999]): " << std::endl;
		std::getline(std::cin, strDateOfBirth);
		this->extractStrPckdData(strDateOfBirth,3,arrDateOfBirth);
		dateOfBirth.assign(arrDateOfBirth[2], arrDateOfBirth[1], arrDateOfBirth[0]);
	}

	std::cout << "Enter Student's Address : " << std::endl;
	std::cout << "Street Name : ";
	std::getline(std::cin, street);

	try
	{
		std::cout << "5-digit Postal Code : ";
		std::cin >> inputPostalCode;
		if(inputPostalCode > 99999 || inputPostalCode <= 0)
			throw inputPostalCode;
		else
			postalCode = inputPostalCode;
	}
	catch(unsigned int& inputPostalCode)
	{
		std::cout << "Postal Code cannot be more than 5-digits or zero." << std::endl;
		std::cout << "5-digit Postal Code : ";
		std::cin >> postalCode;
	}

	std::cin.ignore();

	std::cout << "City Name : ";
	std::getline(std::cin, cityName);;

	std::cout << "Additional Information : ";
	std::getline(std::cin, additionalInfo);
	
	this->setStudents(firstName, lastName, dateOfBirth, street, postalCode, cityName, additionalInfo);
}

void StudentDb::addEnrollment()
{
	std::cout << std::endl;
	unsigned int matrikelNumber;
	unsigned int courseKey;
	std::string semester;

	std::cout << "Enter Student's Matrikel Number : ";
	std::cin >> matrikelNumber;

	if(1 == this->students.count(matrikelNumber))
	{
		std::cout << "Enter Course ID : ";
		std::cin >> courseKey;

		std::cin.ignore();

		if(1 == this->courses.count(courseKey))
		{
			std::cout << "Enter Semester : ";
			std::getline(std::cin, semester);

			std::cout << std::endl;

			Student* student = &(this->students.at(matrikelNumber));
			const Course* course = &(*this->courses.at(courseKey));
	
			bool isEnrolledAlready = 0;
			std::vector<Enrollment> enrollment = student->getEnrollments();
			std::vector<Enrollment>::iterator enrollmentIterator;
			transform(semester.begin(), semester.end(), semester.begin(), ::toupper);
			for(enrollmentIterator = enrollment.begin(); enrollmentIterator != enrollment.end(); enrollmentIterator++)
			{
				const Course* newCourse = enrollmentIterator->getCourse();
				if((newCourse->getCourseKey() == courseKey) && (enrollmentIterator->getSemester() == semester))
				{
					std::cout << "Student has been enrolled to the course with key " << courseKey <<
										" already in the semester " << semester << "." << std::endl << std::endl;
					isEnrolledAlready = 1;
					break;
				}
			}
			if(!isEnrolledAlready)
			{
				student->setEnrollment(course, semester);
				std::cout << "Student enrolled to the course with key " << courseKey << " in the semester " << semester << "." << std::endl << std::endl;
			}
		}
		else
			std::cout << "Course Not Found." << std::endl << std::endl;
	}
	else
		std::cout << "Student Not Found." << std::endl << std::endl;
}

void StudentDb::printStudent()
{
	std::cout << std::endl;
	unsigned int matrikelNumber;

	std::cout << "Enter the Student's Matrikel Number : ";
	std::cin >> matrikelNumber;
	if(1 == this->students.count(matrikelNumber))
	{
		Student* student = &(this->students.at(matrikelNumber));
	
		Poco::Data::Date dateOfBirth = student->getDateOfBirth();
	
		std::cout << std::endl << "Student's Personal Information:" << std::endl;
		std::cout << "First Name : " << student->getFirstName() << std::endl;
		std::cout << "Last Name : " << student->getLastName() << std::endl;
		std::cout << "Date of Birth : " << dateOfBirth.day() << "."
										<< dateOfBirth.month() << "."
										<< dateOfBirth.year() << std::endl;
		std::cout << std::endl << "Student's Address Information:" << std::endl;
		std::cout << "Street : " << student->getAddress()->getStreet() << std::endl;
		std::cout << "Postal Code : " << student->getAddress()->getPostalCode() << std::endl;
		std::cout << "City Name : " << student->getAddress()->getCityName() << std::endl;
		std::cout << "Additional Information : " << student->getAddress()->getAdditionalInfo() << std::endl;
	
		std::vector<Enrollment> enrollments = student->getEnrollments();
		if(!enrollments.empty())
		{
			std::cout << std::endl << "Courses Enrolled by the Student:" << std::endl;
			std::vector<Enrollment>::iterator enrollmentIterator;
			for(enrollmentIterator = enrollments.begin(); enrollmentIterator != enrollments.end(); enrollmentIterator++)
			{
				std::cout << std::endl;
				const Course* course = enrollmentIterator->getCourse();
				std::cout << "Course Key : " << course->getCourseKey() << std::endl;
				std::cout << "Course Title : " << course->getTitle() << std::endl;
				std::cout << "Course Major : " << course->getMajor() << std::endl;
				std::cout << "Course Credit Points : " << course->getCreditPoints() << std::endl;
				std::cout << "Semester : " << enrollmentIterator->getSemester() << std::endl;
				std::cout << "Grade : " << enrollmentIterator->getGrade() << std::endl;
			}
		}
		std::cout << std::endl;
	}
	else
		std::cout << "Student Not Found." << std::endl << std::endl;
}

void StudentDb::searchStudent()
{
	std::cout << std::endl;
	std::string nameSubstring;

	std::cout << "Enter the string to be searched : ";
	std::getline(std::cin, nameSubstring);

	transform(nameSubstring.begin(), nameSubstring.end(), nameSubstring.begin(), ::toupper);
	
	unsigned int foundEntities = 0;
	std::map<int, Student>::iterator studentIterator;
	for(studentIterator = this->students.begin(); studentIterator != this->students.end(); studentIterator++)
	{
		std::string firstName = studentIterator->second.getFirstName();
		std::string lastName = studentIterator->second.getLastName();

		transform(firstName.begin(), firstName.end(), firstName.begin(), ::toupper);
		transform(lastName.begin(), lastName.end(), lastName.begin(), ::toupper);

		if(firstName.find(nameSubstring) != std::string::npos || lastName.find(nameSubstring) != std::string::npos)
		{
			foundEntities++;
			std::cout << "Matrikel Number : " << studentIterator->second.getMatrikelNumber() << std::endl;
			std::cout << "Last Name : " << studentIterator->second.getLastName() << std::endl;
			std::cout << "First Name : " << studentIterator->second.getFirstName() << std::endl;
			std::cout << std::endl;
		}
	}
	
	if(0 != foundEntities)
		std::cout << "Found " << foundEntities << " search result(s)." << std::endl << std::endl;
	else
		std::cout << "No search Results." << std::endl << std::endl;
}

void StudentDb::updateStudent()
{
	std::cout << std::endl;
	unsigned int matrikelNumber;

	std::cout << "Enter the Student's Matrikel Number : ";
	std::cin >> matrikelNumber;

	std::cout << std::endl;

	if(1 == this->students.count(matrikelNumber))
	{
		bool isUpdateOver = false;
		std::string updateName;
		unsigned int select;
		std::string strDateOfBirth;
		int arrDateOfBirth[3] = {0};
		Poco::Data::Date dateOfBirth;

		std::string street;
		unsigned int inputPostalCode;
		unsigned short postalCode;
		std::string cityName;
		std::string additionalInfo;

		unsigned int courseKey;
		std::string semester;
		float grade;

		Student* student = &(this->students.at(matrikelNumber));
		while(!isUpdateOver)
		{
			std::cout << "You are now updating data of student with matrikel number " << student->getMatrikelNumber() << "." << std::endl;
			std::cout << "[0] Exit Update Student." << std::endl;
			std::cout << "[1] Update First Name of the Student." << std::endl;
			std::cout << "[2] Update Last Name of the Student." << std::endl;
			std::cout << "[3] Update Date of Birth of the Student." << std::endl;
			std::cout << "[4] Update Address of the Student." << std::endl;
			std::cout << "[5] Update Enrollments of the Student." << std::endl;
			std::cout << "(select)>> ";
			std::cin >> select;

			std::cin.ignore();
			std::cout << std::endl;
			switch(select)
			{
			case 0 :
				isUpdateOver = true;
				break;
			case 1 :
				std::cout << "(first name)>> ";
				std::getline(std::cin, updateName);
				student->updatePersonalData(updateName, "", NO_DATA_UPDATE, NO_DATA_UPDATE, NO_DATA_UPDATE);
				break;
			case 2 :
				std::cout << "(last name)>> ";
				std::getline(std::cin, updateName);
				student->updatePersonalData("", updateName, NO_DATA_UPDATE, NO_DATA_UPDATE, NO_DATA_UPDATE);
				break;
			case 3 :
				std::cout << "(dd.mm.yyyy)>> ";
				std::getline(std::cin, strDateOfBirth);
				this->extractStrPckdData(strDateOfBirth,3,arrDateOfBirth);
				try
				{
					dateOfBirth.assign(arrDateOfBirth[2], arrDateOfBirth[1], arrDateOfBirth[0]);
				}
				catch(std::exception& e)
				{
					std::cout << "Date invalid. Non-zero entry expected with digit limit provided in the parenthesis." << std::endl;
					std::cout << "Enter Student's Date of Birth ([1,28/29/30/31].[1,12].[1,9999]): " << std::endl;
					std::getline(std::cin, strDateOfBirth);
					this->extractStrPckdData(strDateOfBirth,3,arrDateOfBirth);
				}
				/* Extracted and then pased in the order of day, month, year as per the function declaration.. */
				student->updatePersonalData("", "", arrDateOfBirth[0], arrDateOfBirth[1], arrDateOfBirth[2]);
				break;
			case 4 :
				std::cout << "(Street Name)>> ";
				std::getline(std::cin, street);
				std::cout << "(Postal Code)>> ";
				try
				{
					std::cout << "5-digit Postal Code : ";
					std::cin >> inputPostalCode;
					if(inputPostalCode > 99999 || inputPostalCode <= 0)
						throw inputPostalCode;
					else
						postalCode = inputPostalCode;
				}
				catch(unsigned int& inputPostalCode)
				{
					std::cout << "Postal Code cannot be more than 5-digits or zero." << std::endl;
					std::cout << "5-digit Postal Code : ";
					std::cin >> inputPostalCode;
					postalCode = inputPostalCode;
				}
				std::cin.ignore();
				std::cout << "(City Name)>> ";
				std::getline(std::cin, cityName);
				std::cout << "(Additional Information)>> ";
				std::getline(std::cin, additionalInfo);
				student->updateAddress(street, postalCode, cityName, additionalInfo);
				break;
			case 5 :
				std::cout << "Enter the Course Key : ";
				std::cin >> courseKey;
				std::cout << std::endl;
				std::cin.ignore();
				if(1 == this->courses.count(courseKey))
				{
					std::cout << "(Semester)>>";
					std::getline(std::cin, semester);
					std::cout << "[1] Remove Enrollment." << std::endl;
					std::cout << "[2] Update Grade of the Student in the course." << std::endl;
					std::cout << "(select)>> ";
					std::cin >> select;
					std::cout << std::endl;
					switch(select)
					{
					case 1:
						student->updateEnrollment(courseKey, semester, 'Y', -1.0);
						break;
					case 2:
						std::cout << "(Grade)>> ";
						std::cin >> grade;
						student->updateEnrollment(courseKey, semester, 'N', grade);
						break;
					default :
						std::cout << "Invalid Selection." << std::endl << std::endl;
						break;
					}
				}
				else
					std::cout << "Course with key " << courseKey << " does not exists in the database." << std::endl << std::endl;
				break;
			default :
				std::cout << "Not a valid selection." << std::endl << std::endl;
				break;
			}
			std::cout << std::endl;
		}
	}
	else
	{
		std::cout << "Student with Matrikel Number " << matrikelNumber << " not found in the database." << std::endl << std::endl;
	}
}

void StudentDb::write(std::ostream& out)
{
	out << this->courses.size() << "\n";
	std::map<int, std::unique_ptr<const Course>>::iterator coursesIterator;
	for(coursesIterator = this->courses.begin(); coursesIterator != this->courses.end(); coursesIterator++)
	{
		/* Dynamically choose whether the unique pointer to the courses that was stored was block course or weekly course. */
		if(typeid(BlockCourse) == typeid(*coursesIterator->second))
		{
			/* When course is a block course. */
			out << "B" << ";";
		}
		else if(typeid(WeeklyCourse) == typeid(*coursesIterator->second))
		{
			/* When course is a weekly course. */
			out << "W" << ";";
		}
		coursesIterator->second->write(out); /* Write the complete course information from the database into the file. */
		out << "\n";
	}

	out << this->students.size() << "\n";
	std::map<int, Student>::iterator studentIterator;
	for(studentIterator = this->students.begin(); studentIterator != this->students.end(); studentIterator++)
	{
		studentIterator->second.write(out); /* Write the complete student information from the database into the file. */
		out << "\n";
	}

	for(studentIterator = this->students.begin(); studentIterator != this->students.end(); studentIterator++)
	{
		std::vector<Enrollment> enrollments = studentIterator->second.getEnrollments();
		if(0 != enrollments.size())
		{
			/*Student Enrollments exist.*/
			out << enrollments.size() << "\n";
			std::vector<Enrollment>::iterator enrollmentIterator;
			for(enrollmentIterator = enrollments.begin(); enrollmentIterator != enrollments.end(); enrollmentIterator++)
			{
				const Course* theCourse = enrollmentIterator->getCourse();
				/* Write the enrollment information from the database into the file. */
				out << studentIterator->second.getMatrikelNumber() << ";" << theCourse->getCourseKey() << ";"
						<< enrollmentIterator->getSemester() << ";" << enrollmentIterator->getGrade() << "\n";
			}
		}
	}
}

void  StudentDb::read(std::istream& in)
{
	/* First the database is cleared. */
	this->students.clear();
	this->courses.clear();

	std::string dataFromFile;
	std::vector<std::string> dataUnderProcess;
	
	/* Add Courses to the database after the line information from file has been read, one-by-one.*/
	unsigned char courseType;
	unsigned int courseKey;
	std::string title;
	std::string major;
	float creditPoints;

	std::string strTime;
	std::vector<std::string> dataTime;
	int hour, minute;
	Poco::Data::Time startTime;
	Poco::Data::Time endTime;

	std::string strDate;
	std::vector<std::string> dataDate;
	int day, month, year;
	Poco::Data::Date startDate;
	Poco::Data::Date endDate;
	Poco::DateTime::DaysOfWeek dayOfWeek;

	std::string copyStrToChar;
	
	getline(in, dataFromFile);
	int noCourses = std::stoi(dataFromFile);
	int countCourses = 0;
	
	while(countCourses < noCourses)
	{
		getline(in, dataFromFile);
		std::stringstream strCoursesStream(dataFromFile);

		while(getline(strCoursesStream, dataFromFile, ';'))
		{
			dataUnderProcess.push_back(dataFromFile);
		}
		
		copyStrToChar = dataUnderProcess.at(0);
		courseType = copyStrToChar[0];
		courseKey = std::stoul(dataUnderProcess[1]);
		title = dataUnderProcess[2];
		major = dataUnderProcess[3];
		creditPoints = std::stof(dataUnderProcess[4]);

		if('B' == courseType)
		{
			/* Start Date information has been formatted with dot (.) as the delimiter. */
			strDate = dataUnderProcess[5];
			std::stringstream strStartDateStream(strDate);

			while(getline(strStartDateStream, strDate, '.'))
			{
				dataDate.push_back(strDate);
			}

			day = std::stoi(dataDate[0]);
			month = std::stoi(dataDate[1]);
			year = std::stoi(dataDate[2]);
			startDate.assign(year, month, day);
			dataDate.clear();

			/* End Date information has been formatted with dot (.) as the delimiter. */
			strDate = dataUnderProcess[6];
			std::stringstream strEndDateStream(strDate);

			while(getline(strEndDateStream, strDate, '.'))
			{
				dataDate.push_back(strDate);
			}

			day = std::stoi(dataDate[0]);
			month = std::stoi(dataDate[1]);
			year = std::stoi(dataDate[2]);
			endDate.assign(year, month, day);
			dataDate.clear();

			/* Start Time information has been formatted with colon (:) as the delimiter. */
			strTime = dataUnderProcess[7];
			std::stringstream strStartTimeStream(strTime);

			while(getline(strStartTimeStream, strTime, ':'))
			{
				dataTime.push_back(strTime);
			}

			hour = std::stoi(dataTime[0]);
			minute = std::stoi(dataTime[1]);
			startTime.assign(hour, minute, 0);
			dataTime.clear();

			/* End Time information has been formatted with colon (:) as the delimiter. */
			strTime = dataUnderProcess[8];
			std::stringstream strEndTimeStream(strTime);

			while(getline(strEndTimeStream, strTime, ':'))
			{
				dataTime.push_back(strTime);
			}

			hour = std::stoi(dataTime[0]);
			minute = std::stoi(dataTime[1]);
			endTime.assign(hour, minute, 0);
			dataTime.clear();

		}
		else if('W' == courseType)
		{
			/* Day of the week. */
			day = std::stoi(dataUnderProcess.at(5));
			dayOfWeek = static_cast<Poco::DateTime::DaysOfWeek> (day);

			/* Start Time information has been formatted with colon (:) as the delimiter. */
			strTime = dataUnderProcess[6];
			std::stringstream strStartTime2Stream(strTime);

			while(getline(strStartTime2Stream, strTime, ':'))
			{
				dataTime.push_back(strTime);
			}

			hour = std::stoi(dataTime[0]);
			minute = std::stoi(dataTime[1]);
			startTime.assign(hour, minute, 0);
			dataTime.clear();

			/* End Time information has been formatted with colon (:) as the delimiter. */
			strTime = dataUnderProcess[7];
			std::stringstream strEndTime2Stream(strTime);

			while(getline(strEndTime2Stream, strTime, ':'))
			{
				dataTime.push_back(strTime);
			}

			hour = std::stoi(dataTime[0]);
			minute = std::stoi(dataTime[1]);
			endTime.assign(hour, minute, 0);
			dataTime.clear();
		}

		/* After extracting all the information from the formatted file, add the course into the database. */
		this->setCourses(courseType, courseKey, title, major, creditPoints, startDate, endDate, dayOfWeek, startTime, endTime);

		dataUnderProcess.clear();
		countCourses++;
	}

	/* Add students to the database after the line information from file has been read, one-by-one.*/

	unsigned int matrikelNumber;
	unsigned int highestMatrikelNumber = 0;
	std::string firstName;
	std::string lastName;
	std::string strDOB;
	std::vector<std::string> dataDOB;
	Poco::Data::Date dateOfBirth;

	std::string street;
	unsigned short postalCode;
	std::string cityName;
	std::string additionalInfo;

	getline(in, dataFromFile);
	int noStudents = std::stoi(dataFromFile);
	int countStudents = 0;

	while(countStudents < noStudents)
	{
		getline(in, dataFromFile);
		std::stringstream strStudentsStream(dataFromFile);

		while(getline(strStudentsStream, dataFromFile, ';'))
		{
			dataUnderProcess.push_back(dataFromFile);
		}

		matrikelNumber = std::stoul(dataUnderProcess[0]);
		Student::setNextMatrikelNumber(matrikelNumber);
		highestMatrikelNumber = (highestMatrikelNumber >= matrikelNumber)? highestMatrikelNumber :
																							matrikelNumber;
		firstName = dataUnderProcess[1];
		lastName = dataUnderProcess[2];

		/* Date of birth information has been formatted with dot (.) as the delimiter. */
		strDOB = dataUnderProcess[3];
		std::stringstream strDOBStream(strDOB);

		while(getline(strDOBStream, strDOB, '.'))
		{
			dataDOB.push_back(strDOB);
		}

		day = std::stoi(dataDOB[0]);
		month = std::stoi(dataDOB[1]);
		year = std::stoi(dataDOB[2]);
		dateOfBirth.assign(year, month, day);
		dataDOB.clear();

		street = dataUnderProcess[4];
		postalCode = std::stoul(dataUnderProcess[5]);
		cityName = dataUnderProcess[6];
		additionalInfo = dataUnderProcess[7];

		/* After extracting all the information from the formatted file, add the student into the database. */
		this->setStudents(firstName, lastName, dateOfBirth, street, postalCode, cityName, additionalInfo);

		dataUnderProcess.clear();
		countStudents++;
	}
	Student::setNextMatrikelNumber(++highestMatrikelNumber);

	/* Add Enrollment(s) of respective students to the database after the line information from file has been read, one-by-one.*/

	std::string semester;
	float grade;

	while(getline(in, dataFromFile))
	{
		int noEnrollments = std::stoi(dataFromFile);
		int countEnrollments = 0;
	
		while(countEnrollments < noEnrollments)
		{
			getline(in, dataFromFile);
			std::stringstream strEnrollmentStream(dataFromFile);
	
			while(getline(strEnrollmentStream, dataFromFile, ';'))
			{
				dataUnderProcess.push_back(dataFromFile);
			}
	
			matrikelNumber = std::stoul(dataUnderProcess[0]);
			courseKey = std::stoul(dataUnderProcess[1]);
			semester = dataUnderProcess[2];
			grade = std::stof(dataUnderProcess[3]);

			/* Check if enrollment is duplication before adding. */
			if(1 == this->students.count(matrikelNumber))
			{
				if(1 == this->courses.count(courseKey))
				{
					Student* student = &(this->students.at(matrikelNumber));
					const Course* course = &(*this->courses.at(courseKey));
	
					bool isEnrolledAlready = 0;
					std::vector<Enrollment> enrollment = student->getEnrollments();
					std::vector<Enrollment>::iterator enrollmentIterator;
					transform(semester.begin(), semester.end(), semester.begin(), ::toupper);
					for(enrollmentIterator = enrollment.begin(); enrollmentIterator != enrollment.end(); enrollmentIterator++)
					{
						const Course* newCourse = enrollmentIterator->getCourse();
						if((newCourse->getCourseKey() == courseKey) && (enrollmentIterator->getSemester() == semester))
						{
							std::cout << "Student has been enrolled to the course with key " << courseKey <<
												" already in the semester " << semester << "." << std::endl << std::endl;
							isEnrolledAlready = 1;
							break;
						}
					}
					if(!isEnrolledAlready)
					{
						student->setEnrollment(course, semester);
						student->updateEnrollment(courseKey, semester, 'N', grade);
					}
				}
				else
					std::cout << "Course Not Found." << std::endl;
			}
			else
				std::cout << "Student Not Found." << std::endl;
	
			dataUnderProcess.clear();
			countEnrollments++;
		}
	}
}


dataFromServer_st StudentDb::readDataFromServer(std::string hostAddress, Poco::UInt16 portNumber)
{
	std::string dataFromSrvr;
	std::vector<std::string> arrDataFromSrvr;
	Poco::Net::SocketAddress socketAddress(hostAddress, portNumber);
	std::cout << "Connecting to .... " << socketAddress.toString() << std::endl; /*Print the host address information. */
	Poco::Net::StreamSocket connectionToHost;
	Poco::Net::SocketStream streamToHost(connectionToHost);
	connectionToHost.connect(socketAddress);
	
	try
	{
		if(!streamToHost)
			std::cout << "Connection to host unsuccessful." << std::endl;
		else
			std::cout << "Connected to host successfully." << std::endl;
	
		streamToHost << "generate"; /* Command to the session connected to the host to generate the database datum. */
		streamToHost.flush(); /* Command being flushed into the session. */
		
		connectionToHost.shutdownSend(); /* Stop sending information to the host. */
	
		while(std::getline(streamToHost, dataFromSrvr))
		{
			arrDataFromSrvr.push_back(dataFromSrvr); /* line-by-line copy of the session that includes the generated datum. */
		}
	
		connectionToHost.shutdownReceive(); /*Stop receiving information from the host. */
	
		streamToHost << "quit"; /* Command to the session connected to the host to terminate the session successfully. */
		streamToHost.flush(); /* Command being flushed into the session. */
	
		connectionToHost.close(); /* Close the connection to the host. */
		/*
		 * Session data that was stored in the 'arrDataFromSrvr', line-by-line :
		 * line 1 : 100 Generating
		 * line 2 : (generated JSON formatted datum from the server)
		 * line 3 : 200 Data generated.
		 */
		dataFromServer_st dataEntry_st = this->processDataFromServer(arrDataFromSrvr.at(1)); /* Only the datum at line 2 is of interest to be processed in the function.*/
	
		return dataEntry_st;
	}
	catch(std::exception& e)
	{
		std::cout << "Received insufficient/incorrect/incomplete data from the server for processing." << std::endl;
		return BAD_SERVER_CONNECTION;
	}
}

dataFromServer_st StudentDb::processDataFromServer(std::string jsonData)
{
	std::string firstName;
	std::string lastName;
	try
	{
		Poco::JSON::Parser dataUnderParsing; /* An object of type Poco::JSON::Parser for reading RFC 4627 compliant JSON from strings. */
		Poco::Dynamic::Var parsedData = dataUnderParsing.parse(jsonData); /* An object of type Poco::Dynamic::Var that allows to store data of different types of data and to convert between these types transparently. */
		Poco::JSON::Object::Ptr extractedJsonData = parsedData.extract<Poco::JSON::Object::Ptr>(); /* A shared pointer of type Poco::JSON::Object::Ptr. */

		/* Extracting sub-data after extracting the main data. Here, 'first name' and 'last name' from 'name'.*/
		Poco::Dynamic::Var mainData = extractedJsonData->get("name");
		Poco::JSON::Object::Ptr extractedSubData = mainData.extract<Poco::JSON::Object::Ptr>();
		firstName = extractedSubData->getValue<std::string>("firstName");
		lastName = extractedSubData->getValue<std::string>("lastName");

		/* Extracting sub-data after extracting the main data. Here, 'year', 'month' and 'date' from 'date of birth'.*/
		Poco::Data::Date dateOfBirth;
		mainData = extractedJsonData->get("dateOfBirth");
		extractedSubData = mainData.extract<Poco::JSON::Object::Ptr>();
		dateOfBirth.assign(	extractedSubData->getValue<int>("year"),
							extractedSubData->getValue<int>("month"),
							extractedSubData->getValue<int>("date"));

		/* Extracting sub-data after extracting the main data. Here, 'street', 'postal code', 'city' and 'state' (additional information) from 'location'.*/
		mainData = extractedJsonData->get("location");
		extractedSubData = mainData.extract<Poco::JSON::Object::Ptr>();
		std::string street =  extractedSubData->getValue<std::string>("street");
		unsigned short postalCode = extractedSubData->getValue<unsigned short>("postCode");
		std::string cityName = extractedSubData->getValue<std::string>("city");
		std::string additionalInfo = extractedSubData->getValue<std::string>("state");
		additionalInfo.append(" State");

		this->setStudents(firstName, lastName, dateOfBirth, street, postalCode, cityName, additionalInfo);

		return VALID_DATA_RECEIVED;
	}
	catch(Poco::SyntaxException& e)
	{
		std::cout << "Student : " << firstName << " " << lastName << " has incorrect entry on server database and hence was not downloaded into local database." << std::endl;
		return INVALID_DATA_RECEIVED;
	}
	catch(Poco::InvalidArgumentException& e)
	{
		std::cout << "Student : " << firstName << " " << lastName << " has incorrect entry on server database and hence was not downloaded into local database." << std::endl;
		return INVALID_DATA_RECEIVED;
	}
	catch(Poco::RangeException& e)
	{
		std::cout << "Student : " << firstName << " " << lastName << " has incorrect entry on server database and hence was not downloaded into local database." << std::endl;
		return INVALID_DATA_RECEIVED;
	}
	catch(std::exception& e)
	{
		std::cout << "Student : " << firstName << " " << lastName << " has incorrect entry on server database and hence was not downloaded into local database." << std::endl;
		return INVALID_DATA_RECEIVED;
	}
}
