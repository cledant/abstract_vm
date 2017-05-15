/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 12:35:13 by cledant           #+#    #+#             */
/*   Updated: 2017/05/15 13:15:30 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Env.hpp"

int		main(int argc, char **argv)
{
	std::unique_ptr<Env>	env;
	int						c;

	if (argc == 1)
	{
/*		try
		{
			env.reset(new Env());
			(*env)->parse_from_stdin();
			(*env)->execute_program();
		}
		catch (std::exception	&e)
		{
			std::cout << e.what() << std::endl;
			return (0);
		}*/
		std::cout << "Not now" << std::endl;
	}
	else
	{
		for (c = 1;	c != argc; ++c)
		{
			try
			{
				env.reset(new Env(argv[c]));
				env->parse_from_file();
				env->execute_program();
			}
			catch (std::exception	&e)
			{
				std::cout << e.what() << std::endl;
				return (0);
			}
		}
	}
	return (0);
}
