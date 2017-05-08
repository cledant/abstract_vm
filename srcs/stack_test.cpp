/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:16:17 by cledant           #+#    #+#             */
/*   Updated: 2017/05/08 18:11:24 by cledant          ###   ########.fr       */
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
	delete stack;
	while(1);
	return (0);
}
