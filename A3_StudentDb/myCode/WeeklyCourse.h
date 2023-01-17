/*
 * WeeklyCourse.h
 *
 *  Created on: 19-Jan-2022
 *      Author: JASON
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

#include <Poco/DateTime.h>
#include <Poco/Data/Time.h>
#include "Course.h"
/**
 *  \brief Class WeeklyCourse derived from Class Course
 *  \details Required information about a Weekly course.
 */
class WeeklyCourse: public Course
{
	/**
	 *  \brief Conducting day of the course in a week.
	 */
	Poco::DateTime::DaysOfWeek dayOfWeek;
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
	 *  \param [in] courseKey The identification key of the weekly course to be added.
	 *  \param [in] title The title of the weekly course to be added.
	 *  \param [in] major The major to which the weekly course to be added belongs to.
	 *  \param [in] creditPoints The credit points associated with the weekly course to be added.
	 *  \param [in] dayOfWeek Conducting day of the course in a week.
	 *  \param [in] startTime Start Time of a weekly course in the day.
	 *  \param [in] endTime End Time of a weekly course in the day.
	 *  
	 */
	WeeklyCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints,
				Poco::DateTime::DaysOfWeek dayOfWeek,
				Poco::Data::Time startTime = Poco::Data::Time{0,0,0}, Poco::Data::Time endTime = Poco::Data::Time{0,0,0});
	/**
	 *  \brief Destructor
	 */
	virtual ~WeeklyCourse();
	/**
	 *  \brief Method that prints the course timings of a weekly course.
	 *  \details It completely implements this function for the base class.
	 *  
	 */
	void printCourseTimings() const;
	/**
	 *  \brief Method that writes the weekly course information into a file.
	 *  
	 *  \param [in] out A reference to the object of type ostream, that holds the file information where the block course
	 *  information has to be written(streamed) into.
	 *  
	 *  \details This function is further implemented from the base class virtual funtion.
	 *  
	 */
	void write(std::ostream& out) const;
};

#endif /* WEEKLYCOURSE_H_ */
