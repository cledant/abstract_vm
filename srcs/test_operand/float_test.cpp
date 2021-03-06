/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:04:53 by cledant           #+#    #+#             */
/*   Updated: 2017/05/05 20:51:41 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "OperandFactory.hpp"

void	addition_test(void)
{
	AFactory				*factory = new OperandFactory();
	const IOperand			*a1 = nullptr;
	const IOperand			*a2 = nullptr;
	const IOperand 			*a3 = nullptr;

	std::cout << "===Test on Addition===" << std::endl;
	//Addition test

	//Simple test
	a1 = factory->createOperand(Float, "10");
	a2 = factory->createOperand(Float, "30");
	a3 = *a1 + *a2;
	std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
	std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
	std::cout << "addition test 1: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
	delete a1;
	delete a2;
	delete a3;

	//Negative number test
	a1 = factory->createOperand(Float, "-10");
	a2 = factory->createOperand(Float, "30");
	a3 = *a1 + *a2;
	std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
	std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
	std::cout << "addition test 2: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
	delete a1;
	delete a2;
	delete a3;

	//Exception raising test1
	try
	{
		a1 = factory->createOperand(Float, "100000000000000000000000000000000000000");
		a2 = factory->createOperand(Float, "340000000000000000000000000000000000000");
		a3 = *a1 + *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "addition test 4: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test2
	try
	{
		a1 = factory->createOperand(Float, "-100000000000000000000000000000000000000");
		a2 = factory->createOperand(Float, "-340000000000000000000000000000000000000");
		a3 = *a1 + *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "addition test 4: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}
	std::cout << std::endl;
	delete factory;
}

void	substraction_test(void)
{
	AFactory				*factory = new OperandFactory();
	const IOperand			*a1 = nullptr;
	const IOperand			*a2 = nullptr;
	const IOperand 			*a3 = nullptr;

	std::cout << "===Test on Substraction===" << std::endl;
	//Subtraction test

	//Simple test
	a1 = factory->createOperand(Float, "10");
	a2 = factory->createOperand(Float, "30");
	a3 = *a1 - *a2;
	std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
	std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
	std::cout << "subtraction test 1: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
	delete a1;
	delete a2;
	delete a3;

	//Negative number test
	a1 = factory->createOperand(Float, "-10");
	a2 = factory->createOperand(Float, "30");
	a3 = *a1 - *a2;
	std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
	std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
	std::cout << "subtraction test 2: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
	delete a1;
	delete a2;
	delete a3;

	//Exception raising test1
	try
	{
		a1 = factory->createOperand(Float, "-100000000000000000000000000000000000000");
		a2 = factory->createOperand(Float, "340000000000000000000000000000000000000");
		a3 = *a1 - *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "substraction test 3: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test2
	try
	{
		a1 = factory->createOperand(Float, "-340000000000000000000000000000000000000");
		a2 = factory->createOperand(Float, "100000000000000000000000000000000000000");
		a3 = *a1 - *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "substraction test 4: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}
	std::cout << std::endl;
	delete factory;
}

void	assignation_test(void)
{
	AFactory				*factory = new OperandFactory();
	OperandFloat			*as1 = new OperandFloat(9000);
	OperandFloat 			*as2 = new OperandFloat(1337);

	//Assignation test
	std::cout << "===Test on Assination Operator===" << std::endl;
	std::cout << as1->toString() << std::endl;
	*as2 = *as1;
	delete as1;
	std::cout << as2->toString() << std::endl;
	std::cout << "===========" << std::endl;
	delete as2;
	delete factory;
	std::cout << std::endl;
}

void	out_of_bound_creation_test(void)
{
	AFactory				*factory = new OperandFactory();
	const IOperand 			*as1 = nullptr;

	//OOB test
	std::cout << "===Test on Out of Bound Creation===" << std::endl;
	try
	{
		as1 = factory->createOperand(Float, "10000000000000000000000000000000000000000000000000000000000000000000000");
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}
	try
	{
		as1 = factory->createOperand(Float, "-4000000000000000000000000000000000000000000000000000000000000000000000000");
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}
	delete factory;
	std::cout << std::endl;
}

void	multiplication_test(void)
{
	AFactory				*factory = new OperandFactory();
	const IOperand			*a1 = nullptr;
	const IOperand			*a2 = nullptr;
	const IOperand 			*a3 = nullptr;

	std::cout << "===Test on Multiplication===" << std::endl;
	//Multiplication test

	//Simple test
	a1 = factory->createOperand(Float, "10");
	a2 = factory->createOperand(Float, "30");
	a3 = *a1 * *a2;
	std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
	std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
	std::cout << "multiplication test 1: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
	delete a1;
	delete a2;
	delete a3;

	//Negative number test
	a1 = factory->createOperand(Float, "-10");
	a2 = factory->createOperand(Float, "30");
	a3 = *a1 * *a2;
	std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
	std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
	std::cout << "multiplication test 2: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
	delete a1;
	delete a2;
	delete a3;

	//Exception raising test1
	try
	{
		a1 = factory->createOperand(Float, "100000000000000000000000");
		a2 = factory->createOperand(Float, "9000000000000000000000000000");
		a3 = *a1 * *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "multiplication test 3: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test2
	try
	{
		a1 = factory->createOperand(Float, "-100000000000000000000000");
		a2 = factory->createOperand(Float, "9000000000000000000000000000");
		a3 = *a1 * *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "multiplication test 4: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test3
	try
	{
		a1 = factory->createOperand(Float, "0.000000000000000000000001");
		a2 = factory->createOperand(Float, "0.0000000000000000000000000009");
		a3 = *a1 * *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "multiplication test 5: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	std::cout << std::endl;
	delete factory;
}

void	division_test(void)
{
	AFactory				*factory = new OperandFactory();
	const IOperand			*a1 = nullptr;
	const IOperand			*a2 = nullptr;
	const IOperand 			*a3 = nullptr;

	std::cout << "===Test on Division===" << std::endl;
	//Multiplication test

	//Simple test
	a1 = factory->createOperand(Float, "30");
	a2 = factory->createOperand(Float, "10");
	a3 = *a1 / *a2;
	std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
	std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
	std::cout << "division test 1: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
	delete a1;
	delete a2;
	delete a3;

	//Negative number test
	a1 = factory->createOperand(Float, "-10");
	a2 = factory->createOperand(Float, "30");
	a3 = *a1 / *a2;
	std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
	std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
	std::cout << "division test 2: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
	delete a1;
	delete a2;
	delete a3;

	//Exception raising test1
	try
	{
		a1 = factory->createOperand(Float, "30000");
		a2 = factory->createOperand(Float, "2");
		a3 = *a1 / *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "division test 3: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test2
	try
	{
		a1 = factory->createOperand(Float, "30000");
		a2 = factory->createOperand(Float, "-2");
		a3 = *a1 / *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "division test 4: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test3
	try
	{
		a1 = factory->createOperand(Float, "0.00000000000000001");
		a2 = factory->createOperand(Float, "901000000000000000000000000000");
		a3 = *a1 / *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "division test 5: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test4
	try
	{
		a1 = factory->createOperand(Float, "100000000000000000");
		a2 = factory->createOperand(Float, "-0.0000000000000000000000000001");
		a3 = *a1 / *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "division test 6: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test5
	try
	{
		a1 = factory->createOperand(Float, "0");
		a2 = factory->createOperand(Float, "0");
		a3 = *a1 / *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "division test 7: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test6
	try
	{
		a1 = factory->createOperand(Float, "42");
		a2 = factory->createOperand(Float, "0");
		a3 = *a1 / *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "division test 8: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	std::cout << std::endl;
	delete factory;
}

void	modulo_test(void)
{
	AFactory				*factory = new OperandFactory();
	const IOperand			*a1 = nullptr;
	const IOperand			*a2 = nullptr;
	const IOperand 			*a3 = nullptr;

	std::cout << "===Test on Modulo===" << std::endl;
	//Multiplication test

	//Simple test
	a1 = factory->createOperand(Float, "30");
	a2 = factory->createOperand(Float, "10");
	a3 = *a1 % *a2;
	std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
	std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
	std::cout << "Modulo test 1: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
	delete a1;
	delete a2;
	delete a3;

	//Negative number test
	a1 = factory->createOperand(Float, "-10");
	a2 = factory->createOperand(Float, "30");
	a3 = *a1 % *a2;
	std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
	std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
	std::cout << "Modulo test 2: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
	delete a1;
	delete a2;
	delete a3;

	//Exception raising test1
	try
	{
		a1 = factory->createOperand(Float, "30000");
		a2 = factory->createOperand(Float, "2");
		a3 = *a1 % *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "Modulo test 3: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test2
	try
	{
		a1 = factory->createOperand(Float, "30000");
		a2 = factory->createOperand(Float, "-2");
		a3 = *a1 % *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "Modulo test 4: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test3
	try
	{
		a1 = factory->createOperand(Float, "84164646415324681523465123456");
		a2 = factory->createOperand(Float, "0.00000000000000000000000002");
		a3 = *a1 % *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "modulo test 5: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test4
	try
	{
		a1 = factory->createOperand(Float, "0.0000000000000000000000000001");
		a2 = factory->createOperand(Float, "0.000000000000000000000001");
		a3 = *a1 % *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "modulo test 6: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test5
	try
	{
		a1 = factory->createOperand(Float, "0");
		a2 = factory->createOperand(Float, "0");
		a3 = *a1 % *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "modulo test 7: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	//Exception raising test6
	try
	{
		a1 = factory->createOperand(Float, "42");
		a2 = factory->createOperand(Float, "0");
		a3 = *a1 % *a2;
		std::cout << "a1 : " << dynamic_cast<const OperandFloat *>(a1)->toString() << std::endl;
		std::cout << "a2 : " << dynamic_cast<const OperandFloat *>(a2)->toString() << std::endl;
		std::cout << "modulo test 8: " << dynamic_cast<const OperandFloat *>(a3)->toString() << std::endl << "===========" << std::endl;
		delete a1;
		delete a2;
		delete a3;
	}
	catch (std::exception &e)
	{
		delete a1;
		delete a2;
		std::cout << e.what() << std::endl << "===========" << std::endl;
	}

	std::cout << std::endl;
	delete factory;
}

int		main(void)
{
	std::cout << "Test on OperandFloat" << std::endl << std::endl;
	addition_test();
	substraction_test();
	assignation_test();
	out_of_bound_creation_test();
	multiplication_test();
	division_test();
	modulo_test();
	while(1);
	return (0);
}
