/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandInt16.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:17:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/04 16:32:53 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDINT16_HPP
# define OPERANDINT16_HPP

# include <limits>
# include "IOperand.hpp"
# include "OperandFactory.hpp"

class OperandInt16 : public IOperand
{
	public :

		OperandInt16(void);
		virtual ~OperandInt16(void);
		OperandInt16(OperandInt16 const &src);
		virtual OperandInt16				&operator=(OperandInt16 const &rhs);

		OperandInt16(short int const value);

		virtual int							getPrecision(void) const;
		virtual eOperandType				getType(void) const;
		short int							getValue(void) const;

		virtual IOperand const				*operator+(IOperand const &rhs) const;
		virtual IOperand const				*operator-(IOperand const &rhs) const;
		virtual IOperand const				*operator*(IOperand const &rhs) const;
/*		virtual IOperand const				*operator/(IOperand const &rhs) const;
		virtual IOperand const				*operator%(IOperand const &rhs) const;*/

		virtual std::string const			&toString(void) const;

	private :

		AFactory							*_factory;
		short int							_value;
		std::string							_str_value;
};

#endif
