/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:23:40 by cledant           #+#    #+#             */
/*   Updated: 2017/05/05 10:03:22 by cledant          ###   ########.fr       */
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
