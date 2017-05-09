/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 12:38:57 by cledant           #+#    #+#             */
/*   Updated: 2017/05/09 18:24:45 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <memory>
# include <iostream>
# include "AStack.hpp"

class Stack : public AStack
{
	public :

		Stack(void);
		virtual ~Stack(void);

		virtual void				push(eOperandType type,
										std::string const &value);
		virtual void				pop(void);
		virtual void				dump(void);
		virtual void				assert(eOperandType type,
										std::string const &value);
		virtual void				add(void);
		virtual void				sub(void);
		virtual void				mul(void);
		virtual void				div(void);
		virtual void				mod(void);
		virtual void				print(void);

	private :

		void						do_operation(eOperator op);
		bool						assert_value(IOperand const *lhs,
										IOperand const *rhs);
};

#endif
