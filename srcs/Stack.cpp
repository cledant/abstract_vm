/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:01:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/25 12:50:51 by cledant          ###   ########.fr       */
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

	op.reset(this->_factory->createOperand(type, value));
	this->_stack.push_back(op.get());
	op.release();
}

void		Stack::pop(void)
{
	std::vector<IOperand const *>::reverse_iterator		rit;

	if (this->_stack.empty() == true)
		throw Stack::EmptyStackException();
	rit = this->_stack.rbegin();
	this->_stack.pop_back();
	delete *rit;
}

void		Stack::dump(void)
{
	std::vector<IOperand const *>::reverse_iterator		rit;

	for(rit = this->_stack.rbegin(); rit != this->_stack.rend(); ++rit)
		std::cout << (*rit)->toString() << std::endl;
}

void		Stack::assert(eOperandType type, std::string const &value)
{
	std::vector<IOperand const *>::reverse_iterator		rit;
	std::unique_ptr<IOperand const>						check = nullptr;

	if (this->_stack.empty() == true)
		throw Stack::EmptyStackException();
	rit = this->_stack.rbegin();
	try
	{
		check.reset(this->_factory->createOperand(type, value));
	}
	catch (OperandFactory::OverflowException &e)
	{
		throw Stack::AssertInvalidValueException();
	}
	catch (OperandFactory::UnderflowException &e)
	{
		throw Stack::AssertInvalidValueException();
	}
	if ((*rit)->getType() != check->getType())
		throw Stack::AssertDifferentTypeException();
	if (this->assert_value(*rit, check.get()) == false)
		throw Stack::AssertDifferentValueException();
}

void		Stack::add(void)
{
	this->do_operation(ADD);
}

void		Stack::sub(void)
{
	this->do_operation(SUB);
}

void		Stack::mul(void)
{
	this->do_operation(MUL);
}

void		Stack::div(void)
{
	this->do_operation(DIV);
}

void		Stack::mod(void)
{
	this->do_operation(MOD);
}

void		Stack::print(void)
{
	std::vector<IOperand const *>::reverse_iterator		rit;

	if (this->_stack.empty() == true)
		throw Stack::EmptyStackException();
	rit = this->_stack.rbegin();
	if ((*rit)->getType() != Int8)
		throw Stack::NotInt8Exception();
	if (std::isprint(dynamic_cast<OperandInt8 const *>(*rit)->getValue()))
		std::cout << dynamic_cast<OperandInt8 const *>(*rit)->getValue();
}

eOperandType		Stack::resulting_operand_type(IOperand const *lhs,
						IOperand const *rhs)
{
	if (lhs->getType() > rhs->getType())
		return (lhs->getType());
	return (rhs->getType());
}


void		Stack::do_operation(eOperator op)
{
	std::vector<IOperand const *>::reverse_iterator		lhs;
	std::vector<IOperand const *>::reverse_iterator		rhs;
	std::unique_ptr<IOperand const>						p_lhs;
	std::unique_ptr<IOperand const>						p_rhs;
	std::unique_ptr<IOperand const>						cast;
	std::unique_ptr<IOperand const>						result;
	eOperandType										cast_type;

	if (this->_stack.size() < 2)
		throw Stack::NotEnoughElementException();
	rhs = this->_stack.rbegin();
	this->_stack.pop_back();
	lhs = this->_stack.rbegin();
	this->_stack.pop_back();
	p_lhs.reset(*lhs);
	p_rhs.reset(*rhs);
	cast_type = resulting_operand_type(p_lhs.get(), p_rhs.get());
	if (p_rhs->getType() != cast_type)
	{
		cast.reset(this->_factory->createOperand(cast_type, p_rhs->toString()));
		p_rhs = std::move(cast);
	}
	else if (p_lhs->getType() != cast_type)
	{
		cast.reset(this->_factory->createOperand(cast_type, p_lhs->toString()));
		p_lhs = std::move(cast);
	}
	switch (op)
	{
		case ADD :
			result.reset(*p_lhs + *p_rhs);
			break ;
		case SUB :
			result.reset(*p_lhs - *p_rhs);
			break ;
		case MUL :
			result.reset(*p_lhs * *p_rhs);
			break ;
		case DIV :
			result.reset(*p_lhs / *p_rhs);
			break ;
		case MOD :
			result.reset(*p_lhs % *p_rhs);
			break ;
	}
	this->_stack.push_back(result.get());
	result.release();
}

bool		Stack::assert_value(IOperand const *lhs, IOperand const *rhs)
{
	if (lhs->getType() == Int8)
	{
		if (dynamic_cast<OperandInt8 const *>(lhs)->getValue() ==
				dynamic_cast<OperandInt8 const *>(rhs)->getValue())
			return (true);
	}
	else if (lhs->getType() == Int16)
	{
		if (dynamic_cast<OperandInt16 const *>(lhs)->getValue() ==
				dynamic_cast<OperandInt16 const *>(rhs)->getValue())
			return (true);
	}
	else if (lhs->getType() == Int32)
	{
		if (dynamic_cast<OperandInt32 const *>(lhs)->getValue() ==
				dynamic_cast<OperandInt32 const *>(rhs)->getValue())
			return (true);
	}
	else if (lhs->getType() == Float)
	{
		if (dynamic_cast<OperandFloat const *>(lhs)->getValue() ==
				dynamic_cast<OperandFloat const *>(rhs)->getValue())
			return (true);
	}
	else if (lhs->getType() == Double)
	{
		if (dynamic_cast<OperandDouble const *>(lhs)->getValue() ==
				dynamic_cast<OperandDouble const*>(rhs)->getValue())
			return (true);
	}
	return (false);
}

Stack::EmptyStackException::EmptyStackException(void)
{
		this->_msg = "Runtime Exception : Stack : Stack is empty !";
}

Stack::EmptyStackException::~EmptyStackException(void) throw()
{
}

Stack::NotEnoughElementException::NotEnoughElementException(void)
{
		this->_msg = "Runtime Exception : Stack : Not enough elements in stack for requested instruction !";
}

Stack::NotEnoughElementException::~NotEnoughElementException(void) throw()
{
}

Stack::AssertInvalidValueException::AssertInvalidValueException(void)
{
		this->_msg = "Runtime Exception : Stack : Value to assert is invalid !";
}

Stack::AssertInvalidValueException::~AssertInvalidValueException(void) throw()
{
}

Stack::AssertDifferentTypeException::AssertDifferentTypeException(void)
{
		this->_msg = "Runtime Exception : Stack : Top stack type is different from assert !";
}

Stack::AssertDifferentTypeException::~AssertDifferentTypeException(void) throw()
{
}

Stack::AssertDifferentValueException::AssertDifferentValueException(void)
{
		this->_msg = "Runtime Exception : Stack : Top stack value is different from assert !";
}

Stack::AssertDifferentValueException::~AssertDifferentValueException(void) throw()
{
}

Stack::NotInt8Exception::NotInt8Exception(void)
{
		this->_msg = "Runtime Exception : Stack : Top stack type is not printable !";
}

Stack::NotInt8Exception::~NotInt8Exception(void) throw()
{
}
