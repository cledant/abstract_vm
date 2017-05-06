/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFloat.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:55:23 by cledant           #+#    #+#             */
/*   Updated: 2017/05/06 10:34:53 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFloat.hpp"

OperandFloat::OperandFloat(void) : _value(0.f), _str_value("0")
{
	this->_factory = new OperandFactory();
}

OperandFloat::~OperandFloat(void)
{
	delete this->_factory;
}

OperandFloat::OperandFloat(OperandFloat const &src) : _value(src.getValue()), _str_value(src.toString())
{
	this->_factory = new OperandFactory();
}

OperandFloat			&OperandFloat::operator=(OperandFloat const &rhs)
{
	this->_value = rhs.getValue();
	this->_str_value = rhs.toString().c_str();
	return(*this);
}

OperandFloat::OperandFloat(float const value) : _value(value)
{
	this->_factory = new OperandFactory();
	this->_str_value = std::to_string(value);
}

int						OperandFloat::getPrecision(void) const
{
	return (static_cast<int>(this->getType()));
}

eOperandType			OperandFloat::getType(void) const
{
	return (Float);
}

float					OperandFloat::getValue(void) const
{
	return (this->_value);
}

IOperand const			*OperandFloat::operator+(IOperand const &rhs) const
{
	float				result;
	int					fe;
	const IOperand		*op_result;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value + dynamic_cast<const OperandFloat &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandFloat::OverflowException();
	op_result = this->_factory->createOperand(Float, std::to_string(result));
	return (op_result);
}

IOperand const			*OperandFloat::operator-(IOperand const &rhs) const
{
	float				result;
	int					fe;
	const IOperand		*op_result;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value - dynamic_cast<const OperandFloat &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandFloat::OverflowException();
	op_result = this->_factory->createOperand(Float, std::to_string(result));
	return (op_result);
}

IOperand const			*OperandFloat::operator*(IOperand const &rhs) const
{
	float				result;
	int					fe;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandFloat &>(rhs).getValue() == 0.f ||
			this->getValue() == 0.f)
	{
		op_result = this->_factory->createOperand(Float, "0");
		return (op_result);
	}
	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value * dynamic_cast<const OperandFloat &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandFloat::OverflowException();
	else if (fe & FE_UNDERFLOW)
		throw OperandFloat::UnderflowException();
	op_result = this->_factory->createOperand(Float, std::to_string(result));
	return (op_result);
}

IOperand const			*OperandFloat::operator/(IOperand const &rhs) const
{
	float				result;
	int					fe;
	const IOperand		*op_result;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value / dynamic_cast<const OperandFloat &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandFloat::OverflowException();
	else if (fe & FE_UNDERFLOW)
		throw OperandFloat::UnderflowException();
	else if (fe & FE_DIVBYZERO)
		throw OperandFloat::DivideByZeroException();
	else if (fe & FE_INVALID)
		throw OperandFloat::DivideByZeroException();
	op_result = this->_factory->createOperand(Float, std::to_string(result));
	return (op_result);
}

IOperand const			*OperandFloat::operator%(IOperand const &rhs) const
{
	float				result;
	int					fe;
	const IOperand		*op_result;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = std::fmod(this->_value, dynamic_cast<const OperandFloat &>(rhs).getValue());
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandFloat::OverflowException();
	else if (fe & FE_UNDERFLOW)
		throw OperandFloat::UnderflowException();
	else if (fe & FE_DIVBYZERO)
		throw OperandFloat::DivideByZeroException();
	else if (fe & FE_INVALID)
		throw OperandFloat::DivideByZeroException();
	op_result = this->_factory->createOperand(Float, std::to_string(result));
	return (op_result);
}

std::string const		&OperandFloat::toString(void) const
{
	return (this->_str_value);
}

OperandFloat::OverflowException::OverflowException(void)
{
	this->_msg = "This operation would cause an overflow !";
}

OperandFloat::OverflowException::~OverflowException(void) throw()
{
}

OperandFloat::OverflowException::OverflowException(OverflowException const &src)
{
	this->_msg = src._msg.c_str();
}

OperandFloat::OverflowException		&OperandFloat::OverflowException::operator=(
										OverflowException const &rhs)
{	
	this->_msg = rhs._msg.c_str();
	return (*this);
}

const char						*OperandFloat::OverflowException::what(void)
									const throw()
{
	return (this->_msg.c_str());
}

OperandFloat::UnderflowException::UnderflowException(void)
{
	this->_msg = "This operation would cause an underflow !";
}

OperandFloat::UnderflowException::~UnderflowException(void) throw()
{
}

OperandFloat::UnderflowException::UnderflowException(UnderflowException const &src)
{
	this->_msg = src._msg.c_str();
}

OperandFloat::UnderflowException	&OperandFloat::UnderflowException::operator=(
										UnderflowException const &rhs)
{	
	this->_msg = rhs._msg.c_str();
	return (*this);
}

const char						*OperandFloat::UnderflowException::what(void)
									const throw()
{
	return (this->_msg.c_str());
}

OperandFloat::DivideByZeroException::DivideByZeroException(void)
{
	this->_msg = "This operation would cause a division by zero !";
}

OperandFloat::DivideByZeroException::~DivideByZeroException(void) throw()
{
}

OperandFloat::DivideByZeroException::DivideByZeroException(DivideByZeroException
		const &src)
{
	this->_msg = src._msg.c_str();
}

OperandFloat::DivideByZeroException	&OperandFloat::DivideByZeroException::
										operator=(DivideByZeroException const &rhs)
{	
	this->_msg = rhs._msg.c_str();
	return (*this);
}

const char						*OperandFloat::DivideByZeroException::what(void)
									const throw()
{
	return (this->_msg.c_str());
}
