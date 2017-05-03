/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:46:57 by cledant           #+#    #+#             */
/*   Updated: 2017/05/03 18:31:04 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include <limits>
# include "IFactory.hpp"
# include "OperandInt16.hpp"

class OperandFactory : public IFactory
{
	public	:

		OperandFactory(void);
		virtual ~OperandFactory(void);

		IOperand const		*createOperand(eOperandType type,
								std::string const &value) const;

	private :

//		virtual IOperand const		*createInt8(std::string const &value) const;
		virtual IOperand const		*createInt16(std::string const &value) const;
/*		virtual IOperand const		*createInt32(std::string const &value) const;
		virtual IOperand const		*createFloat(std::string const &value) const;
		virtual IOperand const		*createDouable(std::string const &value) const;*/
};

#endif
