/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandDouble.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:17:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/26 11:37:45 by cledant          ###   ########.fr       */
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
# include "GeneralException.hpp"
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
		size_t								getZeroPrecision(void) const;

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

		size_t								parsePrecision(std::string const
												&value) const;
		std::string							convertToString(double value,
												size_t precision) const;

		AFactory							*_factory;
		double								_value;
		std::string							_str_value;
		size_t								_zeroprecision;
};

#endif
