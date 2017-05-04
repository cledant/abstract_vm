/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:43:07 by cledant           #+#    #+#             */
/*   Updated: 2017/05/04 14:11:59 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <string>
# include "abstract_vm_defines.hpp"

class IOperand
{
	public :

		virtual int					getPrecision(void) const = 0;
		virtual eOperandType		getType(void) const = 0;

		virtual IOperand const		*operator+(IOperand const &rhs) const = 0;
/*		virtual IOperand const		*operator-(IOperand const &rhs) const = 0;
		virtual IOperand const		*operator*(IOperand const &rhs) const = 0;
		virtual IOperand const		*operator/(IOperand const &rhs) const = 0;
		virtual IOperand const		*operator%(IOperand const &rhs) const = 0;*/

		virtual std::string const	&toString(void) const = 0;

		virtual ~IOperand(void) {}
};

#endif
