/*
 * Course.cpp
 *
 *  Created on: 16-Jan-2022
 *      Author: JASON
 */

#include <iostream>
#include "Course.h"

std::map<unsigned char, std::string> Course::majorById = {
		{'A', "AUTOMATION"}, {'C', "COMMUNICATION"}, {'E', "EMBEDDED SYSTEMS AND MICROELECTRONICS"}, {'P', "POWER"}
};

Course::Course(unsigned int courseKey, std::string title, std::string major, float creditPoints)
	: courseKey{courseKey}, creditPoints{creditPoints}
{
	transform(title.begin(), title.end(), title.begin(), ::toupper);
	this->title =  title;
	transform(major.begin(), major.end(), major.begin(), ::toupper);
	this->major = *major.begin();
}

Course::~Course()
{

}

unsigned int Course::getCourseKey() const
{
	return this->courseKey;
}

const std::string& Course::getTitle() const
{
	return this->title;
}

const std::string& Course::getMajor() const
{
		return this->majorById.at(this->major);
}

float Course::getCreditPoints() const
{
	return this->creditPoints;
}

void Course::write(std::ostream& out) const
{
	out << this->courseKey << ";" << this->title << ";" << majorById.at(this->major) << ";" <<  this->creditPoints << ";";
}
