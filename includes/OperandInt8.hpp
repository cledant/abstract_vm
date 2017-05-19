/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandInt8.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:17:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/17 19:21:30 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDINT8_HPP
# define OPERANDINT8_HPP

# include <limits>
# include "IOperand.hpp"
# include "GeneralException.hpp"
# include "OperandFactory.hpp"

class OperandInt8 : public IOperand
{
	public :

		OperandInt8(void);
		virtual ~OperandInt8(void);
		OperandInt8(OperandInt8 const &src);
		OperandInt8							&operator=(OperandInt8 const &rhs);

		OperandInt8(char const value);

		virtual int							getPrecision(void) const;
		virtual eOperandType				getType(void) const;
		char								getValue(void) const;

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
		char								_value;
		std::string							_str_value;
		int									_precision;
};

#endif
