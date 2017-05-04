/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:46:57 by cledant           #+#    #+#             */
/*   Updated: 2017/05/04 14:14:52 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include <limits>
# include "AFactory.hpp"
# include "OperandInt16.hpp"

class OperandFactory : public AFactory
{
	public	:

		OperandFactory(void);
		virtual ~OperandFactory(void);

	private :

//		virtual IOperand const		*createInt8(std::string const &value) const;
		virtual IOperand const		*createInt16(std::string const &value) const;
/*		virtual IOperand const		*createInt32(std::string const &value) const;
		virtual IOperand const		*createFloat(std::string const &value) const;
		virtual IOperand const		*createDouable(std::string const &value) const;*/
};

#endif
