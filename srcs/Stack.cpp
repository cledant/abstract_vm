/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:01:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/08 17:15:49 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Stack.hpp"

Stack::Stack(void)
{
}

Stack::~Stack(void)
{
}

void		Stack::push(eOperandType type, std::string const &value)
{
	IOperand const		*op;

	op = this->_factory->createOperand(type, value);
	this->_stack.push_back(op);
}
