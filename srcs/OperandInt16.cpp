/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandInt16.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:55:23 by cledant           #+#    #+#             */
/*   Updated: 2017/05/03 18:27:04 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandInt16.hpp"

OperandInt16::OperandInt16(void) : _value(0)
{
}

OperandInt16::~OperandInt16(void)
{
}

OperandInt16::OperandInt16(OperandInt16 const &src) : _value(src.getValue())
{
}

OperandInt16			&OperandInt16::operator=(OperandInt16 const &rhs)
{
	this->_value = rhs.getValue();
	return(*this);
}

OperandInt16::OperandInt16(short int const value) : _value(value)
{
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
	return (_value);
}

IOperand const			*OperandInt16::operator+(IOperand const &rhs) const
{
	short int		result;
	IOperand		*op_result;

	if (dynamic_cast<const OperandInt16 &>(rhs).getValue() > 0 &&
			(this->_value > (std::numeric_limits<short int>::max() -
			dynamic_cast<const OperandInt16 &>(rhs).getValue())))
		throw std::overflow_error("Addition would case an overflow");
	else if (dynamic_cast<const OperandInt16 &>(rhs).getValue() < 0 &&
			(this->_value < (std::numeric_limits<short int>::min() -
			dynamic_cast<const OperandInt16 &>(rhs).getValue())))
		throw std::overflow_error("Addition would case an underflow");
	result = this->_value + dynamic_cast<const OperandInt16 &>(rhs).getValue();
	op_result = new OperandInt16(result);
	return (op_result);
}

IOperand const			*OperandInt16::operator-(IOperand const &rhs) const
{
	short int		result;
	IOperand		*op_result;

	if (dynamic_cast<const OperandInt16 &>(rhs).getValue() < 0 &&
			(this->_value > (std::numeric_limits<short int>::max() +
			dynamic_cast<const OperandInt16 &>(rhs).getValue())))
		throw std::overflow_error("Subtraction would case an overflow");
	else if (dynamic_cast<const OperandInt16 &>(rhs).getValue() > 0 &&
			(this->_value < (std::numeric_limits<short int>::min() +
			dynamic_cast<const OperandInt16 &>(rhs).getValue())))
		throw std::underflow_error("Subtraction would case an underflow");
	result = this->_value + dynamic_cast<const OperandInt16 &>(rhs).getValue();
	op_result = new OperandInt16(result);
	return (op_result);
}
