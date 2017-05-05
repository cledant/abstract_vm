/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:23:40 by cledant           #+#    #+#             */
/*   Updated: 2017/05/05 11:05:06 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.hpp"

OperandFactory::OperandFactory(void)
{
}

OperandFactory::~OperandFactory(void)
{
}

IOperand const		*OperandFactory::createInt16(std::string const &value) const
{
	int			convert;

	convert = std::stoi(value, nullptr);
	if (convert > std::numeric_limits<short int>::max())
		throw std::overflow_error("Creating this variable would cause an overflow");
	else if (convert < std::numeric_limits<short int>::min())
		throw std::underflow_error("Creating this variable would cause an underflow");
	return (new OperandInt16(static_cast<short int>(convert)));
}

OperandFactory::OverflowException::OverflowException(void)
{
	this->_msg = "Creating this variable would cause an overflow !";
}

OperandFactory::OverflowException::~OverflowException(void) throw()
{
}

OperandFactory::OverflowException::OverflowException(OverflowException const &src)
{
	this->_msg = src._msg.c_str();
}

OperandFactory::OverflowException		&OperandFactory::OverflowException::
											operator=(OverflowException const &rhs)
{	
	this->_msg = rhs._msg.c_str();
	return (*this);
}

const char								*OperandFactory::OverflowException::what(
											void) const throw()
{
	return (this->_msg.c_str());
}

OperandFactory::UnderflowException::UnderflowException(void)
{
	this->_msg = "Creating this variable would cause an underflow !";
}

OperandFactory::UnderflowException::~UnderflowException(void) throw()
{
}

OperandFactory::UnderflowException::UnderflowException(UnderflowException const &src)
{
	this->_msg = src._msg.c_str();
}

OperandFactory::UnderflowException	&OperandFactory::UnderflowException::operator=(
										UnderflowException const &rhs)
{	
	this->_msg = rhs._msg.c_str();
	return (*this);
}

const char							*OperandFactory::UnderflowException::what(void)
										const throw()
{
	return (this->_msg.c_str());
}
