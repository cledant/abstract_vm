/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:58:08 by cledant           #+#    #+#             */
/*   Updated: 2017/05/16 16:12:11 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Env.hpp"

Env::Env(void) : _ifs(nullptr), _stack(nullptr), _cqueue(nullptr), _parser(nullptr), _filename(nullptr), _orig(KEYBOARD), _has_error(false), _has_exit(false)
{
	try
	{
		this->_stack = new Stack();
		this->_cqueue = new CommandQueue();
		this->_parser = new Parser();
	}
	catch (std::exception &e)
	{
		delete this->_stack;
		delete this->_cqueue;
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
	delete this->_cqueue;
}

Env::Env(Env const &src) : _ifs(src.getFilename()), _stack(nullptr), _cqueue(nullptr), _parser(nullptr), _filename(nullptr), _orig(src.getOrigin()), _has_error(src.getHasError()), _has_exit(src.getHasExit())
{
	if (this->_orig == FILES && !(this->_ifs))
		throw std::runtime_error("Env : Can't open file !");
	try
	{
		this->_stack = new Stack();
		this->_parser = new Parser();
		this->_cqueue = new CommandQueue();
		this->_cqueue = const_cast<CommandQueue *>(src.getQueue());
		this->_stack = const_cast<AStack *>(src.getStack());
	}
	catch (std::exception &e)
	{
		delete this->_stack;
		delete this->_parser;
		delete this->_cqueue;
		throw std::runtime_error("Env : Copy Init failed !");
	}
}

Env									&Env::operator=(Env const &rhs)
{
	this->_stack = const_cast<AStack *>(rhs.getStack());
	this->_cqueue = const_cast<CommandQueue *>(rhs.getQueue());
	this->_orig = rhs.getOrigin();
	this->_filename = rhs.getFilename();
	this->_has_error = rhs.getHasError();
	this->_has_exit = rhs.getHasExit();
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

Env::Env(char const *file) : _ifs(file), _stack(nullptr), _cqueue(nullptr), _parser(nullptr), _filename(file), _orig(FILES), _has_error(false), _has_exit(false)
{
	if (!(this->_ifs))
		throw std::runtime_error("Env : Can't open file !");
	try
	{
		this->_stack = new Stack();
		this->_cqueue = new CommandQueue();
		this->_parser = new Parser();
	}
	catch (std::exception &e)
	{
		delete _stack;
		delete _parser;
		delete _cqueue;
		throw std::runtime_error("Env : Init failed !");
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

CommandQueue const		*Env::getQueue(void) const
{
	return  (this->_cqueue);
}

bool					Env::getHasError(void) const
{
	return (this->_has_error);
}

bool					Env::getHasExit(void) const
{
	return (this->_has_exit);
}

void					Env::parse_from_file(void)
{
	std::string		line;
	std::string		cpy_line;
	size_t			line_nb;
	bool			had_comment;

	line_nb = 1;
	while (std::getline(this->_ifs, line))
	{
		cpy_line = line;
		had_comment = remove_comment(line);
		if (check_push(line, had_comment))
			create_token(I_PUSH, line);
/*		else if (check_pop(line, had_comment))
			create_token(I_POP, line);
		else if (check_assert(line, had_comment))
			create_token(I_ASSERT, line);*/
		else if (check_dump(line, had_comment))
			create_token(I_DUMP, line);
/*		else if (check_assert(line, had_comment))
			create_token(I_ASSERT, line);
		else if (check_add(line, had_comment))
			create_token(I_ADD, line);
		else if (check_sub(line, had_comment))
			create_token(I_SUB, line);
		else if (check_sub(line, had_comment))
			create_token(I_SUB, line);
		else if (check_div(line, had_comment))
			create_token(I_DIV, line);
		else if (check_mul(line, had_comment))
			create_token(I_MUL, line);
		else if (check_mod(line, had_comment))
			create_token(I_MOD, line);
		else if (check_print(line, had_comment))
			create_token(I_PRINT, line);*/
		else if (check_exit(line, had_comment))
			create_token(I_EXIT, line);
/*		else if (check_empty(line, had_comment))
			create_token(I_VALID_EMPTY, line);*/
		else
			std::cout << "Parse Error at line number " << line_nb << ". Line : " << cpy_line << std::endl;
		line_nb++;
	}
	if (this->_has_exit == false)
		throw std::runtime_error("Parse Error : No exit !");
	if (this->_has_error)
		throw std::runtime_error("Parse Error : Error in program !");
}

void					Env::execute_program(void)
{
	Token const			*queue_tok = nullptr;
	bool				loop = true;

	while (this->_cqueue->isEmpty() == false && loop == true)
	{
		queue_tok = this->_cqueue->getFront();
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
				this->_stack->push(queue_tok->type, queue_tok->value);
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
		}
		this->_cqueue->pop();
	}
}

bool				Env::remove_comment(std::string &line) const
{
	size_t		pos;

	pos = line.find(";");
	if (pos == std::string::npos)
		return (false);
	line = line.substr(0, pos);
	return (true);
}

bool				Env::check_push(std::string &line, bool has_comment) const
{
	std::regex		int_comment("^(push) (int8|int16|int32)\\([-]?\\d+\\)[\t ]*");
	std::regex		int_no_comment("^(push) (int8|int16|int32)\\([-]?\\d+\\)");
	std::regex		fp_comment("^(push) (float|double)\\([-]?\\d+(.\\d+)?\\)[\t ]*");
	std::regex		fp_no_comment("^(push) (float|double)\\([-]?\\d+(.\\d+)?\\)");

	if (has_comment)
	{
		if (std::regex_match(line, int_comment) == true)
			return (true);
		if (std::regex_match(line, fp_comment) == true)
			return (true);
	}
	else
	{
		if (std::regex_match(line, int_no_comment) == true)
			return (true);
		if (std::regex_match(line, fp_no_comment) == true)
			return (true);
	}
	return (false);
}

bool				Env::check_dump(std::string &line, bool has_comment) const
{
	std::regex		got_comment("^(dump)[\t ]*");
	std::regex		no_comment("^(dump)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Env::check_exit(std::string &line, bool has_comment) const
{
	std::regex		got_comment("^(exit)[\t ]*");
	std::regex		no_comment("^(exit)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

void				Env::create_token(eInstruction inst, std::string &line)
{
	Token		tok;

	token_creation_parse(tok, inst, line);
	if (inst == I_EXIT)
		this->_has_exit = true;
	this->_cqueue->push(tok);
}

void				Env::token_creation_parse(Token &tok, eInstruction inst,
						std::string &line)
{
	size_t		op_pos;
	size_t		begin_pos;
	size_t		end_pos;

	tok.inst = inst;
	tok.type = Int8;
	tok.value = "0";
	if (inst == I_PUSH || inst == I_ASSERT)
	{
		if ((op_pos = line.find("int8")) != std::string::npos)
			tok.type = Int8;
		else if ((op_pos = line.find("int16")) != std::string::npos)
			tok.type = Int16;
		else if ((op_pos = line.find("int32")) != std::string::npos)
			tok.type = Int32;
		else if ((op_pos = line.find("float")) != std::string::npos)
			tok.type = Float;
		else if ((op_pos = line.find("double")) != std::string::npos)
			tok.type = Double;
		begin_pos = line.find("(");
		end_pos = line.find(")");
		tok.value = line.substr(begin_pos + 1, end_pos - 1 - begin_pos);
	}
}
