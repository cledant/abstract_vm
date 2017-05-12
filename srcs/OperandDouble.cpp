/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandDouble.cpp                  i                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:55:23 by cledant           #+#    #+#             */
/*   Updated: 2017/05/12 09:32:25 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandDouble.hpp"

OperandDouble::OperandDouble(void) : _value(0.0), _str_value("0")
{
	this->_factory = new OperandFactory();
}

OperandDouble::~OperandDouble(void)
{
	delete this->_factory;
}

OperandDouble::OperandDouble(OperandDouble const &src) : _value(src.getValue()), _str_value(src.toString())
{
	this->_factory = new OperandFactory();
}

OperandDouble			&OperandDouble::operator=(OperandDouble const &rhs)
{
	this->_value = rhs.getValue();
	this->_str_value = rhs.toString().c_str();
	return (*this);
}

OperandDouble::OperandDouble(double const value) : _value(value)
{
	this->_factory = new OperandFactory();
	this->_str_value = std::to_string(value);
}

int						OperandDouble::getPrecision(void) const
{
	return (static_cast<int>(this->getType()));
}

eOperandType			OperandDouble::getType(void) const
{
	return (Double);
}

double					OperandDouble::getValue(void) const
{
	return (this->_value);
}

IOperand const			*OperandDouble::operator+(IOperand const &rhs) const
{
	double				result;
	int					fe;
	const IOperand		*op_result;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value + dynamic_cast<const OperandDouble &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandDouble::OverflowException();
	op_result = this->_factory->createOperand(Double, std::to_string(result));
	return (op_result);
}

IOperand const			*OperandDouble::operator-(IOperand const &rhs) const
{
	double				result;
	int					fe;
	const IOperand		*op_result;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value - dynamic_cast<const OperandDouble &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandDouble::OverflowException();
	op_result = this->_factory->createOperand(Double, std::to_string(result));
	return (op_result);
}

IOperand const			*OperandDouble::operator*(IOperand const &rhs) const
{
	double				result;
	int					fe;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandDouble &>(rhs).getValue() == 0.0 ||
			this->getValue() == 0.0)
	{
		op_result = this->_factory->createOperand(Double, "0");
		return (op_result);
	}
	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value * dynamic_cast<const OperandDouble &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandDouble::OverflowException();
	else if (fe & FE_UNDERFLOW)
		throw OperandDouble::UnderflowException();
	op_result = this->_factory->createOperand(Double, std::to_string(result));
	return (op_result);
}

IOperand const			*OperandDouble::operator/(IOperand const &rhs) const
{
	double				result;
	int					fe;
	const IOperand		*op_result;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value / dynamic_cast<const OperandDouble &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandDouble::OverflowException();
	else if (fe & FE_UNDERFLOW)
		throw OperandDouble::UnderflowException();
	else if (fe & FE_DIVBYZERO)
		throw OperandDouble::DivideByZeroException();
	else if (fe & FE_INVALID)
		throw OperandDouble::DivideByZeroException();
	op_result = this->_factory->createOperand(Double, std::to_string(result));
	return (op_result);
}

IOperand const			*OperandDouble::operator%(IOperand const &rhs) const
{
	double				result;
	int					fe;
	const IOperand		*op_result;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = std::fmod(this->_value, dynamic_cast<const OperandDouble &>(rhs).getValue());
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandDouble::OverflowException();
	else if (fe & FE_UNDERFLOW)
		throw OperandDouble::UnderflowException();
	else if (fe & FE_DIVBYZERO)
		throw OperandDouble::DivideByZeroException();
	else if (fe & FE_INVALID)
		throw OperandDouble::DivideByZeroException();
	op_result = this->_factory->createOperand(Double, std::to_string(result));
	return (op_result);
}

std::string const		&OperandDouble::toString(void) const
{
	return (this->_str_value);
}

OperandDouble::OverflowException::OverflowException(void)
{
	this->_msg = "This operation would cause an overflow !";
}

OperandDouble::OverflowException::~OverflowException(void) throw()
{
}

OperandDouble::OverflowException::OverflowException(OverflowException const &src)
{
	this->_msg = src._msg.c_str();
}

OperandDouble::OverflowException		&OperandDouble::OverflowException::operator=(
										OverflowException const &rhs)
{	
	this->_msg = rhs._msg.c_str();
	return (*this);
}

const char						*OperandDouble::OverflowException::what(void)
									const throw()
{
	return (this->_msg.c_str());
}

OperandDouble::UnderflowException::UnderflowException(void)
{
	this->_msg = "This operation would cause an underflow !";
}

OperandDouble::UnderflowException::~UnderflowException(void) throw()
{
}

OperandDouble::UnderflowException::UnderflowException(UnderflowException const &src)
{
	this->_msg = src._msg.c_str();
}

OperandDouble::UnderflowException	&OperandDouble::UnderflowException::operator=(
										UnderflowException const &rhs)
{	
	this->_msg = rhs._msg.c_str();
	return (*this);
}

const char						*OperandDouble::UnderflowException::what(void)
									const throw()
{
	return (this->_msg.c_str());
}

OperandDouble::DivideByZeroException::DivideByZeroException(void)
{
	this->_msg = "This operation would cause a division by zero !";
}

OperandDouble::DivideByZeroException::~DivideByZeroException(void) throw()
{
}

OperandDouble::DivideByZeroException::DivideByZeroException(DivideByZeroException
		const &src)
{
	this->_msg = src._msg.c_str();
}

OperandDouble::DivideByZeroException	&OperandDouble::DivideByZeroException::
										operator=(DivideByZeroException const &rhs)
{	
	this->_msg = rhs._msg.c_str();
	return (*this);
}

const char						*OperandDouble::DivideByZeroException::what(void)
									const throw()
{
	return (this->_msg.c_str());
}
