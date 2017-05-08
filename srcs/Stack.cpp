/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:01:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/08 20:18:28 by cledant          ###   ########.fr       */
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

void		Stack::dump(void)
{
	std::vector<IOperand const *>::reverse_iterator		rit;

	for(rit = this->_stack.rbegin(); rit != this->_stack.rend(); ++rit)
		std::cout << (*rit)->toString() << std::endl;
}

void		Stack::add(void)
{
	std::vector<IOperand const *>::reverse_iterator		lhs;
	std::vector<IOperand const *>::reverse_iterator		rhs;
	IOperand const										*res;
	IOperand const										*cast;

	if (this->_stack.size() < 2)
		throw std::exception("Stack : Add : Not enough elemets in stack");
	lhs = this->_stack.rbegin();
	this->_stack.pop_back();
	rhs = this->_stack.rbegin();
	if ((*lhs)->getType() == (*rhs)->getType())
		res = *lhs + *rhs;
	//faire fonction qui cast le ptr IOpreand dans la bonne classe fille + selon les diff operation et ret
	else if ((*lhs)->getType() > (*rhs)->getType())
	{
		cast = this->_factory->createOperand((*lhs)->getType(), (*rhs)->toString());
		res = *lhs + cast;
		delete cast;
	}
	else
	{
		cast = this->_factory->createOperand((*rhs)->getType(), (*lhs)->toString());
		*res = *rhs + cast;
		delete cast;
	}
	this->_stack.push_back(res);
	delete *lhs;
	delete *rhs;
}
