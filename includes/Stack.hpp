/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 12:38:57 by cledant           #+#    #+#             */
/*   Updated: 2017/05/24 17:11:46 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <memory>
# include <iostream>
# include <cctype>
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

	class EmptyStackException : public GeneralException
	{
		public :

			explicit EmptyStackException(void);
			virtual ~EmptyStackException(void) throw();
	};

	class NotEnoughElementException : public GeneralException
	{
		public :

			explicit NotEnoughElementException(void);
			virtual ~NotEnoughElementException(void) throw();
	};

	class AssertInvalidValueException : public GeneralException
	{
		public :

			explicit AssertInvalidValueException(void);
			virtual ~AssertInvalidValueException(void) throw();
	};

	class AssertDifferentTypeException : public GeneralException
	{
		public :

			explicit AssertDifferentTypeException(void);
			virtual ~AssertDifferentTypeException(void) throw();
	};

	class AssertDifferentValueException : public GeneralException
	{
		public :

			explicit AssertDifferentValueException(void);
			virtual ~AssertDifferentValueException(void) throw();
	};

	class NotInt8Exception : public GeneralException
	{
		public :

			explicit NotInt8Exception(void);
			virtual ~NotInt8Exception(void) throw();
	};

	private :

		eOperandType				resulting_operand_type(IOperand const *lhs,
										IOperand const *rhs);
		void						do_operation(eOperator op);
		bool						assert_value(IOperand const *lhs,
										IOperand const *rhs);
};

#endif
