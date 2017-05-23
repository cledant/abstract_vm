/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_vm_defines.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:55:37 by cledant           #+#    #+#             */
/*   Updated: 2017/05/23 11:21:44 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_VM_DEFINES_HPP
# define ABSTRACT_VM_DEFINES_HPP

enum		eOperandType
{
	Int8 = 0,
	Int16 = 1,
	Int32 = 2,
	Float = 3,
	Double = 4,
};

enum		eOperator
{
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
};

enum		eInstruction
{
	I_PUSH = 0,
	I_POP = 1,
	I_DUMP = 2,
	I_ASSERT = 3,
	I_ADD = 4,
	I_SUB = 5,
	I_MUL = 6,
	I_DIV = 7,
	I_MOD = 8,
	I_PRINT = 9,
	I_EXIT = 10,
	I_VALID_EMPTY = 11,
};

enum		eOrigin
{
	KEYBOARD,
	FILES,
};

#endif
