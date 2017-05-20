/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:58:08 by cledant           #+#    #+#             */
/*   Updated: 2017/05/17 17:41:47 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Env.hpp"

Env::Env(void) : _ifs(nullptr), _stack(nullptr), _parser(nullptr), _filename(nullptr), _orig(KEYBOARD)
{
	try
	{
		this->_stack = new Stack();
		this->_parser = new Parser();
	}
	catch (std::exception &e)
	{
		delete this->_stack;
		delete this->_parser;
		throw Env::InitFailException();
	}
}

Env::~Env(void)
{
	if (this->_ifs)
		this->_ifs.close();
	delete this->_stack;
	delete this->_parser;
}

Env::Env(Env const &src) : _ifs(src.getFilename()), _stack(nullptr), _parser(nullptr), _filename(nullptr), _orig(src.getOrigin())
{
	if (this->_orig == FILES && !(this->_ifs))
		throw OpenFailException();
	try
	{
		this->_stack = new Stack();
		this->_parser = new Parser();
		this->_stack = const_cast<AStack *>(src.getStack());
	}
	catch (std::exception &e)
	{
		if (this->_ifs)
			this->_ifs.close();
		delete this->_stack;
		delete this->_parser;
		throw Env::InitFailException();
	}
}

Env									&Env::operator=(Env const &rhs)
{
	this->_stack = const_cast<AStack *>(rhs.getStack());
	this->_orig = rhs.getOrigin();
	this->_filename = rhs.getFilename();
	if (this->_ifs)
		this->_ifs.close();
	if (this->_orig == FILES)
	{
		this->_ifs.open(this->_filename);
		if (!(this->_ifs))
			throw OpenFailException();
	}
	return (*this);
}

Env::Env(char const *file) : _ifs(file), _stack(nullptr), _parser(nullptr), _filename(file), _orig(FILES)
{
	if (!(this->_ifs))
			throw OpenFailException();
	try
	{
		this->_stack = new Stack();
		this->_parser = new Parser();
	}
	catch (std::exception &e)
	{
		if (this->_ifs)
			this->_ifs.close();
		delete _stack;
		delete _parser;
		throw Env::InitFailException();
	}
}

eOrigin					Env::getOrigin(void) const
{
	return (this->_orig);
}

char const				*Env::getFilename(void) const
{
	return (this->_filename);
}

std::ifstream const		&Env::getIfs(void) const
{
	return (this->_ifs);
}

AStack const			*Env::getStack(void) const
{
	return (this->_stack);
}

void					Env::parse(void)
{
	if (this->_orig == KEYBOARD)
		this->_parser->parse_from_stdin();
	else
		this->_parser->parse_from_file(this->_ifs);
}

void					Env::execute_program(void)
{
	Token const			*queue_tok = nullptr;
	bool				loop = true;

	while (this->_parser->getQueue()->isEmpty() == false && loop == true)
	{
		queue_tok = this->_parser->getQueue()->getFront();
		switch (queue_tok->inst)
		{
			case I_PUSH :
				this->_stack->push(queue_tok->type, queue_tok->value);
				break ;
			case I_POP :
				this->_stack->pop();
				break ;
			case I_DUMP :
				this->_stack->dump();
				break ;
			case I_ASSERT :
				this->_stack->assert(queue_tok->type, queue_tok->value);
				break ;
			case I_ADD :
				this->_stack->add();
				break ;
			case I_SUB :
				this->_stack->sub();
				break ;
			case I_MUL :
				this->_stack->mul();
				break ;
			case I_DIV :
				this->_stack->div();
				break ;
			case I_MOD :
				this->_stack->mod();
				break ;
			case I_PRINT :
				this->_stack->print();
				break ;
			case I_EXIT :
				loop = false;
				break ;
			case I_VALID_EMPTY :
				break ;
		}
		this->_parser->getQueue()->pop();
	}
}

Env::InitFailException::InitFailException(void)
{
		this->_msg = "Error : Initialisation failed !";
}

Env::InitFailException::~InitFailException(void) throw()
{
}

Env::OpenFailException::OpenFailException(void)
{
		this->_msg = "Error : Can't open file !";
}

Env::OpenFailException::~OpenFailException(void) throw()
{
}
