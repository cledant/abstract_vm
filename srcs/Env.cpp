/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:58:08 by cledant           #+#    #+#             */
/*   Updated: 2017/05/11 16:38:23 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Env.hpp"

Env::Env(void) : _ifs(nullptr), _stack(nullptr), /*_cqueue(nullptr),*/ _parser(nullptr), _filename(nullptr), _orig(KEYBOARD)
{
	try
	{
		this->_stack = new Stack();
//		this->_cqueue = new CommandQueue(void);
		this->_parser = new Parser();
	}
	catch (std::exception &e)
	{
		delete this->_stack;
//		delete this->_cqueue;
		delete this->_parser;
		throw std::runtime_error("Env : Init failed !");
	}
}

Env::~Env(void)
{
	if (this->_ifs)
		this->_ifs.close();
	delete this->_stack;
//	delete this->_cqueue;
	delete this->_parser;
}

Env::Env(Env const &src) : _ifs(src.getFilename()), _stack(nullptr),/* _cqueue(nullptr),*/ _parser(nullptr), _filename(src.getFilename()), _orig(src.getOrigin())
{
	if (this->_orig == FILES && !(this->_ifs))
		throw std::runtime_error("Env : Can't open file !");
	try
	{
		this->_stack = new Stack();
//		this->_cqueue = new CommandQueue(void);
		this->_parser = new Parser();
	}
	catch (std::exception &e)
	{
		delete this->_stack;
//		delete this->_cqueue;
		delete this->_parser;
		throw std::runtime_error("Env : Init by copy failed !");
	}
}

Env									&Env::operator=(Env const &rhs)
{
	(void)rhs;
	return (*this);
}

Env::Env(char const *file) : _ifs(file), _stack(nullptr),/* _cqueue(nullptr),*/ _parser(nullptr), _filename(file), _orig(FILES)
{
	if (!(this->_ifs))
		throw std::runtime_error("Env : Can't open file !");
	try
	{
		_stack = new Stack();
//		_cqueue = new CommandQueue(void);
		_parser = new Parser();
	}
	catch (std::exception &e)
	{
		delete _stack;
//		delete _cqueue;
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

void		Env::parse_from_file(void)
{
	std::cout << "Oki" << std::endl;
}
