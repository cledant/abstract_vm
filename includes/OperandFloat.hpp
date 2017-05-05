/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFloat.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:17:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/05 18:51:21 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFLOAT_HPP
# define OPERANDFLOAT_HPP

# include <limits>
# include <cfenv>
# include <cmath>
# include "IOperand.hpp"
# include "OperandFactory.hpp"

class OperandFloat : public IOperand
{
	public :

		OperandFloat(void);
		virtual ~OperandFloat(void);
		OperandFloat(OperandFloat const &src);
		virtual OperandFloat				&operator=(OperandFloat const &rhs);

		OperandFloat(float const value);

		virtual int							getPrecision(void) const;
		virtual eOperandType				getType(void) const;
		float								getValue(void) const;

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
		float								_value;
		std::string							_str_value;
};

#endif
