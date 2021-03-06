/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandInt32.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:55:23 by cledant           #+#    #+#             */
/*   Updated: 2017/05/26 10:54:03 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandInt32.hpp"

OperandInt32::OperandInt32(void) : _value(0), _str_value("0"), _zeroprecision(0)
{
	this->_factory = new OperandFactory();
}

OperandInt32::~OperandInt32(void)
{
	delete this->_factory;
}

OperandInt32::OperandInt32(OperandInt32 const &src) : _value(src.getValue()), _str_value(src.toString()), _zeroprecision(src.getZeroPrecision())
{
	this->_factory = new OperandFactory();
}

OperandInt32			&OperandInt32::operator=(OperandInt32 const &rhs)
{
	this->_value = rhs.getValue();
	this->_str_value = rhs.toString().c_str();
	this->_zeroprecision = rhs.getZeroPrecision();
	return (*this);
}

OperandInt32::OperandInt32(int const value) : _value(value), _zeroprecision(0)
{
	this->_factory = new OperandFactory();
	this->_str_value = std::to_string(value);
}

int						OperandInt32::getPrecision(void) const
{
	return (static_cast<int>(this->getType()));
}

eOperandType			OperandInt32::getType(void) const
{
	return (Int32);
}

int						OperandInt32::getValue(void) const
{
	return (this->_value);
}

size_t					OperandInt32::getZeroPrecision(void) const
{
	return (this->_zeroprecision);
}

IOperand const			*OperandInt32::operator+(IOperand const &rhs) const
{
	int					result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt32 &>(rhs).getValue() > 0 &&
			(this->_value > (std::numeric_limits<int>::max() -
			dynamic_cast<const OperandInt32 &>(rhs).getValue())))
		throw OperandInt32::OverflowException();
	else if (dynamic_cast<const OperandInt32 &>(rhs).getValue() < 0 &&
			(this->_value < (std::numeric_limits<int>::min() -
			dynamic_cast<const OperandInt32 &>(rhs).getValue())))
		throw OperandInt32::UnderflowException();
	result = this->_value + dynamic_cast<const OperandInt32 &>(rhs).getValue();
	op_result = this->_factory->createOperand(Int32, std::to_string(result));
	return (op_result);
}

IOperand const			*OperandInt32::operator-(IOperand const &rhs) const
{
	int					result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt32 &>(rhs).getValue() < 0 &&
			(this->_value > (std::numeric_limits<int>::max() +
			dynamic_cast<const OperandInt32 &>(rhs).getValue())))
		throw OperandInt32::OverflowException();
	else if (dynamic_cast<const OperandInt32 &>(rhs).getValue() > 0 &&
			(this->_value < (std::numeric_limits<int>::min() +
			dynamic_cast<const OperandInt32 &>(rhs).getValue())))
		throw OperandInt32::UnderflowException();
	result = this->_value - dynamic_cast<const OperandInt32 &>(rhs).getValue();
	op_result = this->_factory->createOperand(Int32, std::to_string(result));
	return (op_result);
}

IOperand const			*OperandInt32::operator*(IOperand const &rhs) const
{
	int					result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt32 &>(rhs).getValue() == 0 ||
			this->getValue() == 0)
	{
		op_result = this->_factory->createOperand(Int32, "0");
		return (op_result);
	}
	else if (this->_value == -1 && std::numeric_limits<int>::min() ==
			dynamic_cast<const OperandInt32 &>(rhs).getValue())
		throw OperandInt32::OverflowException();
	else if (dynamic_cast<const OperandInt32 &>(rhs).getValue() == -1 &&
			this->_value == std::numeric_limits<int>::min())
		throw OperandInt32::OverflowException();
	else if (this->_value > 0 &&
			dynamic_cast<const OperandInt32 &>(rhs).getValue() > 0 &&
			this->_value > (std::numeric_limits<int>::max() /
			dynamic_cast<const OperandInt32 &>(rhs).getValue()))
		throw OperandInt32::OverflowException();
	else if (this->_value > 0 &&
			dynamic_cast<const OperandInt32 &>(rhs).getValue() <= 0 &&
			dynamic_cast<const OperandInt32 &>(rhs).getValue() <
			(std::numeric_limits<int>::min() / this->_value))
		throw OperandInt32::OverflowException();
	else if (this->_value <= 0 &&
			dynamic_cast<const OperandInt32 &>(rhs).getValue() > 0 &&
			this->_value < (std::numeric_limits<int>::min() /
			dynamic_cast<const OperandInt32 &>(rhs).getValue()))
		throw OperandInt32::OverflowException();
	else if (this->_value <= 0 &&
			dynamic_cast<const OperandInt32 &>(rhs).getValue() <= 0 &&
			dynamic_cast<const OperandInt32 &>(rhs).getValue() <
			(std::numeric_limits<int>::max() / this->_value))
		throw OperandInt32::OverflowException();
	result = this->_value * dynamic_cast<const OperandInt32 &>(rhs).getValue();
	op_result = this->_factory->createOperand(Int32, std::to_string(result));
	return (op_result);
}

IOperand const			*OperandInt32::operator/(IOperand const &rhs) const
{
	int					result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt32 &>(rhs).getValue() == 0)
		throw OperandInt32::DivideByZeroException();
	else if (this->getValue() == 0)
	{
		op_result = this->_factory->createOperand(Int32, "0");
		return (op_result);
	}
	else if (dynamic_cast<const OperandInt32 &>(rhs).getValue() == -1 &&
			this->_value == std::numeric_limits<int>::min())
		throw OperandInt32::OverflowException();
	result = this->_value / dynamic_cast<const OperandInt32 &>(rhs).getValue();
	op_result = this->_factory->createOperand(Int32, std::to_string(result));
	return (op_result);
}

IOperand const			*OperandInt32::operator%(IOperand const &rhs) const
{
	int					result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt32 &>(rhs).getValue() == 0)
		throw OperandInt32::DivideByZeroException();
	else if (this->getValue() == 0)
	{
		op_result = this->_factory->createOperand(Int32, "0");
		return (op_result);
	}
	else if (dynamic_cast<const OperandInt32 &>(rhs).getValue() == -1 &&
			this->_value == std::numeric_limits<int>::min())
		throw OperandInt32::OverflowException();
	result = this->_value % dynamic_cast<const OperandInt32 &>(rhs).getValue();
	op_result = this->_factory->createOperand(Int32, std::to_string(result));
	return (op_result);
}

std::string const		&OperandInt32::toString(void) const
{
	return (this->_str_value);
}

OperandInt32::OverflowException::OverflowException(void)
{
	this->_msg = "Runtime Exception : OperandInt32 : This operation would cause an overflow !";
}

OperandInt32::OverflowException::~OverflowException(void) throw()
{
}

OperandInt32::UnderflowException::UnderflowException(void)
{
	this->_msg = "Runtime Exception : OperandInt32 : This operation would cause an underflow !";
}

OperandInt32::UnderflowException::~UnderflowException(void) throw()
{
}

OperandInt32::DivideByZeroException::DivideByZeroException(void)
{
		this->_msg = "Runtime Exception : OperandInt32 : This operation would cause a division by zero !";
}

OperandInt32::DivideByZeroException::~DivideByZeroException(void) throw()
{
}
