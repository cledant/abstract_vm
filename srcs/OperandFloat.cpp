/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFloat.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:55:23 by cledant           #+#    #+#             */
/*   Updated: 2017/05/26 11:41:29 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFloat.hpp"

OperandFloat::OperandFloat(void) : _value(0.f), _str_value("0.00000"), _zeroprecision(5)
{
	this->_factory = new OperandFactory();
}

OperandFloat::~OperandFloat(void)
{
	delete this->_factory;
}

OperandFloat::OperandFloat(OperandFloat const &src) : _value(src.getValue()), _str_value(src.toString()), _zeroprecision(src.getZeroPrecision())
{
	this->_factory = new OperandFactory();
}

OperandFloat			&OperandFloat::operator=(OperandFloat const &rhs)
{
	this->_value = rhs.getValue();
	this->_str_value = rhs.toString().c_str();
	this->_zeroprecision = rhs.getZeroPrecision();
	return (*this);
}

OperandFloat::OperandFloat(float const value, std::string const &str) : _value(value)
{
	this->_factory = new OperandFactory();
	if ((this->_zeroprecision = this->parsePrecision(str)) >= 5)
		this->_str_value = str;
	else
	{
		this->_zeroprecision = 5;
		this->_str_value = this->convertToString(this->_value, this->_zeroprecision);
	}
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

size_t					OperandFloat::getZeroPrecision(void) const
{
	return (this->_zeroprecision);
}

IOperand const			*OperandFloat::operator+(IOperand const &rhs) const
{
	float				result;
	int					fe;
	const IOperand		*op_result;
	size_t				precision;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value + dynamic_cast<const OperandFloat &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandFloat::OverflowException();
	precision = (dynamic_cast<OperandFloat const &>(rhs).getZeroPrecision() >
		this->_zeroprecision) ?
		dynamic_cast<OperandFloat const &>(rhs).getZeroPrecision() :
		this->_zeroprecision;
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
	size_t				precision;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value - dynamic_cast<const OperandFloat &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandFloat::OverflowException();
	precision = (dynamic_cast<OperandFloat const &>(rhs).getZeroPrecision() >
		this->_zeroprecision) ?
		dynamic_cast<OperandFloat const &>(rhs).getZeroPrecision() :
		this->_zeroprecision;
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
	size_t				precision;

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
	precision = (dynamic_cast<OperandFloat const &>(rhs).getZeroPrecision() >
		this->_zeroprecision) ?
		dynamic_cast<OperandFloat const &>(rhs).getZeroPrecision() :
		this->_zeroprecision;
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
	size_t				precision;

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
	precision = (dynamic_cast<OperandFloat const &>(rhs).getZeroPrecision() >
		this->_zeroprecision) ?
		dynamic_cast<OperandFloat const &>(rhs).getZeroPrecision() :
		this->_zeroprecision;
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
	size_t				precision;

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
	precision = (dynamic_cast<OperandFloat const &>(rhs).getZeroPrecision() >
		this->_zeroprecision) ?
		dynamic_cast<OperandFloat const &>(rhs).getZeroPrecision() :
		this->_zeroprecision;
	op_result = this->_factory->createOperand(Float,
		dynamic_cast<OperandFloat const *>(this)->convertToString(result,
		precision));
	return (op_result);
}

std::string const		&OperandFloat::toString(void) const
{
	return (this->_str_value);
}

size_t					OperandFloat::parsePrecision(std::string const &value) const
{
	size_t		pos_dot;
	size_t		pos_paren;

	pos_dot = value.find(".") + 1;
	pos_paren = value.size();
	return (pos_paren - pos_dot);
}

std::string				OperandFloat::convertToString(float value,
							size_t precision) const
{
	std::ostringstream		out;
	std::string				conv;

	out << std::fixed << std::setprecision(static_cast<int>(precision)) << value;
	conv = out.str();
	return (conv);
}

OperandFloat::OverflowException::OverflowException(void)
{
	this->_msg = "Runtime Exception : OperandFloat : This operation would cause an overflow !";
}

OperandFloat::OverflowException::~OverflowException(void) throw()
{
}

OperandFloat::UnderflowException::UnderflowException(void)
{
	this->_msg = "Runtime Exception : OperandFloat : This operation would cause an underflow !";
}

OperandFloat::UnderflowException::~UnderflowException(void) throw()
{
}

OperandFloat::DivideByZeroException::DivideByZeroException(void)
{
		this->_msg = "Runtime Exception : OperandFloat : This operation would cause a division by zero !";
}

OperandFloat::DivideByZeroException::~DivideByZeroException(void) throw()
{
}
