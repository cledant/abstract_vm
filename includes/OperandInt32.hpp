/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandInt32.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:17:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/17 19:21:20 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDINT32_HPP
# define OPERANDINT32_HPP

# include <limits>
# include "IOperand.hpp"
# include "GeneralException.hpp"
# include "OperandFactory.hpp"

class OperandInt32 : public IOperand
{
	public :

		OperandInt32(void);
		virtual ~OperandInt32(void);
		OperandInt32(OperandInt32 const &src);
		OperandInt32						&operator=(OperandInt32 const &rhs);

		OperandInt32(int const value);

		virtual int							getPrecision(void) const;
		virtual eOperandType				getType(void) const;
		int									getValue(void) const;

		virtual IOperand const				*operator+(IOperand const &rhs) const;
		virtual IOperand const				*operator-(IOperand const &rhs) const;
		virtual IOperand const				*operator*(IOperand const &rhs) const;
		virtual IOperand const				*operator/(IOperand const &rhs) const;
		virtual IOperand const				*operator%(IOperand const &rhs) const;

		virtual std::string const			&toString(void) const;

		class	OverflowException : public GeneralException
		{
			public :

				explicit OverflowException(void);
				virtual ~OverflowException(void) throw();
		};

		class	UnderflowException : public GeneralException
		{
			public :

				explicit UnderflowException(void);
				virtual ~UnderflowException(void) throw();
		};

		class	DivideByZeroException : public GeneralException
		{
			public :

				explicit DivideByZeroException(void);
				virtual ~DivideByZeroException(void) throw();
		};

	private :

		AFactory							*_factory;
		int									_value;
		std::string							_str_value;
		int									_precision;
};

#endif
