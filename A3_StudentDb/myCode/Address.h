/*
 * Address.h
 *
 *  Created on: 16-Jan-2022
 *      Author: JASON
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_
/* Header files */
#include <string>
/**
 *  \brief Class Address
 *  \details An immutable class.
 */
class Address
{
	/**
	 *  \brief Street address of the student.
	 */
	std::string street;
	/**
	 *  \brief Address postal code information of the student.
	 */
	unsigned short postalCode;
	/**
	 *  \brief Name of the city where the student resides.
	 */
	std::string cityName;
	/**
	 *  \brief Any additional address information about the student.
	 */
	std::string additionalInfo;
public:
	/**
	 *  \brief Parameterized Constructor
	 *  
	 *  \param [in] street Street address of the student.
	 *  \param [in] postalCode Address postal code information of the student.
	 *  \param [in] cityName Name of the city where the student resides. 
	 *  \param [in] additionalInfo Any additional address information about the student.
	 *  
	 */
	Address(std::string street = "N.A.", unsigned short postalCode = 0,
			std::string cityName = "N.A", std::string additionalInfo = "");
	/**
	 *  \brief Destructor.
	 */
	virtual ~Address();
	/**
	 *  \brief Getter function to street address.
	 *  
	 *  \return Returns the street address of the student.
	 *  
	 */
	const std::string& getStreet() const;
	/**
	 *  \brief Getter function to postal code.
	 *  
	 *  \return Returns the postal code of the student.
	 *  
	 */
	unsigned short getPostalCode() const;
	/**
	 *  \brief Getter function to City Name..
	 *  
	 *  \return Returns the city name of the student.
	 *  
	 */
	const std::string& getCityName() const;
	/**
	 *  \brief Getter function to Additional Information.
	 *  
	 *  \return Returns the additional information about the student.
	 *  
	 */
	const std::string& getAdditionalInfo() const;
};

#endif /* ADDRESS_H_ */
