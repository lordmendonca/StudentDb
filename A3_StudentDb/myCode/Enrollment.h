/*
 * Enrollment.h
 *
 *  Created on: 16-Jan-2022
 *      Author: JASON
 */

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

#include <string>
#include "Course.h"
/**
 *  \brief Class Enrollment
 *  \details Required information about an enrollment of a student in a course.
 */
class Enrollment
{
	/**
	 *  \brief Grade of a student in the enrolled course.
	 */
	float grade;
	/**
	 *  \brief Semester of enrollment of the course of the student.
	 */
	std::string semester;
    /**
     * \brief A pointer of type Course that has complete information of the enrolled course.
	 * @link aggregation
     * @supplierCardinality 1
     * @clientCardinality 1..* 
     */
	const Course* course;
public:
	/**
	 *  \brief Parameterized Constructor.
	 *  
	 *  \param [in] course A pointer of type Course that the student has to be enrolled to.
	 *  \param [in] semester The semester of student's enrollment to the course.
	 *  \param [in] grade The grade of the student in the course.
	 */
	Enrollment(const Course* course, std::string semester, float grade = -1.0);
	/**
	 *  \brief Destructor
	 */
	virtual ~Enrollment();
	/**
	 *  \brief Setter Function to grade a student.
	 *  
	 *  \param [in] grade The grade to be assigned to the student in the enrolled course.
	 */
	void setGrade(float grade);
	/**
	 *  \brief Getter Function to read the grade of a student.
	 *  
	 *  \return Returns the grade of the student in the enrolled course.
	 */
	float getGrade() const;
	/**
	 *  \brief Getter Function to read the semester in which the student was enrolled to the course.
	 *  
	 *  \return Returns the semester in which the student was enrolled to the course.
	 */
	const std::string& getSemester() const;
	/**
	 *  \brief Getter Function to read the information about the course that was enrolled.
	 *  
	 *  \return Returns the reference of the pointer to the course that was enrolled.
	 *  
	 *  \details More details
	 */
	const Course*& getCourse();
};

#endif /* ENROLLMENT_H_ */
