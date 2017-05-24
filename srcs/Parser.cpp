/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:22:19 by cledant           #+#    #+#             */
/*   Updated: 2017/05/24 11:40:29 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(void) : _cqueue(nullptr), _has_error(false), _has_exit(false), _has_stdin_exit(false), _line_nb(1)
{
	this->_cqueue = new CommandQueue();
}

Parser::~Parser(void)
{
	delete this->_cqueue;
}

Parser::Parser(Parser const &src) : _cqueue(nullptr), _has_error(src.getHasError()), _has_exit(src.getHasExit()), _has_stdin_exit(src.getHasStdinExit()), _line_nb(src.getCurrentLine())
{
	this->_cqueue = new CommandQueue();
	this->_cqueue = src.getQueue();
}

Parser					&Parser::operator=(Parser const &rhs)
{
	this->_cqueue = rhs.getQueue();
	this->_has_error = rhs.getHasError();
	this->_has_exit = rhs.getHasExit();
	this->_has_stdin_exit = rhs.getHasStdinExit();
	this->_line_nb = rhs.getCurrentLine();
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

size_t					Parser::getCurrentLine(void) const
{
	return (this->_line_nb);
}

void					Parser::parse(std::istream &ifs, eOrigin from)
{
	std::string		line;
	std::string		cpy_line;
	bool			had_comment;

	while (std::getline(ifs, line))
	{
		cpy_line = line;
		if (from == KEYBOARD && check_stdin_end(line))
		{
			this->_has_stdin_exit = true;
			break ;
		}
		had_comment = this->remove_comment(line);
		this->parse_line(line, had_comment);
		this->_line_nb++;
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

void				Parser::parse_line(std::string &line, bool had_comment)
{
	size_t	c = 0;
	std::vector<std::regex> reg_array = {std::regex("^[\t ]*push\\b.*"),
		std::regex("^[\t ]*pop\\b.*"), std::regex("^[\t ]*dump\\b.*"),
		std::regex("^[\t ]*assert\\b.*"), std::regex("^[\t ]*add\\b.*"),
		std::regex("^[\t ]*sub\\b.*"), std::regex("^[\t ]*mul\\b.*"),
		std::regex("^[\t ]*div\\b.*"), std::regex("^[\t ]*mod\\b.*"),
		std::regex("^[\t ]*print\\b.*"), std::regex("^[\t ]*exit\\b.*"),
		std::regex("[\t ]*$")};
	bool	(Parser::*fct[12])(std::string &, bool) =
				{&Parser::check_push, &Parser::check_pop, &Parser::check_dump,
				&Parser::check_assert, &Parser::check_add, &Parser::check_sub,
				&Parser::check_mul, &Parser::check_div, &Parser::check_mod,
				&Parser::check_print, &Parser::check_exit, &Parser::check_empty};
	std::vector<std::regex>::iterator		it;

	for (it = reg_array.begin(); it != reg_array.end(); ++it)
	{
		if (std::regex_match(line, *it))
		{
			(this->*fct[c])(line, had_comment);
			return ;
		}
		++c;
	}
	std::cout << "Error on line " << this->_line_nb << " : Unknown instruction !" <<
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
	std::regex	syntax_comment("^(push) (.+)\\(.+\\)[\t ]*");
	std::regex	syntax_no_comment("^(push) (.+)\\(.+\\)");
	if ((has_comment && std::regex_match(line, syntax_comment)) ||
				std::regex_match(line, syntax_no_comment))
	{
		if (this->create_token(I_PUSH, line))
			return (false);
		return (true);
	}
	this->_has_error = true;
	std::cout << "Error on line " << this->_line_nb << " : Syntax Error !" <<
		std::endl;
	return (false);
}

bool				Parser::check_pop(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(pop)[\t ]*");
	std::regex		no_comment("^(pop)");

	if (has_comment)
	{
		if (std::regex_match(line, got_comment))
		{
			this->create_token(I_POP, line);
			return (true);
		}
	}
	else if (std::regex_match(line, no_comment))
	{
		this->create_token(I_POP, line);
		return (true);
	}
	this->_has_error = true;
	std::cout << "Error on line " << this->_line_nb << " : Syntax Error !" <<
		std::endl;
	return (false);
}

bool				Parser::check_dump(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(dump)[\t ]*");
	std::regex		no_comment("^(dump)");

	if (has_comment)
	{
		if (std::regex_match(line, got_comment))
		{
			this->create_token(I_DUMP, line);
			return (true);
		}
	}
	else if (std::regex_match(line, no_comment))
	{
		this->create_token(I_DUMP, line);
		return (true);
	}
	this->_has_error = true;
	std::cout << "Error on line " << this->_line_nb << " : Syntax Error !" <<
		std::endl;
	return (false);
}

bool				Parser::check_assert(std::string &line, bool has_comment)
{
	std::regex		int_comment("^(assert) (int8|int16|int32)\\([-]?\\d+\\)[\t ]*");
	std::regex		int_no_comment("^(assert) (int8|int16|int32)\\([-]?\\d+\\)");
	std::regex		fp_comment("^(assert) (float|double)\\([-]?\\d+(\\.\\d+)\\)[\t ]*");
	std::regex		fp_no_comment("^(assert) (float|double)\\([-]?\\d+(\\.\\d+)\\)");

	if (has_comment)
	{
		if (std::regex_match(line, int_comment) ||
				std::regex_match(line, fp_comment))
		{
			this->create_token(I_ASSERT, line);
			return (true);
		}
	}
	else
	{
		if (std::regex_match(line, int_no_comment) ||
				std::regex_match(line, fp_no_comment))
		{
			this->create_token(I_ASSERT, line);
			return (true);
		}
	}
	this->_has_error = true;
	std::cout << "Error on line " << this->_line_nb << " : Syntax Error !" <<
		std::endl;
	return (false);
}

bool				Parser::check_add(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(add)[\t ]*");
	std::regex		no_comment("^(add)");

	if (has_comment)
	{
		if (std::regex_match(line, got_comment))
		{
			this->create_token(I_ADD, line);
			return (true);
		}
	}
	else if (std::regex_match(line, no_comment))
	{
		this->create_token(I_ADD, line);
		return (true);
	}
	this->_has_error = true;
	std::cout << "Error on line " << this->_line_nb << " : Syntax Error !" <<
		std::endl;
	return (false);
}

bool				Parser::check_sub(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(sub)[\t ]*");
	std::regex		no_comment("^(sub)");

	if (has_comment)
	{
		if (std::regex_match(line, got_comment))
		{
			this->create_token(I_SUB, line);
			return (true);
		}
	}
	else if (std::regex_match(line, no_comment))
	{
		this->create_token(I_SUB, line);
		return (true);
	}
	this->_has_error = true;
	std::cout << "Error on line " << this->_line_nb << " : Syntax Error !" <<
		std::endl;
	return (false);
}

bool				Parser::check_mul(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(mul)[\t ]*");
	std::regex		no_comment("^(mul)");

	if (has_comment)
	{
		if (std::regex_match(line, got_comment))
		{
			this->create_token(I_MUL, line);
			return (true);
		}
	}
	else if (std::regex_match(line, no_comment))
	{
		this->create_token(I_MUL, line);
		return (true);
	}
	this->_has_error = true;
	std::cout << "Error on line " << this->_line_nb << " : Syntax Error !" <<
		std::endl;
	return (false);
}

bool				Parser::check_div(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(div)[\t ]*");
	std::regex		no_comment("^(div)");

	if (has_comment)
	{
		if (std::regex_match(line, got_comment))
		{
			this->create_token(I_DIV, line);
			return (true);
		}
	}
	else if (std::regex_match(line, no_comment))
	{
		this->create_token(I_DIV, line);
		return (true);
	}
	this->_has_error = true;
	std::cout << "Error on line " << this->_line_nb << " : Syntax Error !" <<
		std::endl;
	return (false);
}

bool				Parser::check_mod(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(mod)[\t ]*");
	std::regex		no_comment("^(mod)");

	if (has_comment)
	{
		if (std::regex_match(line, got_comment))
		{
			this->create_token(I_MOD, line);
			return (true);
		}
	}
	else if (std::regex_match(line, no_comment))
	{
		this->create_token(I_MOD, line);
		return (true);
	}
	this->_has_error = true;
	std::cout << "Error on line " << this->_line_nb << " : Syntax Error !" <<
		std::endl;
	return (false);
}

bool				Parser::check_print(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(print)[\t ]*");
	std::regex		no_comment("^(print)");

	if (has_comment)
	{
		if (std::regex_match(line, got_comment))
		{
			this->create_token(I_PRINT, line);
			return (true);
		}
	}
	else if (std::regex_match(line, no_comment))
	{
		this->create_token(I_PRINT, line);
		return (true);
	}
	this->_has_error = true;
	std::cout << "Error on line " << this->_line_nb << " : Syntax Error !" <<
		std::endl;
	return (false);
}

bool				Parser::check_exit(std::string &line, bool has_comment)
{
	std::regex		got_comment("^(exit)[\t ]*");
	std::regex		no_comment("^(exit)");

	if (has_comment)
	{
		if (std::regex_match(line, got_comment))
		{
			this->create_token(I_EXIT, line);
			return (true);
		}
	}
	else if (std::regex_match(line, no_comment))
	{
		this->create_token(I_EXIT, line);
		return (true);
	}
	this->_has_error = true;
	std::cout << "Error on line " << this->_line_nb << " : Syntax Error !" <<
		std::endl;
	return (false);
}

bool				Parser::check_empty(std::string &line, bool has_comment)
{
	std::regex		got_comment("^[\t ]*");

	if (has_comment)
	{
		if (std::regex_match(line, got_comment))
		{
			this->create_token(I_VALID_EMPTY, line);
			return (true);
		}
	}
	else if (line.size() == 0)
	{
		this->create_token(I_VALID_EMPTY, line);
		return (true);
	}
	this->_has_error = true;
	std::cout << "Error on line " << this->_line_nb << " : Syntax Error !" <<
		std::endl;
	return (false);
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

bool				Parser::create_token(eInstruction inst, std::string &line)
{
	Token		tok;

	if (!this->token_creation_parse(tok, inst, line))
		return (false);
	if (inst == I_EXIT)
		this->_has_exit = true;
	this->_cqueue->push(tok);
	return (true);
}

bool				Parser::token_creation_parse(Token &tok, eInstruction inst,
						std::string &line)
{
	size_t		op_pos;
	size_t		begin_pos;
	size_t		end_pos;
	std::regex	int_check("^(push|assert) (int8|int16|int32)\\([-]?\\d+\\)[\t ]*");
	std::regex	fp_check("^(push|assert) (float|double)\\([-]?\\d+(\\.\\d+)\\)[\t ]*");
	std::regex	lexical_check("^(push|assert) (int8|int16|int32|float|double)\\(.+\\)[\t ]*");

	tok.inst = inst;
	tok.type = Int8;
	tok.value = "0";
	if (inst == I_PUSH || inst == I_ASSERT)
	{
		if (!std::regex_match(line, lexical_check))
		{
			this->_has_error = true;
			std::cout << "Error on line " << this->_line_nb << " : Lexical Error !"
				<< std::endl;
			return (false);
		}
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
		if (tok.type == Int8 || tok.type == Int16 || tok.type == Int32)
		{
			if (!std::regex_match(line, int_check))
			{
				this->_has_error = true;
				std::cout << "Error on line " << this->_line_nb <<
					" : Syntax Error !" << std::endl;
				return (false);
			}
		}
		else if (tok.type == Float || tok.type == Double)
		{
			if (!std::regex_match(line, fp_check))
			{
				this->_has_error = true;
				std::cout << "Error on line " << this->_line_nb <<
					" : Syntax Error !" << std::endl;
				return (false);
			}
		}
		begin_pos = line.find("(");
		end_pos = line.find(")");
		tok.value = line.substr(begin_pos + 1, end_pos - 1 - begin_pos);
	}
	return (true);
}

Parser::ParsingError::ParsingError(void)
{
		this->_msg = "Parse error : One or more errors have been detected. Aborting execution !";
}

Parser::ParsingError::~ParsingError(void) throw()
{
}
