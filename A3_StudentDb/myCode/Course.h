/*
 * Course.h
 *
 *  Created on: 16-Jan-2022
 *      Author: JASON
 */

#ifndef COURSE_H_
#define COURSE_H_

#include <map>
#include <string>
#include <algorithm>
/**
 *  \brief Class Course
 *  \details Required information about a course.
 */
class Course
{
	/**
	 *  \brief A map that associates a character Id to the corresponding the major.
	 *  \details A static member attribute.
	 */
	static std::map<unsigned char, std::string> majorById;
	/**
	 * \brief The identification key of the course.
	 */
	unsigned int courseKey;
	/**
	 *  \brief The title of the course.
	 */
	std::string title;
	/**
	 *  \brief The unique character Id that can be associated to a major.
	 */
	unsigned char major;
	/**
	 *  \brief The credit points associated with the course.
	 */
	float creditPoints;
public:
	/**
	 *  \brief Parameterized Constructor
	 *  
	 *  \param [in] courseKey The identification key of the course to be added.
	 *  \param [in] title The title of the course to be added.
	 *  \param [in] major The major to which the course to be added belongs to.
	 *  \param [in] creditPoints The credit points associated with the course to be added.
	 */
	Course(unsigned int courseKey = 0, std::string title = "N.N", std::string major = "N.N.", float creditPoints = -1.0);
	/**
	 *  \brief Destructor
	 *  \details A pure virtual destructor.
	 */
	virtual ~Course() = 0;
	/**
	 *  \brief Getter function to fetch the course key.
	 *  
	 *  \return Returns the course key.
	 */
	unsigned int getCourseKey() const;
	/**
	 *  \brief Getter function to fetch the title of the course.
	 *  
	 *  \return Returns the title of the course.
	 */
	const std::string& getTitle() const;
		/**
	 *  \brief Getter function to fetch the major of the course information.
	 *  
	 *  \return Returns the the major of the course.
	 */
	const std::string& getMajor() const;
		/**
	 *  \brief Getter function to fetch the credit points of the course.
	 *  
	 *  \return Returns the credits points of the course.
	 */
	float getCreditPoints() const;	
	/**
	 *  \brief Method that prints the course timings.
	 *  
	 *  \details Pure virtual function. Actual implementation exists in the derived classes Block and Weekly courses,
	 *  	 respectively, seperately. 
	 */
	virtual void printCourseTimings() const = 0;
	/**
	 *  \brief Method that writes the course information into a file.
	 *  
	 *  \param [in] out A reference to the object of type ostream, that holds the file information where the course
	 *  information has to be written(streamed) into.
	 *  
	 *  \details It is a virtual function. The function has further been implemented for Block and Weekly courses,
	 *  	 respectively, seperately. 
	 */
	virtual void write(std::ostream& out) const;
};

#endif /* COURSE_H_ */
