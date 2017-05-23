/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:22:19 by cledant           #+#    #+#             */
/*   Updated: 2017/05/23 13:49:16 by cledant          ###   ########.fr       */
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

void					Parser::parse(std::istream &ifs, eOrigin from)
{
	std::string		line;
	std::string		cpy_line;
	size_t			line_nb;
	bool			had_comment;

	line_nb = 1;
	while (std::getline(ifs, line))
	{
		cpy_line = line;
		if (from == KEYBOARD && check_stdin_end(line))
		{
			this->_has_stdin_exit = true;
			break ;
		}
		had_comment = remove_comment(line);
		parse_line(line, line_nb, had_comment);
		line_nb++;
/*		if (check_push(line, had_comment))
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
		}*/
	}
	if (from == KEYBOARD && this->_has_stdin_exit == false)
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

void				Parser::check_line(std::string &line, size_t line_nb,
						bool had_comment)
{
	if (!check_instruction(line, line_nb))
		return ;
	std::cout << "OK" << std::endl;
	(void)had_comment;
}

bool				Parser::check_instruction(std::string &line, size_t line_nb)
{
	std::regex	instr("^[\t ]*(push|pop|dump|assert|add|sub|mul|div|mod|print|exit)\\b.*");
	std::regex	empty("^[\t ]*$");

	if (line.size() == 0)
		return (true);
	else if (std::regex_match(line, empty))
		return (true);
	else if (!std::regex_match(line, instr))
	{
		std::cout << "Error on line " << line_nb << " : Unknown instruction !" <<
			std::endl;
		this->_has_error = true;
		return (false);
	}
	return (true);
}

void				Parser::parse_line(std::string &line, size_t line_nb,
						bool had_comment)
{
	size_t	c = 0;
	std::vector<std::regex> reg_array = {std::regex("^[\t ]*push\\b.*"),
		std::regex("^[\t ]*pop\\b.*"), std::regex("^[\t ]*dump\\b.*"),
		std::regex("^[\t ]*assert\\b.*"), std::regex("^[\t ]*add\\b.*"),
		std::regex("^[\t ]*sub\\b.*"), std::regex("^[\t ]*mul\\b.*"),
		std::regex("^[\t ]*div\\b.*"), std::regex("^[\t ]*mod\\b.*"),
		std::regex("^[\t ]*print\\b.*"), std::regex("^[\t ]*exit\\b.*"),
		std::regex("[\t ]*$")};
	bool	(Parser::*fct[12])(std::string &, bool) = {&Parser::check_push,
				&Parser::check_pop, &Parser::check_dump, &Parser::check_assert,
				&Parser::check_add, &Parser::check_sub, &Parser::check_mul,
				&Parser::check_div, &Parser::check_mod, &Parser::check_print,
				&Parser::check_exit, &Parser::check_empty};
	std::vector<std::regex>::iterator		it;

	for(it = reg_array.begin(); it != reg_array.end(); ++it)
	{
		if (std::regex_match(line, *it))
		{
			(this->*fct[c])(line, had_comment);
			return ;
		}
		++c;
	}
	std::cout << "Error on line " << line_nb << " : Unknown instruction !" <<
		std::endl;
	this->_has_error = true;
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

bool				Parser::check_push(std::string &line, bool has_comment)
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

bool				Parser::check_pop(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(pop)[\t ]*");
	std::regex		no_comment("^(pop)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_dump(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(dump)[\t ]*");
	std::regex		no_comment("^(dump)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_assert(std::string &line, bool has_comment)
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

bool				Parser::check_add(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(add)[\t ]*");
	std::regex		no_comment("^(add)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_sub(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(sub)[\t ]*");
	std::regex		no_comment("^(sub)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_mul(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(mul)[\t ]*");
	std::regex		no_comment("^(mul)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_div(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(div)[\t ]*");
	std::regex		no_comment("^(div)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_mod(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(mod)[\t ]*");
	std::regex		no_comment("^(mod)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_print(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(print)[\t ]*");
	std::regex		no_comment("^(print)");

	if (has_comment)
		return (std::regex_match(line, got_comment));
	return (std::regex_match(line, no_comment));
}

bool				Parser::check_exit(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(exit)[\t ]*");
	std::regex		no_comment("^(exit)");

	if (has_comment)
	{
		if (std::regex_match(line, got_comment))
		{
			create_token(I_EXIT, line);
			return (true);
		}
		return (false);
	}
	if (std::regex_match(line, no_comment))
	{
		create_token(I_EXIT, line);
		return (true);
	}
	return (false);
}

bool				Parser::check_empty(std::string &line, bool has_comment)
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
