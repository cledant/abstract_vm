/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 20:46:11 by cledant           #+#    #+#             */
/*   Updated: 2017/05/16 16:21:37 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token(void) : inst(I_PUSH), type(Int8)
{
	this->value = "0";
}

#include <iostream>

Token::Token(eInstruction inst_type, eOperandType op_type, const char *init_val) : inst(inst_type), type(op_type)
{
	this->value.assign(init_val);
}

Token::~Token(void)
{
}
