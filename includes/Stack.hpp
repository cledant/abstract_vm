/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 12:38:57 by cledant           #+#    #+#             */
/*   Updated: 2017/05/09 13:06:30 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include "AStack.hpp"

class Stack : public AStack
{
	public :

		Stack(void);
		virtual ~Stack(void);

		virtual void				push(eOperandType type,
										std::string const &value);
//		void						pop(void);
		virtual void				dump(void);
/*		void						assert(eOperandType type,
										std::string const &value);*/
		virtual void				add(void);
/*		void						sub(void);
		void						mul(void);
		void						div(void);
		void						mod(void);
		void						print(void);*/

	private :
		void						do_operation(IOperand const *lhs,
										IOperand const *rhs, eOperandType type,
										eCast cast, eOperator op);
		void						do_add(IOperand const *lhs, IOperand const *rhs,
										eCast cast, eOperandType type);
};

#endif
