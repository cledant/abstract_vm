/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_vm_defines.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:55:37 by cledant           #+#    #+#             */
/*   Updated: 2017/05/11 12:50:24 by cledant          ###   ########.fr       */
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
	PUSH,
	POP,
	DUMP,
	ASSERT,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	PRINT,
	EXIT,
};

enum		eOrigin
{
	KEYBOARD,
	FILES,
};

#endif
