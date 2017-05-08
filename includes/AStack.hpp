/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 12:38:57 by cledant           #+#    #+#             */
/*   Updated: 2017/05/08 18:03:49 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTACK_HPP
# define ASTACK_HPP

# include <vector>
# include <string>
# include "OperandFactory.hpp"

class AStack
{
	public :

		AStack(void);
		virtual ~AStack(void);
		AStack(AStack const &src);
		virtual AStack							&operator=(AStack const &rhs);

		std::vector<IOperand const *> const		&getStack(void) const;

		virtual void					push(eOperandType type,
											std::string const &value) = 0;
//		void							pop(void) = 0;
		virtual void					dump(void) = 0;
/*		void							assert(eOperandType type,
											std::string const &value) = 0;
		void							dump(void) = 0;
		void							assert(void) = 0;
		void							add(void) = 0;
		void							sub(void) = 0;
		void							mul(void) = 0;
		void							div(void) = 0;
		void							mod(void) = 0;
		void							print(void) = 0;*/

	protected :

		std::vector<IOperand const *>			_stack;
		AFactory								*_factory;
};

#endif
