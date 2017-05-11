/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 20:46:11 by cledant           #+#    #+#             */
/*   Updated: 2017/05/11 20:52:54 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token(eInstruction inst_type, eOperandType op_type, std::string &init_val) : inst(inst_type), type(op_type), value(init_val.c_str())
{
}

Token::~Token(void)
{
}
