/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_vm_defines.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:55:37 by cledant           #+#    #+#             */
/*   Updated: 2017/05/16 14:04:18 by cledant          ###   ########.fr       */
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
	I_PUSH,
	I_POP,
	I_DUMP,
	I_ASSERT,
	I_ADD,
	I_SUB,
	I_MUL,
	I_DIV,
	I_MOD,
	I_PRINT,
	I_EXIT,
};

enum		eOrigin
{
	KEYBOARD,
	FILES,
};

#endif
