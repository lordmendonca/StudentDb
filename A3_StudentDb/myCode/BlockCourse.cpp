/*
 * BlockCourse.cpp
 *
 *  Created on: 19-Jan-2022
 *      Author: JASON
 */

#include <iostream>
#include "BlockCourse.h"

BlockCourse::BlockCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints,
		Poco::Data::Date startDate, Poco::Data::Date endDate, Poco::Data::Time startTime, Poco::Data::Time endTime) :
			Course{courseKey, title, major, creditPoints},
			startDate{startDate}, endDate{endDate}, startTime{startTime}, endTime{endTime}
{

}

BlockCourse::~BlockCourse()
{

}

void BlockCourse::printCourseTimings() const
{
	std::cout << "Start Date : " << this->startDate.day() << "." << this->startDate.month() << "." << this->startDate.year() << std::endl;
	std::cout << "End Date : " << this->endDate.day() << "." << this->endDate.month() << "." << this->endDate.year() << std::endl;
	std::cout << "Start Time : " << this->startTime.hour() << ":" << this->startTime.minute() << std::endl;
	std::cout << "End Time : " << this->endTime.hour() << ":" << this->endTime.minute() << std::endl;
}

void BlockCourse::write(std::ostream& out) const
{
	Course::write(out);
	out << this->startDate.day() << "." << this->startDate.month() << "." << this->startDate.year() << ";"
		<< this->endDate.day() << "." << this->endDate.month() << "." << this->endDate.year() << ";"
		<< this->startTime.hour() << ":" << this->startTime.minute() << ";"
		<< this->endTime.hour() << ":" << this->endTime.minute();
}
