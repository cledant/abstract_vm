/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:04:53 by cledant           #+#    #+#             */
/*   Updated: 2017/05/04 14:18:26 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "OperandFactory.hpp"

int		main(void)
{
	AFactory				*factory = new OperandFactory();
	const IOperand			*a = nullptr;
	const IOperand			*b = nullptr;
	const IOperand 			*c = nullptr;
	OperandInt16			*d = new OperandInt16(9000);
	OperandInt16 			*e = new OperandInt16(1337);

	a = factory->createOperand(Int16, "10");
	try
	{
		b = factory->createOperand(Int16, "30");
		c = *a + *b;
		std::cout << dynamic_cast<const OperandInt16 *>(c)->toString() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << d->toString() << std::endl;
	std::cout << e->toString() << std::endl;
	*e = *d;
	delete d;
	std::cout << dynamic_cast<OperandInt16 *>(e)->getValue() << std::endl;
	std::cout << e->toString() << std::endl;
	delete a;
	delete b;
	delete c;
	delete e;
	return (0);
}
