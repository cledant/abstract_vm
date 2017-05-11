/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandQueue.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 10:44:20 by cledant           #+#    #+#             */
/*   Updated: 2017/05/11 12:01:50 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDQUEUE_HPP
# define COMMANDQUEUUE_HPP

# include <string>

struct	Token
{
	enum eInstruction		inst;
	enum eOperator			type;
	std::string				value;
};

class 	CommandQueue
{
	public :
		CommandQueue(void);
		CommandQueue(CommandQueue const &src);
		virtual	~CommandQueue(void);
		virtual CommandQueue		&operator=(CommandQueue const &rhs);

		void	push(struct Token)

	private :

		std::queue<struct Token const>		_queue;
};

# endif
