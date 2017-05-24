/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 10:40:39 by cledant           #+#    #+#             */
/*   Updated: 2017/05/24 11:31:41 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <fstream>
# include <iostream>
# include <vector>
# include <regex>
# include "CommandQueue.hpp"

class Parser
{
	public :

		Parser(void);
		Parser(Parser const &src);
		virtual ~Parser(void);
		Parser							&operator=(Parser const &rhs);

		bool							getHasError(void) const;
		bool							getHasExit(void) const;
		bool							getHasStdinExit(void) const;
		CommandQueue					*getQueue(void) const;
		size_t							getCurrentLine(void) const;

		void							parse(std::istream &ifs, eOrigin from);

		class ParsingError : public GeneralException
		{
			public :

				explicit ParsingError(void);
				virtual ~ParsingError(void) throw();
		};

	private :

		bool							remove_comment(std::string	&line) const;
		void							parse_line(std::string &line, 
											bool had_comment);
		bool							check_push(std::string &line,
											bool has_comment);
		bool							check_pop(std::string &line,
											bool has_comment);
		bool							check_dump(std::string &line,
											bool has_comment);
		bool							check_assert(std::string &line,
											bool has_comment);
		bool							check_add(std::string &line,
											bool has_comment);
		bool							check_sub(std::string &line,
											bool has_comment);
		bool							check_mul(std::string &line,
											bool has_comment);
		bool							check_div(std::string &line,
											bool has_comment);
		bool							check_mod(std::string &line,
											bool has_comment);
		bool							check_print(std::string &line,
											bool has_comment);
		bool							check_exit(std::string &line,
											bool has_comment);
		bool							check_empty(std::string &line,
											bool has_comment);
		bool							check_stdin_end(std::string &line) const;
		bool							create_token(eInstruction inst,
											std::string &line);
		bool							token_creation_parse(Token &tok,
											eInstruction inst, std::string &line);

		CommandQueue					*_cqueue;
		bool							_has_error;
		bool							_has_exit;
		bool							_has_stdin_exit;
		size_t							_line_nb;
};

#endif
