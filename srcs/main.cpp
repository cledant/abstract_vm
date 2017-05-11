/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 12:35:13 by cledant           #+#    #+#             */
/*   Updated: 2017/05/11 12:59:57 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		main(int argc, char **argv)
{
	std::unique_ptr<Env>	env;
	size_t					c;

	if (argc == 1)
	{
		env.reset(new Env(KEYBOARD));
		try
		{
			(*env)->parser->parse_from_stdin();
			(*env)->execute_program();
		}
		catch (std::exception	&e)
		{
			std::cout << e.what() << std::endl;
			env.release();
			return (0);
		}
	}
	else
	{
		for (c = 0,	c == argc, ++c)
		{
			env.reset(new Env(FILES, argv[c]));
			try
			{
				(*env)->parser->parse_from_file();
				(*env)->execute_program();
			}
			catch (std::exception	&e)
			{
				std::cout << e.what() << std::endl;
				env.release();
				return (0);
			}
		}
	}
	return (0);
}
