/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandInt16.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:17:28 by cledant           #+#    #+#             */
/*   Updated: 2017/05/03 12:51:29 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDINT16_HPP
# define OPERANDINT16_HPP

# include "IOperand.hpp"

class OperandInt16 : public IOperand
{
	public :
		OperandInt16(void);
		virtual ~OperandInt16(void);
		OperandInt16(OperandInt16 const &src);
		virtual OperandInt16				&operator=(OperandInt16 const &rhs);

		OperandInt16(std::string const &value) const;

		virtual int							getPrecision(void) const;
		virtual eOperand					getType(void) const;
		virtual short int					getValue(void) const;

		virtual OperandInt16 const			*operator+(OperandInt16 const &rhs) const;
		virtual OperandInt16 const			*operator-(OperandInt16 const &rhs) const;
		virtual OperandInt16 const			*operator*(OperandInt16 const &rhs) const;
		virtual OperandInt16 const			*operator/(OperandInt16 const &rhs) const;
		virtual OperandInt16 const			*operator%(OperandInt16 const &rhs) const;

		virtual std::string const			&toString(void) const;

	private :
		short int							_value;
};

#endif
