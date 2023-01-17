/*
 * Student.h
 *
 *  Created on: 16-Jan-2022
 *      Author: JASON
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>
#include <Poco/DateTime.h>
#include <Poco/Data/Date.h>
#include "Enrollment.h"
#include "Address.h"
/**
 *  \brief Pre-processor value used to identify that some data for student was not updated.
 */
#define NO_DATA_UPDATE -1
/**
 *  \brief Class Student
 *  \details Required information for a student's entry into the student data base.
 */
class Student
{
	/**
	 *  \brief The next available matrikel number to be assigned to the student.
	 *  \details This is a static member attribute of this class.
	 */
	static unsigned int nextMatrikelNumber;
	/**
	 *  \brief The Matrikel Number of the student.
	 */
	unsigned int matrikelNumber;
	/**
	 *  \brief The first name of the student.
	 */
	std::string firstName;
	/**
	 *  \brief The last name of the student.
	 */
	std::string lastName;
	/**
	 *  \brief The date of birth of the student.
	 */
	Poco::Data::Date dateOfBirth;
    /**
     * \brief vector (collected data) of all the course enrollments of a student.
	 * @link aggregationByValue 
     */
	std::vector<Enrollment> enrollments;
    /**
     * \brief Pointer to the type Address that has the address information of a student.
	 * @link aggregationByValue 
     */
	Address* address;
public:
	/**
	 *  \brief Getter function to fetch the next available matrikel number for the student.
	 *  
	 *  \return Returns the next available matrikel number for the student.
	 *  
	 *  \details This is a static member function of this class.
	 */
	static unsigned int getNextMatrikelNumber();
	/**
	 *  \brief Setter function that sets the next available matrikel number for the student.
	 *  
	 *  \param [in] newMatrikelNumber The matrikel number that must be available to be assigned to the next student 
	 *  who will be enrolled.
	 *  
	 *  \details This is a static member function of this class.
	 */
	static void setNextMatrikelNumber(unsigned int newMatrikelNumber);
	/**
	 *  \brief Parameterized Constructor
	 *  
	 *  \param [in] firstName First Name of the student.
	 *  \param [in] lastName Last Name of the student.
	 *  \param [in] dateOfBirth Date of Birth of the student.
	 *  \param [in] street Street address of the student.
	 *  \param [in] postalCode Address postal code information of the student.
	 *  \param [in] cityName Name of the city where the student resides. 
	 *  \param [in] additionalInfo Any additional address information about the student.
	 *  
	 *  \details The address related information is required and passed onto the immutable class Address throught this class.
	 */
	Student(std::string firstName = "N.N.", std::string lastName = "N.N.", Poco::Data::Date dateOfBirth = Poco::Data::Date{1970,1,1},
			std::string street = "N.A.", unsigned short postalCode = 0,
			std::string cityName = "N.A", std::string additionalInfo = "");
	/**
	 *  \brief Destructor
	 */
	virtual ~Student();
	/**
	 *  \brief Set the enrollment of a course for the student
	 *  
	 *  \param [in] course Pointer to the type Course having the complete course information.
	 *  \param [in] semester Semester in which the course must be enrolled.
	 */
	void setEnrollment(const Course* course, std::string semester);
	/**
	 *  \brief Getter function to student's first name.
	 *  
	 *  \return Returns the first name of the student.
	 */
	const std::string& getFirstName() const;
	/**
	 *  \brief Getter function to student's last name.
	 *  
	 *  \return Returns the last name of the student.
	 */
	const std::string& getLastName() const;
	/**
	 *  \brief Getter function to student's matrikel number.
	 *  
	 *  \return Returns the matrikel number of the student.
	 */
	unsigned int getMatrikelNumber() const;
	/**
	 *  \brief Getter function to student's date of birth.
	 *  
	 *  \return Returns the date of birth of the student.
	 */
	const Poco::Data::Date& getDateOfBirth() const;
	/**
	 *  \brief Getter function to pointer object of type Address.
	 *  
	 *  \return Returns the pointer to the object member attribute 'address' of type Address..
	 */
	const Address* getAddress() const;
	/**
	 *  \brief Getter function to fetch the student course enrollments.
	 *  
	 *  \return Returns all the course enrollments of a student.
	 */
	const std::vector<Enrollment>& getEnrollments() const;
	/**
	 *  \brief Updates the personal data of a student as described in the parameters list.
	 *  
	 *  \param [in] firstName First Name of the student.
	 *  \param [in] lastName Last Name of the student.
	 *  \param [in] day  Day of Birth of the student.
	 *  \param [in] month  Month of Birth of the student.
	 *  \param [in] year  Year of Birth of the student.
	 */
	void updatePersonalData(std::string firstName, std::string lastName, int day, int month, int year);
	/**
	 *  \brief Updates the address information of a student.
	 *  
	 *  \param [in] street Street address of the student.
	 *  \param [in] postalCode Address postal code information of the student.
	 *  \param [in] cityName Name of the city where the student resides. 
	 *  \param [in] additionalInfo Any additional address information about the student.
	 */
	void updateAddress(std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo);
	/**
	 *  \brief Updates a course enrollment information of a student.
	 *  
	 *  \param [in] courseKey The course enrollment information that must be accessed is uniquely done through the course key.
	 *  \param [in] semester The semester in which the course was enrolled for the student.
	 *  \param [in] isRemove Character driven information whether the course has to be removed or only updated. ['Y' for removing enrollment]
	 *  \param [in] grade The grade that has to be assigned to the enrolled course of the student, identified by course key.
	 */
	void updateEnrollment(unsigned int courseKey, std::string semester, unsigned char isRemove, float grade);
	/**
	 *  \brief Method that writes the student information into a file.
	 *  
	 *  \param [in] out A reference to the object of type ostream, that holds the file information where the student
	 *  information has to be written(streamed) into.
	 */
	virtual void write(std::ostream& out) const;
};

#endif /* STUDENT_H_ */
