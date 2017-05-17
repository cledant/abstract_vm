/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFloat.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:55:23 by cledant           #+#    #+#             */
/*   Updated: 2017/05/17 20:29:43 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFloat.hpp"

OperandFloat::OperandFloat(void) : _value(0.f), _str_value("0.0"), _precision(1)
{
	this->_factory = new OperandFactory();
}

OperandFloat::~OperandFloat(void)
{
	delete this->_factory;
}

OperandFloat::OperandFloat(OperandFloat const &src) : _value(src.getValue()), _str_value(src.toString()), _precision(src.getPrecision())
{
	this->_factory = new OperandFactory();
}

OperandFloat			&OperandFloat::operator=(OperandFloat const &rhs)
{
	this->_value = rhs.getValue();
	this->_str_value = rhs.toString().c_str();
	this->_precision = rhs.getPrecision();
	return (*this);
}

OperandFloat::OperandFloat(float const value, std::string const &str) : _value(value)
{
	this->_factory = new OperandFactory();
	this->_precision = this->parsePrecision(str);
	this->_str_value = str;
}

int						OperandFloat::getPrecision(void) const
{
	return (this->_precision);
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
	int					precision;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value + dynamic_cast<const OperandFloat &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandFloat::OverflowException();
	precision = (rhs.getPrecision() > this->_precision) ? rhs.getPrecision() :
		this->_precision;
	op_result = this->_factory->createOperand(Float,
		dynamic_cast<OperandFloat const *>(this)->convertToString(result,
		precision));
	return (op_result);
}

IOperand const			*OperandFloat::operator-(IOperand const &rhs) const
{
	float				result;
	int					fe;
	const IOperand		*op_result;
	int					precision;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value - dynamic_cast<const OperandFloat &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandFloat::OverflowException();
	precision = (rhs.getPrecision() > this->_precision) ? rhs.getPrecision() :
		this->_precision;
	op_result = this->_factory->createOperand(Float,
		dynamic_cast<OperandFloat const *>(this)->convertToString(result,
		precision));
	return (op_result);
}

IOperand const			*OperandFloat::operator*(IOperand const &rhs) const
{
	float				result;
	int					fe;
	const IOperand		*op_result;
	int					precision;

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
	precision = (rhs.getPrecision() > this->_precision) ? rhs.getPrecision() :
		this->_precision;
	op_result = this->_factory->createOperand(Float,
		dynamic_cast<OperandFloat const *>(this)->convertToString(result,
		precision));
	return (op_result);
}

IOperand const			*OperandFloat::operator/(IOperand const &rhs) const
{
	float				result;
	int					fe;
	const IOperand		*op_result;
	int					precision;

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
	precision = (rhs.getPrecision() > this->_precision) ? rhs.getPrecision() :
		this->_precision;
	op_result = this->_factory->createOperand(Float,
		dynamic_cast<OperandFloat const *>(this)->convertToString(result,
		precision));
	return (op_result);
}

IOperand const			*OperandFloat::operator%(IOperand const &rhs) const
{
	float				result;
	int					fe;
	const IOperand		*op_result;
	int					precision;

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
	precision = (rhs.getPrecision() > this->_precision) ? rhs.getPrecision() :
		this->_precision;
	op_result = this->_factory->createOperand(Float,
		dynamic_cast<OperandFloat const *>(this)->convertToString(result,
		precision));
	return (op_result);
}

std::string const		&OperandFloat::toString(void) const
{
	return (this->_str_value);
}

int						OperandFloat::parsePrecision(std::string const &value) const
{
	size_t		pos_dot;
	size_t		pos_paren;

	pos_dot = value.find(".") + 1;
	pos_paren = value.size();
	return (static_cast<int>(pos_paren - pos_dot));
}

std::string				OperandFloat::convertToString(float value,
							int precision) const
{
	std::ostringstream		out;
	std::string				conv;

	out << std::fixed << std::setprecision(precision) << value;
	conv = out.str();
	return (conv);
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
