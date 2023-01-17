/*
 * BlockCourse.h
 *
 *  Created on: 19-Jan-2022
 *      Author: JASON
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_

#include <Poco/DateTime.h>
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>
#include "Course.h"
/**
 *  \brief Class BlockCourse derived from Class Course
 *  \details Required information about a Block course.
 */
class BlockCourse: public Course
{
	/**
	 *  \brief Start Date of a course.
	 */
	Poco::Data::Date startDate;
	/**
	 *  \brief End Date of a course.
	 */
	Poco::Data::Date endDate;
	/**
	 *  \brief Start Time of a course in the day.
	 */
	Poco::Data::Time startTime;
	/**
	 *  \brief End Time of a course in the day.
	 */
	Poco::Data::Time endTime;
public:
	/**
	 *  \brief Parameterized Constructor
	 *  
	 *  \param [in] courseKey The identification key of the block course to be added.
	 *  \param [in] title The title of the block course to be added.
	 *  \param [in] major The major to which the block course to be added belongs to.
	 *  \param [in] creditPoints The credit points associated with the block course to be added.
	 *  \param [in] startDate Start Date of a block course.
	 *  \param [in] endDate End Date of a block course.
	 *  \param [in] startTime Start Time of a block course in the day.
	 *  \param [in] endTime End Time of a block course in the day.
	 *  
	 */
	BlockCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints,
					Poco::Data::Date startDate = Poco::Data::Date{1970, 1, 1}, Poco::Data::Date endDate = Poco::Data::Date{1970, 1, 1},
					Poco::Data::Time startTime = Poco::Data::Time{0,0,0}, Poco::Data::Time endTime = Poco::Data::Time{0,0,0});
	/**
	 *  \brief Destructor
	 */
	virtual ~BlockCourse();
	/**
	 *  \brief Method that prints the course timings of a block course.
	 *  \details It completely implements this function for the base class.
	 *  
	 */
	void printCourseTimings() const;
	/**
	 *  \brief Method that writes the block course information into a file.
	 *  
	 *  \param [in] out A reference to the object of type ostream, that holds the file information where the block course
	 *  information has to be written(streamed) into.
	 *  
	 *  \details This function is further implemented from the base class virtual funtion.
	 *  
	 */
	void write(std::ostream& out) const;
};

#endif /* BLOCKCOURSE_H_ */
