/*
 * Address.cpp
 *
 *  Created on: 16-Jan-2022
 *      Author: JASON
 */

/* Header files */
#include "Address.h"

Address::Address(std::string street, unsigned short postalCode, std::string cityName, std::string additionalInfo)
	: street{street}, postalCode{postalCode}, cityName{cityName}, additionalInfo{additionalInfo}
{

}

 Address::~Address()
 {

 }

const std::string& Address::getStreet() const
{
	return street;
}

const std::string& Address::getCityName() const
{
	return cityName;
}

unsigned short Address::getPostalCode() const
{
	return postalCode;
}

const std::string& Address::getAdditionalInfo() const
{
	return additionalInfo;
}
