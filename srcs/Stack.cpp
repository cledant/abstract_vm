/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:01:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/09 13:18:42 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Stack.hpp"
#include "abstract_vm_defines.hpp"

Stack::Stack(void) : _cast(nullptr)
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

	if (this->_stack.size() < 2)
		throw std::exception("Stack : Add : Not enough elemets in stack");
	lhs = this->_stack.rbegin();
	this->_stack.pop_back();
	rhs = this->_stack.rbegin();
	this->_stack.pop_back();
	if ((*lhs)->getType() == (*rhs)->getType())
		this->do_operation(*lhs, *rhs, (*rhs)->getType(), NO_CAST, ADD);
	else if ((*lhs)->getType() > (*rhs)->getType())
		this->do_operation(*lhs, *rhs, (*lhs)->getType(), CAST_RHS, ADD);
	else
		this->do_operation(*lhs, *rhs, (*rhs)->getType(), CAST_LHS, ADD);
}

void		Stack::do_operation(IOperand const *lhs, IOperand const *rhs,
				eOperandType type, eCast cast, eOperator op)
{
	switch (op)
	{
		case ADD :
			this->do_add(lhs, rhs, cast, type);
			break ;
		case SUB :
			this->do_add(lhs, rhs, cast, type);
			break ;
		case MUL :
			this->do_add(lhs, rhs, cast, type);
			break ;
		case DIV :
			this->do_add(lhs, rhs, cast, type);
			break ;
		case MOD :
			this->do_add(lhs, rhs, cast, type);
			break ;
	}
}

void		Stack::do_add(IOperand const *lhs, IOperand const *rhs,
				eCast cast, eOperandType type)
{
	std::unique_ptr<IOperand>		p_lhs = nullptr;
	std::unique_ptr<IOperand>		p_rhs = nullptr;
	std::unique_ptr<IOperand>		cast = nullptr;

	p_lhs = std::unique_ptr<IOperand>(lhs);
	p_rhs = std::unique_ptr<IOperand>(rhs);
	if (cast == CAST_LHS)
	{
		cast = std::unique_ptr<IOperand>(this->createOperand(type,
					p_lhs->toString()));
		p_lhs = std::move(cast);
	}
	else if (cast == CAST_RHS)
	{
		cast = std::unique_ptr<IOperand>(this->createOperand(type,
					p_rhs->toString()));
		p_rhs = std::move(cast);
	}
	switch (op)
	{
		case ADD :
			this->do_add(lhs, rhs, type);
			break ;
		case SUB :
			this->do_add(lhs, rhs, type);
			break ;
		case MUL :
			this->do_add(lhs, rhs, type);
			break ;
		case DIV :
			this->do_add(lhs, rhs, type);
			break ;
		case MOD :
			this->do_add(lhs, rhs, type);
			break ;
	}
}
