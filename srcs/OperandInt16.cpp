/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandInt16.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:55:23 by cledant           #+#    #+#             */
/*   Updated: 2017/05/03 12:52:09 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandInt16.hpp"

OperandInt16::OperandInt16(void) : _value(0)
{
}

OperandInt16::~OperandInt16(void)
{
}

OperandInt16::OperandInt16(OperandInt16 const &src) : _value(srv.getValue())
{
}

OperandInt16		&OperandInt16::operator=(OperandInt16 const &rhs)
{
	this->_value = rhs.getValue();
	return(*this);
}

int			OperandInt16::getPrecision(void) const
{
	return (static_cast<int>(this->getType()));
}

eOperand	OperandInt16::getType(void) const
{
	return (Int16);
}

short int	OperandInt16::getValue(void)
{
	return (_value);
}
