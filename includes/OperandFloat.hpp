/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFloat.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:17:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/26 11:37:55 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFLOAT_HPP
# define OPERANDFLOAT_HPP

# include <limits>
# include <cfenv>
# include <cmath>
# include <sstream>
# include <iomanip>
# include "GeneralException.hpp"
# include "IOperand.hpp"
# include "OperandFactory.hpp"

class OperandFloat : public IOperand
{
	public :

		OperandFloat(void);
		virtual ~OperandFloat(void);
		OperandFloat(OperandFloat const &src);
		OperandFloat						&operator=(OperandFloat const &rhs);

		OperandFloat(float const value, std::string const &str);

		virtual int							getPrecision(void) const;
		virtual eOperandType				getType(void) const;
		float								getValue(void) const;
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
		std::string							convertToString(float value,
												size_t precision) const;

		AFactory							*_factory;
		float								_value;
		std::string							_str_value;
		size_t								_zeroprecision;
};

#endif
