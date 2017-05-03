/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:04:53 by cledant           #+#    #+#             */
/*   Updated: 2017/05/03 14:52:17 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "OperandInt16.hpp"

int		main(void)
{
	IOperand	*a;
	IOperand	*b;

	a = new OperandInt16(10);
	b = new OperandInt16(20);	

	const IOperand *c = *a + *b;
	std::cout << dynamic_cast<const OperandInt16 *>(c)->getValue() << std::endl;
	return (0);
}
