/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AFactory.cpp       	                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:23:40 by cledant           #+#    #+#             */
/*   Updated: 2017/05/05 12:35:17 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AFactory.hpp"

AFactory::AFactory(void)
{
}

AFactory::~AFactory(void)
{
}

IOperand const		*AFactory::createOperand(eOperandType type,
						std::string const &value) const
{
	const IOperand *op = nullptr;

	switch (type)
	{
		case Int8 :
			op = this->createInt16(value);
			break ;
		case Int16 :
			op = this->createInt16(value);
			break ;
		case Int32 :
			op = this->createInt16(value);
			break ;
		case Float :
			op = this->createFloat(value);
			break ;
		case Double :
			op = this->createInt16(value);
			break ;
	}
	return (op);
}
