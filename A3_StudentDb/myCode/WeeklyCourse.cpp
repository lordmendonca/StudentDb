/*
 * WeeklyCourse.cpp
 *
 *  Created on: 19-Jan-2022
 *      Author: JASON
 */

#include <iostream>
#include "WeeklyCourse.h"

WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints,
		Poco::DateTime::DaysOfWeek dayOfWeek, Poco::Data::Time startTime, Poco::Data::Time endTime) :
			Course{courseKey, title, major, creditPoints},
			dayOfWeek{dayOfWeek}, startTime{startTime}, endTime{endTime}
{

}

WeeklyCourse::~WeeklyCourse()
{
	
}

void WeeklyCourse::printCourseTimings() const
{
	std::cout << "Day of the Week : " << this->dayOfWeek << std::endl;
	std::cout << "Start Time : " << this->startTime.hour() << ":" << this->startTime.minute() << std::endl;
	std::cout << "End Time : " << this->endTime.hour() << ":" << this->endTime.minute() << std::endl;
}

void WeeklyCourse::write(std::ostream& out) const
{
	Course::write(out);
	out << this->dayOfWeek << ";"
		<< this->startTime.hour() << ":" << this->startTime.minute() << ";"
		<< this->endTime.hour() << ":" << this->endTime.minute();
}
