/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStack.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 14:54:00 by cledant           #+#    #+#             */
/*   Updated: 2017/05/09 14:33:12 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AStack.hpp"

AStack::AStack(void)
{
	this->_factory = new OperandFactory();
}

AStack::~AStack(void)
{
	std::vector<IOperand const *>::iterator		it;

	for(it = this->_stack.begin(); it != this->_stack.end(); ++it)
		delete *it;
	delete this->_factory;
}

AStack::AStack(AStack const &src)
{
	std::vector<IOperand const *>::const_iterator		it;

	this->_factory = new OperandFactory();
	for(it = src.getStack().cbegin(); it != src.getStack().cend(); ++it)
		this->_stack.push_back(*it);
}

AStack									&AStack::operator=(AStack const &rhs)
{
	std::vector<IOperand const *>::const_iterator		it;
	IOperand const										*cpy;

	for(it = this->_stack.cbegin(); it != this->_stack.cend(); ++it)
		delete *it;
	this->_stack.clear();
	for(it = rhs.getStack().cbegin(); it != rhs.getStack().cend(); ++it)
	{
		cpy = this->_factory->createOperand((*it)->getType(), (*it)->toString());
		this->_stack.push_back(cpy);
	}
	return (*this);
}

std::vector<IOperand const *> const		&AStack::getStack(void) const
{
	return (this->_stack);
}
