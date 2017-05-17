/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandInt8.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:17:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/17 18:12:32 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDINT8_HPP
# define OPERANDINT8_HPP

# include <limits>
# include "IOperand.hpp"
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

		class	OverflowException : public std::exception
		{
			public :

				explicit OverflowException(void);
				virtual ~OverflowException(void) throw();
				OverflowException(OverflowException const &src);
				OverflowException &operator=(OverflowException const &rhs);
				virtual const char		*what(void) const throw();

			protected :

				std::string		_msg;
		};

		class	UnderflowException : public std::exception
		{
			public :

				explicit UnderflowException(void);
				virtual ~UnderflowException(void) throw();
				UnderflowException(UnderflowException const &src);
				UnderflowException &operator=(UnderflowException const &rhs);
				virtual const char		*what(void) const throw();

			protected :

				std::string		_msg;
		};

		class	DivideByZeroException : public std::exception
		{
			public :

				explicit DivideByZeroException(void);
				virtual ~DivideByZeroException(void) throw();
				DivideByZeroException(DivideByZeroException const &src);
				DivideByZeroException &operator=(DivideByZeroException const &rhs);
				virtual const char		*what(void) const throw();

			protected :

				std::string		_msg;
		};

	private :

		AFactory							*_factory;
		char								_value;
		std::string							_str_value;
		size_t								_precision;
};

#endif
