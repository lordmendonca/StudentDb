/*
 * Student.cpp
 *
 *  Created on: 16-Jan-2022
 *      Author: JASON
 */

#include <iostream>
#include "Student.h"

unsigned int Student::nextMatrikelNumber = 100000;

void Student::setNextMatrikelNumber(unsigned int newMatrikelNumber)
{
	nextMatrikelNumber = newMatrikelNumber;
}

unsigned int Student::getNextMatrikelNumber()
{
	return nextMatrikelNumber;
}

Student::Student(std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth,
		std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo)
		: matrikelNumber{nextMatrikelNumber}, firstName{firstName}, lastName{lastName},
		  dateOfBirth{dateOfBirth}
{
	nextMatrikelNumber++;
	this->address = new Address(street, postalCode, cityName, additionalInfo);
}

Student::~Student()
{

}

void Student::setEnrollment(const Course* course, std::string semester)
{
	transform(semester.begin(), semester.end(), semester.begin(), ::toupper);
	this->enrollments.push_back(Enrollment{course, semester});
}

unsigned int Student::getMatrikelNumber() const
{
	return this->matrikelNumber;
}

const std::string& Student::getFirstName() const
{
	return this->firstName;
}

const std::string& Student::getLastName() const
{
	return this->lastName;
}

const Poco::Data::Date& Student::getDateOfBirth() const
{
	return this->dateOfBirth;
}

const Address* Student::getAddress() const
{
	return address;
}

const std::vector<Enrollment>& Student::getEnrollments() const
{
	return this->enrollments;
}

void Student::updatePersonalData(std::string firstName, std::string lastName, int day, int month, int year)
{
	if("" != firstName)
		this->firstName = firstName;
	if("" != lastName)
		this->lastName = lastName;
	if(NO_DATA_UPDATE != day && NO_DATA_UPDATE != month && NO_DATA_UPDATE != year)
		this->dateOfBirth.assign(year, month, day);
}

void Student::updateAddress(std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo)
{
	delete this->address;
	this->address = new Address(street, postalCode, cityName, additionalInfo);
}

void Student::updateEnrollment(unsigned int courseKey, std::string semester, unsigned char isRemove, float grade)
{
	std::vector<Enrollment> enrollment = this->enrollments;
	std::vector<Enrollment>::iterator enrollmentIterator;
	bool isUpdateDone = false;
	transform(semester.begin(), semester.end(), semester.begin(), ::toupper);
	/* Executed only if course has to be removed from enrollments. */
	if('Y' == isRemove)
	{
		for(enrollmentIterator = enrollment.begin(); enrollmentIterator != enrollment.end(); enrollmentIterator++)
		{
			const Course* theCourse = enrollmentIterator->getCourse();
			if((theCourse->getCourseKey() == courseKey) && (enrollmentIterator->getSemester() == semester))
			{
				enrollment.erase(enrollmentIterator); /* Course Key found then remove enrollment. */
				isUpdateDone = true;
				break;
			}
		}
		if(!isUpdateDone)
			std::cout << "Student was never enrolled in the course with key " << courseKey << " in the semester "
											<< semester << "." << std::endl << std::endl;
	}
	/* Executed only when grade of an enrolled course has to be updated. */
	if((-1.0) != grade)
	{
		for(enrollmentIterator = enrollment.begin(); enrollmentIterator != enrollment.end(); enrollmentIterator++)
		{
			const Course* theCourse = enrollmentIterator->getCourse();
			if((theCourse->getCourseKey() == courseKey) && (enrollmentIterator->getSemester() == semester))
			{
				enrollmentIterator->setGrade(grade); /* Course Key not found then set the grade.*/
				isUpdateDone = true;
				break;
			}
		}
		if(!isUpdateDone)
			std::cout << "Student was either not enrolled for the course with key " << courseKey << " or in that semester of "
											<< semester << " and therefore not graded." << std::endl << std::endl;

	}
	this->enrollments = enrollment;


}

void Student::write(std::ostream& out) const
{
	out << this->matrikelNumber << ";" << this->firstName << ";" << this->lastName << ";"
			<< this->dateOfBirth.day() << "." << this->dateOfBirth.month() << "." << this->dateOfBirth.year() << ";"
			<< this->address->getStreet() << ";" << this->address->getPostalCode() << ";"
			<< this->address->getCityName() << ";" << this->address->getAdditionalInfo();
}
