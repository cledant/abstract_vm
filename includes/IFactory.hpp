/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IFactory.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:17:55 by cledant           #+#    #+#             */
/*   Updated: 2017/05/03 18:28:58 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IFACTORY_HPP
# define IFACTORY_HPP

#include <string>
#include "IOperand.hpp"

class IFactory
{
	public :

		virtual ~IFactory(void) {}

	private :

//		virtual IOperand const		*createInt8(std::string const &value) const = 0;
		virtual IOperand const		*createInt16(std::string const &value) const = 0;
/*		virtual IOperand const		*createInt32(std::string const &value) const = 0;
		virtual IOperand const		*createFloat(std::string const &value) const = 0;
		virtual IOperand const		*createDouble(std::string const &value) const = 0;*/
};

#endif
