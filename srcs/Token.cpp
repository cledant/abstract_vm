/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 20:46:11 by cledant           #+#    #+#             */
/*   Updated: 2017/05/12 11:18:00 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token(eInstruction inst_type, eOperandType op_type, const char *init_val) : inst(inst_type), type(op_type)
{
	this->value = *init_val;
}

Token::~Token(void)
{
}
