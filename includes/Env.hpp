/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:07:25 by cledant           #+#    #+#             */
/*   Updated: 2017/05/16 19:25:13 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_HPP
# define ENV_HPP

# include <fstream>
# include "Token.hpp"
# include "Stack.hpp"
# include "Parser.hpp"

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

		void							parse(void);
		void							execute_program(void);

		class InitFailException : public GeneralException
		{
			public :

				explicit InitFailException(void);
				virtual ~InitFailException(void) throw();
		};

		class OpenFailException : public GeneralException
		{
			public :

				explicit OpenFailException(void);
				virtual ~OpenFailException(void) throw();
		};

	private :

		std::ifstream					_ifs;
		AStack							*_stack;
		Parser							*_parser;
		char const						*_filename;
		eOrigin							_orig;
};

#endif
