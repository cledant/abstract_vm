/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:58:08 by cledant           #+#    #+#             */
/*   Updated: 2017/05/11 22:38:39 by cledant          ###   ########.fr       */
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
		throw std::runtime_error("Env : Init failed !");
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
		throw std::runtime_error("Env : Can't open file !");
	try
	{
		this->_stack = new Stack();
		this->_parser = new Parser();
		this->_cqueue = src.getQueue();
		this->_stack = const_cast<AStack *>(src.getStack());
	}
	catch (std::exception &e)
	{
		delete this->_stack;
		delete this->_parser;
		throw std::runtime_error("Env : Copy Init failed !");
	}
}

Env									&Env::operator=(Env const &rhs)
{
	this->_stack = const_cast<AStack *>(rhs.getStack());
	this->_cqueue = rhs.getQueue();
	this->_orig = rhs.getOrigin();
	this->_filename = rhs.getFilename();
	if (this->_ifs)
		this->_ifs.close();
	if (this->_orig == FILES)
	{
		this->_ifs.open(this->_filename);
		if (!(this->_ifs))
			throw std::runtime_error("Env : Can't open file !");
	}
	return (*this);
}

Env::Env(char const *file) : _ifs(file), _stack(nullptr), _parser(nullptr), _filename(file), _orig(FILES)
{
	if (!(this->_ifs))
		throw std::runtime_error("Env : Can't open file !");
	try
	{
		_stack = new Stack();
		_parser = new Parser();
	}
	catch (std::exception &e)
	{
		delete _stack;
		delete _parser;
		throw std::runtime_error("Env : Init failed !");
	}
}

eOrigin		Env::getOrigin(void) const
{
	return (this->_orig);
}

char const	*Env::getFilename(void) const
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

std::deque<Token const *> const		&Env::getQueue(void) const
{
	return  (this->_cqueue);
}

void		Env::parse_from_file(void)
{
	std::string		line;

	while (std::getline(this->_ifs, line))
	{
		std::cout << line << std::endl;
	}
}
