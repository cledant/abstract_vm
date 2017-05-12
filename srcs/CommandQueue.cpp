/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandQueue.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 10:52:24 by cledant           #+#    #+#             */
/*   Updated: 2017/05/12 11:29:13 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandQueue.hpp"

CommandQueue::CommandQueue(void)
{
}

CommandQueue::~CommandQueue(void)
{
	std::deque<Token const *>::iterator		it;

	for(it = this->_stack.begin(); it != this->_stack.end(); ++it)
		delete *it;
}

CommandQueue::CommandQueue(CommandQueue const &src)
{
	std::deque<Token const *>::const_iterator			it;
	Token const											*cpy;

	for(it = src.getStack().cbegin(); it != src.getStack().cend(); ++it)
	{
		cpy = new Token((*it)->inst, (*it)->type, (*it)->value.c_str());
		this->_stack.push_back(cpy);
	}
}

CommandQueue					&CommandQueue::operator=(CommandQueue const &rhs)
{
	std::deque<Token const *>::const_iterator			it;
	Token const											*cpy;

	for(it = this->_stack.cbegin(); it != this->_stack.cend(); ++it)
		delete *it;
	this->_stack.clear();
	for(it = rhs.getStack().cbegin(); it != rhs.getStack().cend(); ++it)
	{
		cpy = new Token((*it)->inst, (*it)->type, (*it)->value.c_str());
		this->_stack.push_back(cpy);
	}
	return (*this);
}

std::deque<Token const *> const		&CommandQueue::getStack(void) const
{
	return (this->_stack);
}

void								CommandQueue::pop(void)
{
	Token const		*pop;

	pop = this->getFront();
	delete pop;
	this->_stack.pop_front();
}

Token const							*CommandQueue::getFront(void)
{
	if (this->_stack.empty() == true)
		throw std::runtime_error("CommandQueue is Empty");
	return (this->_stack.front());
}
