/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:01:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/09 14:50:34 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Stack.hpp"
#include "abstract_vm_defines.hpp"

Stack::Stack(void)
{
}

Stack::~Stack(void)
{
}

void		Stack::push(eOperandType type, std::string const &value)
{
	std::unique_ptr<IOperand const>op = nullptr;

	op = std::unique_ptr<IOperand const>(this->_factory->createOperand(type, value));
	this->_stack.push_back(op.get());
	op.release();
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
	std::unique_ptr<IOperand const>						p_lhs;
	std::unique_ptr<IOperand const>						p_rhs;
	std::unique_ptr<IOperand const>						cast;
	std::unique_ptr<IOperand const>						result;

	if (this->_stack.size() < 2)
		throw std::runtime_error("Stack : Add : Not enough elemets in stack");
	lhs = this->_stack.rbegin();
	this->_stack.pop_back();
	rhs = this->_stack.rbegin();
	this->_stack.pop_back();
	p_lhs = std::unique_ptr<IOperand const>(*lhs);
	p_rhs = std::unique_ptr<IOperand const>(*rhs);
	if (p_lhs->getType() > p_rhs->getType())
	{
		cast = std::unique_ptr<IOperand const>(this->_factory->createOperand(
					p_lhs->getType(), p_rhs->toString()));
		p_rhs = std::move(cast);
	}
	else if (p_lhs->getType() < p_rhs->getType())
	{
		cast = std::unique_ptr<IOperand const>(this->_factory->createOperand(
					p_rhs->getType(), p_lhs->toString()));
		p_lhs = std::move(cast);
	}
	result = std::unique_ptr<IOperand const>(*p_lhs + *p_rhs);
	this->_stack.push_back(result.get());
	result.release();
}
