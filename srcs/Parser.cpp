/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:22:19 by cledant           #+#    #+#             */
/*   Updated: 2017/05/11 16:23:21 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(void) : _cqueue(nullptr), _has_error(false), _has_exit(false), _has_stdin_exit(false)
{
	this->_cqueue = new CommandQueue();
}

Parser::~Parser(void)
{
	delete this->_cqueue;
}

Parser::Parser(Parser const &src) : _cqueue(nullptr), _has_error(src.getHasError()), _has_exit(src.getHasExit()), _has_stdin_exit(src.getHasStdinExit())
{
	this->_cqueue = new CommandQueue();
	this->_cqueue = src.getQueue();
}

Parser									&Parser::operator=(Parser const &rhs)
{
	this->_cqueue = rhs.getQueue();
	this->_has_error = rhs.getHasError();
	this->_has_exit = rhs.getHasExit();
	this->_has_stdin_exit = rhs.getHasStdinExit();
	return (*this);
}

bool					Parser::getHasError(void) const
{
	return (this->_has_error);
}

bool					Parser::getHasExit(void) const
{
	return (this->_has_exit);
}

bool					Parser::getHasStdinExit(void) const
{
	return (this->_has_stdin_exit);
}

CommandQueue			*Parser::getQueue(void) const
{
	return  (this->_cqueue);
}

void					Parser::parse_from_stdin(void)
{
	std::string		line;
	std::string		cpy_line;
	size_t			line_nb;
	bool			had_comment;

	line_nb = 1;
	while (std::getline(std::cin, line))
	{
		cpy_line = line;
		if (check_stdin_end(line))
		{
			this->_has_stdin_exit = true;
			break ;
		}
		had_comment = remove_comment(line);
		if (check_push(line, had_comment))
			create_token(I_PUSH, line);
		else if (check_pop(line, had_comment))
			create_token(I_POP, line);
		else if (check_assert(line, had_comment))
			create_token(I_ASSERT, line);
		else if (check_dump(line, had_comment))
			create_token(I_DUMP, line);
		else if (check_assert(line, had_comment))
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
			create_token(I_PRINT, line);
		else if (check_exit(line, had_comment))
			create_token(I_EXIT, line);
		else if (check_empty(line, had_comment))
			create_token(I_VALID_EMPTY, line);
		else
		{
			this->_has_error = true;
			std::cout << "Parse Error at line number " << line_nb << ". Line : " << cpy_line << std::endl;
		}
		line_nb++;
	}
	if (this->_has_stdin_exit == false)
	{
		this->_has_error = true;
		std::cout << "Parse Error : No exit sequence from stdin !" << std::endl;
	}
	if (this->_has_exit == false)
	{
		this->_has_error = true;
		std::cout << "Parse Error : No exit !" << std::endl;
	}
	if (this->_has_error)
		throw Parser::ParsingError();
}

void					Parser::parse_from_file(std::ifstream &ifs)
{
	std::string		line;
	std::string		cpy_line;
	size_t			line_nb;
	bool			had_comment;

	line_nb = 1;
	while (std::getline(ifs, line))
	{
		cpy_line = line;
		had_comment = remove_comment(line);
		if (check_push(line, had_comment))
			create_token(I_PUSH, line);
		else if (check_pop(line, had_comment))
			create_token(I_POP, line);
		else if (check_assert(line, had_comment))
			create_token(I_ASSERT, line);
		else if (check_dump(line, had_comment))
			create_token(I_DUMP, line);
		else if (check_assert(line, had_comment))
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
			create_token(I_PRINT, line);
		else if (check_exit(line, had_comment))
			create_token(I_EXIT, line);
		else if (check_empty(line, had_comment))
			create_token(I_VALID_EMPTY, line);
		else
		{
			this->_has_error = true;
			std::cout << "Parse Error at line number " << line_nb << ". Line : " << cpy_line << std::endl;
		}
		line_nb++;
	}
	if (this->_has_exit == false)
	{
		this->_has_error = true;
		std::cout << "Parse Error : No exit !" << std::endl;
	}
	if (this->_has_error)
		throw Parser::ParsingError();
}


bool				Parser::remove_comment(std::string &line) const
{
	size_t		pos;

	pos = line.find(";");
	if (pos == std::string::npos)
		return (false);
	line = line.substr(0, pos);
	return (true);
}

bool				Parser::check_push(std::string &line, bool has_comment) const
{
	std::regex		int_comment("^(push) (int8|int16|int32)\\([-]?\\d+\\)[\t ]*");
	std::regex		int_no_comment("^(push) (int8|int16|int32)\\([-]?\\d+\\)");
	std::regex		fp_comment("^(push) (float|double)\\([-]?\\d+\\.\\d+\\)[\t ]*");
	std::regex		fp_no_comment("^(push) (float|double)\\([-]?\\d+\\.\\d+\\)");

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

bool				Parser::check_pop(std::string &line, bool has_comment) const
{
	std::regex		got_comment("^(pop)[\t ]*");
	std::regex		no_comment("^(pop)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_dump(std::string &line, bool has_comment) const
{
	std::regex		got_comment("^(dump)[\t ]*");
	std::regex		no_comment("^(dump)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_assert(std::string &line, bool has_comment) const
{
	std::regex		int_comment("^(assert) (int8|int16|int32)\\([-]?\\d+\\)[\t ]*");
	std::regex		int_no_comment("^(assert) (int8|int16|int32)\\([-]?\\d+\\)");
	std::regex		fp_comment("^(assert) (float|double)\\([-]?\\d+(.\\d+)?\\)[\t ]*");
	std::regex		fp_no_comment("^(assert) (float|double)\\([-]?\\d+(.\\d+)?\\)");

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

bool				Parser::check_add(std::string &line, bool has_comment) const
{
	std::regex		got_comment("^(add)[\t ]*");
	std::regex		no_comment("^(add)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_sub(std::string &line, bool has_comment) const
{
	std::regex		got_comment("^(sub)[\t ]*");
	std::regex		no_comment("^(sub)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_mul(std::string &line, bool has_comment) const
{
	std::regex		got_comment("^(mul)[\t ]*");
	std::regex		no_comment("^(mul)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_div(std::string &line, bool has_comment) const
{
	std::regex		got_comment("^(div)[\t ]*");
	std::regex		no_comment("^(div)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_mod(std::string &line, bool has_comment) const
{
	std::regex		got_comment("^(mod)[\t ]*");
	std::regex		no_comment("^(mod)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_print(std::string &line, bool has_comment) const
{
	std::regex		got_comment("^(print)[\t ]*");
	std::regex		no_comment("^(print)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_exit(std::string &line, bool has_comment) const
{
	std::regex		got_comment("^(exit)[\t ]*");
	std::regex		no_comment("^(exit)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_empty(std::string &line, bool has_comment) const
{
	std::regex		got_comment("^[\t ]*");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	if (line.size() != 0)
		return (false);
	return (true);
}

bool				Parser::check_stdin_end(std::string &line) const
{
	std::regex		got_comment("^;;[\t ]*;.*");

	if (std::regex_match(line, got_comment))
		return (true);
	if (line.compare(";;") == 0)
		return (true);
	return (false);
}

void				Parser::create_token(eInstruction inst, std::string &line)
{
	Token		tok;

	token_creation_parse(tok, inst, line);
	if (inst == I_EXIT)
		this->_has_exit = true;
	this->_cqueue->push(tok);
}

void				Parser::token_creation_parse(Token &tok, eInstruction inst,
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

Parser::ParsingError::ParsingError(void)
{
		this->_msg = "Parse error : One or more errors have been detected. Aborting execution !";
}

Parser::ParsingError::~ParsingError(void) throw()
{
}
