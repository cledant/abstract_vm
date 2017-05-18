/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 12:35:13 by cledant           #+#    #+#             */
/*   Updated: 2017/05/16 18:25:12 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Env.hpp"

static int		from_stdin(void)
{
	std::unique_ptr<Env>	env;

	try
	{
		env.reset(new Env());
		env->parse();
		env->execute_program();
	}
	catch (std::exception	&e)
	{
		std::cout << e.what() << std::endl;
		return (0);
	}
	return (0);
}

static int		from_file(int argc, char **argv)
{
	int						c;
	std::unique_ptr<Env>	env;

	for (c = 1;	c != argc; ++c)
	{
		try
		{
			env.reset(new Env(argv[c]));
			env->parse();
			env->execute_program();
		}
		catch (std::exception	&e)
		{
			std::cout << e.what() << std::endl;
			return (0);
		}
	}
	return (0);
}

int				main(int argc, char **argv)
{
	if (argc == 1)
		return (from_stdin());
	return (from_file(argc, argv));
}
