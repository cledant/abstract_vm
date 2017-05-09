/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:16:17 by cledant           #+#    #+#             */
/*   Updated: 2017/05/09 14:54:09 by cledant          ###   ########.fr       */
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
	stack->add();
	stack->dump();
	stack->push(Int16, "30000");
	stack->push(Int16, "30000");
	try
	{	
		stack->add();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	delete stack;
	while(1);
	return (0);
}
