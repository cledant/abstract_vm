/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IFactory.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:17:55 by cledant           #+#    #+#             */
/*   Updated: 2017/05/06 13:38:44 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFACTORY_HPP
# define AFACTORY_HPP

#include <string>
#include "abstract_vm_defines.hpp"

class IOperand;

class AFactory
{
	public :

		AFactory(void);
		virtual ~AFactory(void);

		IOperand const		*createOperand(eOperandType type,
								std::string const &value) const;

	private :

		virtual IOperand const		*createInt8(std::string const &value) const = 0;
		virtual IOperand const		*createInt16(std::string const &value) const = 0;
		virtual IOperand const		*createInt32(std::string const &value) const = 0;
		virtual IOperand const		*createFloat(std::string const &value) const = 0;
		virtual IOperand const		*createDouble(std::string const &value) const = 0;
};

#endif
