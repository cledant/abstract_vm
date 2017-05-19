/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandDouble.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:17:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/17 20:37:12 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDDOUBLE_HPP
# define OPERANDDOUBLE_HPP

# include <limits>
# include <cfenv>
# include <cmath>
# include <sstream>
# include <iomanip>
# include "IOperand.hpp"
# include "OperandFactory.hpp"

class OperandDouble : public IOperand
{
	public :

		OperandDouble(void);
		virtual ~OperandDouble(void);
		OperandDouble(OperandDouble const &src);
		OperandDouble						&operator=(OperandDouble const &rhs);

		OperandDouble(double const value, std::string const &str);

		virtual int							getPrecision(void) const;
		virtual eOperandType				getType(void) const;
		double								getValue(void) const;

		virtual IOperand const				*operator+(IOperand const &rhs) const;
		virtual IOperand const				*operator-(IOperand const &rhs) const;
		virtual IOperand const				*operator*(IOperand const &rhs) const;
		virtual IOperand const				*operator/(IOperand const &rhs) const;
		virtual IOperand const				*operator%(IOperand const &rhs) const;

		virtual std::string const			&toString(void) const;

		class	OverflowException : public std::overflow_error
		{
			public :

				explicit OverflowException(void);
				virtual ~OverflowException(void) throw();
		};

		class	UnderflowException : public std::underflow_error
		{
			public :

				explicit UnderflowException(void);
				virtual ~UnderflowException(void) throw();
		};

		class	DivideByZeroException : public std::invalid_argument
		{
			public :

				explicit DivideByZeroException(void);
				virtual ~DivideByZeroException(void) throw();
		};

	private :

		int									parsePrecision(std::string const
												&value) const;
		std::string							convertToString(double value,
												int precision) const;

		AFactory							*_factory;
		double								_value;
		std::string							_str_value;
		int									_precision;
};

#endif
