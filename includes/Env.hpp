/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:07:25 by cledant           #+#    #+#             */
/*   Updated: 2017/05/11 22:02:42 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_HPP
# define ENV_HPP

# include <iostream>
# include <fstream>
# include <deque>
# include "Token.hpp"
# include "Stack.hpp"
# include "Parser.hpp"

class Env
{
	public	:

		Env(void);
		Env(Env const &src);
		virtual ~Env(void);
		virtual Env			&operator=(Env const &rhs);

		Env(char const *file);
		eOrigin								getOrigin(void) const;
		char const							*getFilename(void) const;
		std::ifstream const					&getIfs(void) const;
		AStack const						*getStack(void) const;
		std::deque<Token const *> const		&getQueue(void) const;
	//	void								parse_from_stdin(void);
		void								parse_from_file(void);
//		void								execute_program(void);

	private :

		std::ifstream					_ifs;
		AStack							*_stack;
		std::deque<Token const *>		_cqueue;
		Parser							*_parser;
		char const						*_filename;
		eOrigin							_orig;
};

#endif
