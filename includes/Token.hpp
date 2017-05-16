/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 20:30:41 by cledant           #+#    #+#             */
/*   Updated: 2017/05/16 15:45:33 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include "abstract_vm_defines.hpp"

struct	Token
{
	Token(void);
	Token(eInstruction inst_type, eOperandType op_type, const char *init_val);
	~Token(void);

	eInstruction			inst;
	eOperandType			type;
	std::string				value;
};

# endif
