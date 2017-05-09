/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:16:17 by cledant           #+#    #+#             */
/*   Updated: 2017/05/09 18:26:36 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Stack.hpp"

int 		main(void)
{
	AStack	*stack =	new Stack();

	stack->push(Int8, "42");
	stack->push(Double, "42.42");
	stack->push(Int32, "424242");
	stack->dump();
	std::cout << "===========" << std::endl;
	stack->add();
	stack->dump();
	std::cout << "===========" << std::endl;
	stack->push(Int16, "30000");
	stack->dump();
	std::cout << "===========" << std::endl;
	stack->sub();
	stack->dump();
	std::cout << "===========" << std::endl;
	stack->pop();
	stack->dump();
	std::cout << "===========" << std::endl;
	stack->assert(Int8, "42");
	stack->dump();
	std::cout << "===========" << std::endl;
	stack->push(Double, "42.4200001");
	stack->dump();
	std::cout << "===========" << std::endl;
	try
	{
		stack->assert(Double, "42.42");
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	stack->dump();
	std::cout << "===========" << std::endl;
	stack->push(Int8, "-100");
	stack->dump();
	std::cout << "===========" << std::endl;
	stack->print();
	stack->dump();
	std::cout << "===========" << std::endl;
	delete stack;
	while(1);
	return (0);
}
