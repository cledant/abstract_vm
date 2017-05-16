/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:07:25 by cledant           #+#    #+#             */
/*   Updated: 2017/05/16 15:48:00 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_HPP
# define ENV_HPP

# include <iostream>
# include <fstream>
# include <deque>
# include <regex>
# include "Token.hpp"
# include "Stack.hpp"
# include "Parser.hpp"
# include "CommandQueue.hpp"

class Env
{
	public	:

		Env(void);
		Env(Env const &src);
		virtual ~Env(void);
		Env								&operator=(Env const &rhs);

		Env(char const *file);
		eOrigin							getOrigin(void) const;
		char const						*getFilename(void) const;
		std::ifstream const				&getIfs(void) const;
		AStack const					*getStack(void) const;
		CommandQueue const				*getQueue(void) const;
		bool							getHasError(void) const;
		bool							getHasExit(void) const;
	//	void							parse_from_stdin(void);
		void							parse_from_file(void);
		void							execute_program(void);

	private :

		bool							remove_comment(std::string	&line) const;
		bool							check_push(std::string &line,
											bool has_comment) const;
		bool							check_dump(std::string &line,
											bool has_comment) const;
		bool							check_exit(std::string &line,
											bool has_comment) const;
		void							create_token(eInstruction inst,
											std::string &line);
		void							token_creation_parse(Token &tok,
											eInstruction inst, std::string &line);

		std::ifstream					_ifs;
		AStack							*_stack;
		CommandQueue					*_cqueue;
		Parser							*_parser;
		char const						*_filename;
		eOrigin							_orig;
		bool							_has_error;
		bool							_has_exit;
};

#endif
