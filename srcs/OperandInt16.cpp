/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandInt16.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:55:23 by cledant           #+#    #+#             */
/*   Updated: 2017/05/04 17:37:04 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandInt16.hpp"

OperandInt16::OperandInt16(void) : _value(0), _str_value("0")
{
	this->_factory = new OperandFactory();
}

OperandInt16::~OperandInt16(void)
{
	delete this->_factory;
}

OperandInt16::OperandInt16(OperandInt16 const &src) : _value(src.getValue()), _str_value(src.toString())
{
	this->_factory = new OperandFactory();
}

OperandInt16			&OperandInt16::operator=(OperandInt16 const &rhs)
{
	this->_value = rhs.getValue();
	this->_str_value = rhs.toString().c_str();
	return(*this);
}

OperandInt16::OperandInt16(short int const value) : _value(value)
{
	this->_factory = new OperandFactory();
	this->_str_value = std::to_string(static_cast<int>(value));
}

int						OperandInt16::getPrecision(void) const
{
	return (static_cast<int>(this->getType()));
}

eOperandType			OperandInt16::getType(void) const
{
	return (Int16);
}

short int				OperandInt16::getValue(void) const
{
	return (this->_value);
}

IOperand const			*OperandInt16::operator+(IOperand const &rhs) const
{
	short int			result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt16 &>(rhs).getValue() > 0 &&
			(this->_value > (std::numeric_limits<short int>::max() -
			dynamic_cast<const OperandInt16 &>(rhs).getValue())))
		throw std::overflow_error("Addition would cause an overflow");
	else if (dynamic_cast<const OperandInt16 &>(rhs).getValue() < 0 &&
			(this->_value < (std::numeric_limits<short int>::min() -
			dynamic_cast<const OperandInt16 &>(rhs).getValue())))
		throw std::overflow_error("Addition would cause an underflow");
	result = this->_value + dynamic_cast<const OperandInt16 &>(rhs).getValue();
	op_result = this->_factory->createOperand(Int16,
		std::to_string(static_cast<int>(result)));
	return (op_result);
}

IOperand const			*OperandInt16::operator-(IOperand const &rhs) const
{
	short int			result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt16 &>(rhs).getValue() < 0 &&
			(this->_value > (std::numeric_limits<short int>::max() +
			dynamic_cast<const OperandInt16 &>(rhs).getValue())))
		throw std::overflow_error("Subtraction would cause an overflow");
	else if (dynamic_cast<const OperandInt16 &>(rhs).getValue() > 0 &&
			(this->_value < (std::numeric_limits<short int>::min() +
			dynamic_cast<const OperandInt16 &>(rhs).getValue())))
		throw std::underflow_error("Subtraction would cause an underflow");
	result = this->_value - dynamic_cast<const OperandInt16 &>(rhs).getValue();
	op_result = this->_factory->createOperand(Int16,
		std::to_string(static_cast<int>(result)));
	return (op_result);
}

IOperand const			*OperandInt16::operator*(IOperand const &rhs) const
{
	short int			result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt16 &>(rhs).getValue() == 0 ||
			this->getValue() == 0)
	{
		op_result = this->_factory->createOperand(Int16, "0");
		return (op_result);
	}
	else if (this->_value > (std::numeric_limits<short int>::max() /
			dynamic_cast<const OperandInt16 &>(rhs).getValue()))
		throw std::overflow_error("Multiplication would cause an overflow");
	else if (this->_value == -1 && std::numeric_limits<short int>::min() ==
			dynamic_cast<const OperandInt16 &>(rhs).getValue())
		throw std::overflow_error("Multiplication would cause an overflow");
	else if (dynamic_cast<const OperandInt16 &>(rhs).getValue() == -1 &&
			this->_value == std::numeric_limits<short int>::min())
		throw std::overflow_error("Multiplication would cause an overflow");
	else if (this->_value < (std::numeric_limits<short int>::min() /
			dynamic_cast<const OperandInt16 &>(rhs).getValue()))
		throw std::underflow_error("Multiplication would cause an underflow");
	result = this->_value * dynamic_cast<const OperandInt16 &>(rhs).getValue();
	op_result = this->_factory->createOperand(Int16,
		std::to_string(static_cast<int>(result)));
	return (op_result);
}

IOperand const			*OperandInt16::operator/(IOperand const &rhs) const
{
	short int			result;
	const IOperand		*op_result;

	if (dynamic_cast<const OperandInt16 &>(rhs).getValue() == 0)
		throw std::logic_error("Division can't divide by zero");
	else if (this->getValue() == 0)
	{
		op_result = this->_factory->createOperand(Int16, "0");
		return (op_result);
	}
	else if (dynamic_cast<const OperandInt16 &>(rhs).getValue() == -1 &&
			this->_value == std::numeric_limits<short int>::min())
		throw std::overflow_error("Division would cause an overflow");
	result = this->_value / dynamic_cast<const OperandInt16 &>(rhs).getValue();
	op_result = this->_factory->createOperand(Int16,
		std::to_string(static_cast<int>(result)));
	return (op_result);
}

std::string const		&OperandInt16::toString(void) const
{
	return (this->_str_value);
}
