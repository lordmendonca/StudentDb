/*
 * Enrollment.cpp
 *
 *  Created on: 16-Jan-2022
 *      Author: JASON
 */

#include <iostream>
#include "Enrollment.h"

Enrollment::Enrollment(const Course* course, std::string semester, float grade)
	: grade{grade}, semester{semester}, course{course}
{

}

Enrollment::~Enrollment()
{

}

void Enrollment::setGrade(float grade)
{
	this->grade = grade;
}

float Enrollment::getGrade() const
{
	return this->grade;
}

const std::string& Enrollment::getSemester() const
{
	return this->semester;
}

const Course*& Enrollment::getCourse()
{
	return this->course;
}
