/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandInt8.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:55:23 by cledant           #+#    #+#             */
/*   Updated: 2017/05/26 10:45:37 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandInt8.hpp"

OperandInt8::OperandInt8(void) : _value(0), _str_value("0"), _zeroprecision(0)
{
	this->_factory = new OperandFactory();
}

OperandInt8::~OperandInt8(void)
{
	delete this->_factory;
}

OperandInt8::OperandInt8(OperandInt8 const &src) : _value(src.getValue()), _str_value(src.toString()), _zeroprecision(src.getZeroPrecision())
{
	this->_factory = new OperandFactory();
}

OperandInt8			&OperandInt8::operator=(OperandInt8 const &rhs)
{
	this->_value = rhs.getValue();
	this->_str_value = rhs.toString().c_str();
	this->_zeroprecision = rhs.getZeroPrecision();
	return (*this);
}

OperandInt8::OperandInt8(char const value) : _value(value), _zeroprecision(0)
{
	this->_factory = new OperandFactory();
	this->_str_value = std::to_string(static_cast<int>(value));
}

int						OperandInt8::getPrecision(void) const
{
	return (static_cast<int>(this->getType()));
}

eOperandType			OperandInt8::getType(void) const
{
	return (Int8);
}

char					OperandInt8::getValue(void) const
{
	return (this->_value);
}

size_t					OperandInt8::getZeroPrecision(void) const
{
	return (this->_zeroprecision);
}

IOperand const			*OperandInt8::operator+(IOperand const &rhs) const
{
	char				result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt8 &>(rhs).getValue() > 0 &&
			(this->_value > (std::numeric_limits<char>::max() -
			dynamic_cast<const OperandInt8 &>(rhs).getValue())))
		throw OperandInt8::OverflowException();
	else if (dynamic_cast<const OperandInt8 &>(rhs).getValue() < 0 &&
			(this->_value < (std::numeric_limits<char>::min() -
			dynamic_cast<const OperandInt8 &>(rhs).getValue())))
		throw OperandInt8::UnderflowException();
	result = static_cast<char>(this->_value + dynamic_cast<const OperandInt8 &>(rhs).getValue());
	op_result = this->_factory->createOperand(Int8,
		std::to_string(static_cast<int>(result)));
	return (op_result);
}

IOperand const			*OperandInt8::operator-(IOperand const &rhs) const
{
	char				result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt8 &>(rhs).getValue() < 0 &&
			(this->_value > (std::numeric_limits<char>::max() +
			dynamic_cast<const OperandInt8 &>(rhs).getValue())))
		throw OperandInt8::OverflowException();
	else if (dynamic_cast<const OperandInt8 &>(rhs).getValue() > 0 &&
			(this->_value < (std::numeric_limits<char>::min() +
			dynamic_cast<const OperandInt8 &>(rhs).getValue())))
		throw OperandInt8::UnderflowException();
	result = static_cast<char>(this->_value - dynamic_cast<const OperandInt8 &>(rhs).getValue());
	op_result = this->_factory->createOperand(Int8,
		std::to_string(static_cast<int>(result)));
	return (op_result);
}

IOperand const			*OperandInt8::operator*(IOperand const &rhs) const
{
	char				result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt8 &>(rhs).getValue() == 0 ||
			this->getValue() == 0)
	{
		op_result = this->_factory->createOperand(Int8, "0");
		return (op_result);
	}
	else if (this->_value == -1 && std::numeric_limits<char>::min() ==
			dynamic_cast<const OperandInt8 &>(rhs).getValue())
		throw OperandInt8::OverflowException();
	else if (dynamic_cast<const OperandInt8 &>(rhs).getValue() == -1 &&
			this->_value == std::numeric_limits<char>::min())
		throw OperandInt8::OverflowException();
	else if (this->_value > 0 &&
			dynamic_cast<const OperandInt8 &>(rhs).getValue() > 0 &&
			this->_value > (std::numeric_limits<char>::max() /
			dynamic_cast<const OperandInt8 &>(rhs).getValue()))
		throw OperandInt8::OverflowException();
	else if (this->_value > 0 &&
			dynamic_cast<const OperandInt8 &>(rhs).getValue() <= 0 &&
			dynamic_cast<const OperandInt8 &>(rhs).getValue() <
			(std::numeric_limits<char>::min() / this->_value))
		throw OperandInt8::OverflowException();
	else if (this->_value <= 0 &&
			dynamic_cast<const OperandInt8 &>(rhs).getValue() > 0 &&
			this->_value < (std::numeric_limits<char>::min() /
			dynamic_cast<const OperandInt8 &>(rhs).getValue()))
		throw OperandInt8::OverflowException();
	else if (this->_value <= 0 &&
			dynamic_cast<const OperandInt8 &>(rhs).getValue() <= 0 &&
			dynamic_cast<const OperandInt8 &>(rhs).getValue() <
			(std::numeric_limits<char>::max() / this->_value))
		throw OperandInt8::OverflowException();
	result = static_cast<char>(this->_value * dynamic_cast<const OperandInt8 &>(rhs).getValue());
	op_result = this->_factory->createOperand(Int8,
		std::to_string(static_cast<int>(result)));
	return (op_result);
}

IOperand const			*OperandInt8::operator/(IOperand const &rhs) const
{
	char				result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt8 &>(rhs).getValue() == 0)
		throw OperandInt8::DivideByZeroException();
	else if (this->getValue() == 0)
	{
		op_result = this->_factory->createOperand(Int8, "0");
		return (op_result);
	}
	else if (dynamic_cast<const OperandInt8 &>(rhs).getValue() == -1 &&
			this->_value == std::numeric_limits<char>::min())
		throw OperandInt8::OverflowException();
	result = static_cast<char>(this->_value / dynamic_cast<const OperandInt8 &>(rhs).getValue());
	op_result = this->_factory->createOperand(Int8,
		std::to_string(static_cast<int>(result)));
	return (op_result);
}

IOperand const			*OperandInt8::operator%(IOperand const &rhs) const
{
	char				result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt8 &>(rhs).getValue() == 0)
		throw OperandInt8::DivideByZeroException();
	else if (this->getValue() == 0)
	{
		op_result = this->_factory->createOperand(Int8, "0");
		return (op_result);
	}
	else if (dynamic_cast<const OperandInt8 &>(rhs).getValue() == -1 &&
			this->_value == std::numeric_limits<char>::min())
		throw OperandInt8::OverflowException();
	result = static_cast<char>(this->_value % dynamic_cast<const OperandInt8 &>(rhs).getValue());
	op_result = this->_factory->createOperand(Int8,
		std::to_string(static_cast<int>(result)));
	return (op_result);
}

std::string const		&OperandInt8::toString(void) const
{
	return (this->_str_value);
}

OperandInt8::OverflowException::OverflowException(void)
{
	this->_msg = "Runtime Exception : OperandInt8 : This operation would cause an overflow !";
}

OperandInt8::OverflowException::~OverflowException(void) throw()
{
}

OperandInt8::UnderflowException::UnderflowException(void)
{
	this->_msg = "Runtime Exception : OperandInt8 : This operation would cause an underflow !";
}

OperandInt8::UnderflowException::~UnderflowException(void) throw()
{
}

OperandInt8::DivideByZeroException::DivideByZeroException(void)
{
		this->_msg = "Runtime Exception : OperandInt8 : This operation would cause a division by zero !";
}

OperandInt8::DivideByZeroException::~DivideByZeroException(void) throw()
{
}
