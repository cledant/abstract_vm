/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:23:40 by cledant           #+#    #+#             */
/*   Updated: 2017/05/20 13:28:19 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.hpp"

OperandFactory::OperandFactory(void)
{
}

OperandFactory::~OperandFactory(void)
{
}

IOperand const		*OperandFactory::createInt8(std::string const &value) const
{
	int			convert;
	
	try
	{
		convert = std::stoi(value, nullptr);
	}
	catch (std::exception &e)
	{
		throw OperandFactory::InvalidConversionException();
	}
	if (convert > std::numeric_limits<char>::max())
		throw OperandFactory::OverflowException();
	else if (convert < std::numeric_limits<char>::min())
		throw OperandFactory::UnderflowException();
	return (new OperandInt8(static_cast<char>(convert)));
}

IOperand const		*OperandFactory::createInt16(std::string const &value) const
{
	int			convert;
	
	try
	{
		convert = std::stoi(value, nullptr);
	}
	catch (std::exception &e)
	{
		throw OperandFactory::InvalidConversionException();
	}
	if (convert > std::numeric_limits<short int>::max())
		throw OperandFactory::OverflowException();
	else if (convert < std::numeric_limits<short int>::min())
		throw OperandFactory::UnderflowException();
	return (new OperandInt16(static_cast<short int>(convert)));
}

IOperand const		*OperandFactory::createInt32(std::string const &value) const
{
	int			convert;

	try
	{
		convert = std::stoi(value, nullptr);
	}
	catch (std::exception &e)
	{
		throw OperandFactory::InvalidConversionException();
	}
	if (convert > std::numeric_limits<int>::max())
		throw OperandFactory::OverflowException();
	else if (convert < std::numeric_limits<int>::min())
		throw OperandFactory::UnderflowException();
	return (new OperandInt32(convert));
}

IOperand const		*OperandFactory::createFloat(std::string const &value) const
{
	float		convert;

	try
	{
		convert = std::stof(value, nullptr);
	}
	catch (std::exception &e)
	{
		throw OperandFactory::InvalidConversionException();
	}
	return (new OperandFloat(convert, value));
}

IOperand const		*OperandFactory::createDouble(std::string const &value) const
{
	double		convert;

	try
	{
		convert = std::stod(value, nullptr);
	}
	catch (std::exception &e)
	{
		throw OperandFactory::InvalidConversionException();
	}
	return (new OperandDouble(convert, value));
}

OperandFactory::OverflowException::OverflowException(void)
{
	this->_msg = "Runtime Exception : OperandFactory : Creating this variable would cause an overflow !";
}

OperandFactory::OverflowException::~OverflowException(void) throw()
{
}

OperandFactory::UnderflowException::UnderflowException(void)
{
	this->_msg = "Runtime Exception : OperandFactory : Creating this variable would cause an underflow !";
}

OperandFactory::UnderflowException::~UnderflowException(void) throw()
{
}

OperandFactory::InvalidConversionException::InvalidConversionException(void)
{
	this->_msg = "Runtime Exception : OperandFactory : String to value conversion failed !";
}

OperandFactory::InvalidConversionException::~InvalidConversionException(void) throw()
{
}
