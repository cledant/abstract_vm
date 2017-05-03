/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:04:53 by cledant           #+#    #+#             */
/*   Updated: 2017/05/03 18:43:53 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "OperandFactory.hpp"

int		main(void)
{
	OperandFactory			*factory = new OperandFactory();
	const IOperand			*a = nullptr;
	const IOperand			*b = nullptr;
	const IOperand 			*c = nullptr;

	a = factory->createOperand(Int16, "10");
	try
	{
		b = factory->createOperand(Int16, "30");
		c = *a + *b;
		std::cout << dynamic_cast<const OperandInt16 *>(c)->getValue() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
