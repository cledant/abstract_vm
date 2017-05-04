/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:04:53 by cledant           #+#    #+#             */
/*   Updated: 2017/05/04 16:08:00 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "OperandFactory.hpp"

int		main(void)
{
	AFactory				*factory = new OperandFactory();
	const IOperand			*a1 = nullptr;
	const IOperand			*a2 = nullptr;
	const IOperand 			*a3 = nullptr;

	std::cout << "Test on OperandInt16" << std::endl << std::endl;
	//Addition test

	//Simple test
	a1 = factory->createOperand(Int16, "10");
	a2 = factory->createOperand(Int16, "30");
	a3 = *a1 + *a2;
	std::cout << "a1 : " << dynamic_cast<const OperandInt16 *>(a1)->toString() << std::endl;
	std::cout << "a2 : " << dynamic_cast<const OperandInt16 *>(a2)->toString() << std::endl;
	std::cout << "addition test 1: " << dynamic_cast<const OperandInt16 *>(a3)->toString() << std::endl << "===========" << std::endl;
	delete a1;
	delete a2;
	delete a3;
	//Negative number test
	a1 = factory->createOperand(Int16, "-10");
	a2 = factory->createOperand(Int16, "30");
	a3 = *a1 + *a2;
	std::cout << "a1 : " << dynamic_cast<const OperandInt16 *>(a1)->toString() << std::endl;
	std::cout << "a2 : " << dynamic_cast<const OperandInt16 *>(a2)->toString() << std::endl;
	std::cout << "addition test 2: " << dynamic_cast<const OperandInt16 *>(a3)->toString() << std::endl << "===========" << std::endl;
	delete a1;
	delete a2;
	delete a3;
	//Exception raising test1
	try
	{
		a1 = factory->createOperand(Int16, "10000");
		a2 = factory->createOperand(Int16, "30000");
		a3 = *a1 + *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandInt16 *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandInt16 *>(a2)->toString() << std::endl;
		std::cout << "addition test 2: " << dynamic_cast<const OperandInt16 *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}
	//Exception raising test2
	try
	{
		a1 = factory->createOperand(Int16, "-10000");
		a2 = factory->createOperand(Int16, "-30000");
		a3 = *a1 + *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandInt16 *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandInt16 *>(a2)->toString() << std::endl;
		std::cout << "addition test 2: " << dynamic_cast<const OperandInt16 *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}
	//Subtraction test

	//Assignation test
	OperandInt16			*as1 = new OperandInt16(9000);
	OperandInt16 			*as2 = new OperandInt16(1337);
	std::cout << "Assination operator test" << std::endl;
	std::cout << as1->toString() << std::endl;
	*as2 = *as1;
	delete as1;
	std::cout << as2->toString() << std::endl;
	std::cout << "===========" << std::endl;
	delete as2;
	delete factory;
	return (0);
}
