/*
 * StudentDb.h
 *
 *  Created on: 16-Jan-2022
 *      Author: JASON
 */

#ifndef STUDENTDB_H_
#define STUDENTDB_H_

#include <map>
#include <memory>
#include <string>
#include "Student.h"
#include "BlockCourse.h"
#include "WeeklyCourse.h"
#include "Course.h"
/**
 * \brief dataFromServer_st			: used to represent the status of reading and processing data from database server.
 * \details INVALID_DATA_RECEIVED	: Data not processed due to incorrect data entry of the student in the database.
 * \details VALID_DATA_RECEIVED		: Data successfully processed and entered in the local database.
 * \details BAD_SERVER_CONNECTION	: Server is down or connection is too bad to process the data.
 */
typedef enum{INVALID_DATA_RECEIVED = 0/**< 0 */, VALID_DATA_RECEIVED = 1/**< 1 */, BAD_SERVER_CONNECTION = 2/**< 2 */} dataFromServer_st;
/**
 *  \brief Class StudentDb
 *  \details Student Database.
 */
class StudentDb
{
private:
	/**
	 *  \brief The mapped entity of a matrikel number to a student with his/her details namely personal details, address and course enrollments.
	 */
	std::map<int, Student> students;
	/**
	 *  \brief The mapped entity of a course key to a course, where the course can be a block or weekly course.
	 */
	std::map<int, std::unique_ptr<const Course>> courses;
	/**
	 *  \brief Method that extracts required number of numeric data from a string containing alphanumeric and special characters.  
	 *  
	 *  \param [in] strData String data that must be processed.
	 *  \param [in] noOfSplits Number of character separated numerical values that must be extracted from a given string.
	 *  \param [in] arrStrExtractedData A pointer to an array of type integer, extracted character seperated numerical values are stored in the array.
	 *  \return Return description
	 *  
	 *  \details Private Helper Function.
	 */
	void extractStrPckdData(std::string strData, unsigned int noOfSplits, int* arrStrExtractedData);
	/**
	 *  \brief This method adds a student into the mapped entity of students of the student database.
	 *  
	 *  \param [in] firstName First Name of the student.
	 *  \param [in] lastName Last Name of the student.
	 *  \param [in] dateOfBirth Date of Birth of the student.
	 *  \param [in] street Street address of the student.
	 *  \param [in] postalCode Address postal code information of the student.
	 *  \param [in] cityName Name of the city where the student resides. 
	 *  \param [in] additionalInfo Any additional address information about the student.
	 */
	void setStudents(std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth,
			std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo);
	/**
	 *  \brief This method adds a course into the mapped entity of courses of the student database.
	 *  
	 *  \param [in] courseKey The identification key of the course to be added.
	 *  \param [in] title The title of the course to be added.
	 *  \param [in] major The major to which the course to be added belongs to.
	 *  \param [in] creditPoints The credit points associated with the course to be added.
	 *  \param [in] startDate Start Date of a block course.
	 *  \param [in] endDate End Date of a block course.
	 *  \param [in] dayOfWeek Conducting day of the course in a week.
	 *  \param [in] startTime Start Time of a course in the day.
	 *  \param [in] endTime End Time of a course in the day.
	 */
	void setCourses(unsigned int courseType, unsigned int courseKey, std::string title, std::string major, float creditPoints,
								Poco::Data::Date startDate, Poco::Data::Date endDate, Poco::DateTime::DaysOfWeek dayOfWeek,
								Poco::Data::Time startTime, Poco::Data::Time endTime);
	/**
	 *  \brief Method that processes the streamed data from the server.
	 *  
	 *  \param [in] jsonData The JSON formatted output that was streamed from the server. 
	 *  
	 *  \return Returns process status of enumerated type 'dataFromServer_st'.
	 *
	 *  \details The method has been implemented to read JSON formatted data only.
	 *  \details The method processes the JSON formatted data to extract information namely, first name, last name, data of birth, street address, postal code, city name and state information as additional information.
	 */
	dataFromServer_st processDataFromServer(std::string jsonData);
public:
	/**
	 *  \brief Default Constructor
	 */
	StudentDb();
	/**
	 *  \brief Destructor
	 */
	virtual ~StudentDb();
	/**
	 *  \brief Method that adds a new course into the mapped entity of 'courses'.
	 *  \details The user is asked to provide : course type (Block/Weekly), course key, course title, major and credit points as basic information.
	 *  \details if course is a block course, then the user is also asked for start date, end date, start time and end time of the course.
	 *  \details if course is a weekly course, then the user is also asked for day of the course in the week, start time and end time of the course.
	 */
	void addNewCourse();
	/**
	 *  \brief Method that lists all the available course in the student database.
	 *  
	 */
	void listCourses();
	/**
	 *  \brief Method that adds a new student into the mapped entity of 'students'.
	 *  \details The user is asked to provide the details of students namely, first and last name, date of birth as day, month and year, 
	 *  address information like street address name, postal code and city name and any additional information for address.
	 */
	void addNewStudent();
	/**
	 *  \brief Method that enrolls a student from the database into a course.
	 *  \details The user is asked to enter the student's matrikel number and the course key of the course that the student must be enrolledn into.
	 */
	void addEnrollment();
	/**
	 *  \brief Method that prints a student's complete information.
	 *  \details The user is asked to enter the matrikel number of the student whose information needs to be printed.
	 *  \details Basic information like personal and address information are printed by default.
	 *  \details Enrollment information of any of the courses is printed only if the student has been enrolled.
	 */
	void printStudent();
	/**
	 *  \brief Method that searches a student in the student database.
	 *  \details The user is asked to provide atleast a part of the string associated with the first or last name or both of the student.
	 *  \details If student is found, then matrikel number, last name and first name are printed, in that order.
	 */
	void searchStudent();
	/**
	 *  \brief Method that updates the details of the student already present in the student database.
	 *  \details Either update the first name of the student OR
	 *  \details Update the last name of the student OR
	 *  \details Update the date of birth of the student OR
	 *  \details Update the address information of the student OR
	 *  \details Remove a course enrollment of the student or Update the grade of the enrolled course of a student.
	 */
	void updateStudent();
	/**
	 *  \brief Method that writes the student information into a file.
	 *  
	 *  \param [in] out A reference to the object of type ostream, that holds the file information where the student
	 *  information has to be written(streamed) into.
	 *  
	 *  \details The method decides if the course stores in the database is a block or weekly course to be written into the file.
	 *  \details It is responsible for invoking the write() function from classes Courses(Blocked/Weekly) and Students in total.
	 */
	void write(std::ostream& out);
	/**
	 *  \brief Method that reads the formatted data from the a file and adds the student and course information into mapped entities of students and courses, respectively.
	 *  
	 *  \param [in] in A reference to the object of type istream, that holds the file information where the student
	 *  information has to be read(streamed) from.
	 *  
	 *  \details Invokling this function first clears the database entities students and courses.
	 */
	void read(std::istream& in);
	/**
	 *  \brief Method that reads data from a server.
	 *  
	 *  \param [in] hostAddress The address of the host.
	 *  \param [in] portNumber Port number of the host.
	 *  
	 *  \return Returns process status of enumerated type 'dataFromServer_st'.
	 *
	 *  \details The method has been implemented to read the data from host 'mnl.de' on port '42424' only.
	 */
	dataFromServer_st readDataFromServer(std::string hostAddress, Poco::UInt16 portNumber);
};

#endif /* STUDENTDB_H_ */
