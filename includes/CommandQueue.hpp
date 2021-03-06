/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandQueue.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 10:48:07 by cledant           #+#    #+#             */
/*   Updated: 2017/05/12 18:25:55 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDQUEUE_HPP
# define COMMANDQUEUE_HPP

# include <deque>
# include <memory>
# include "GeneralException.hpp"
# include "Token.hpp"

class CommandQueue
{
	public :

		CommandQueue(void);
		virtual ~CommandQueue(void);
		CommandQueue(CommandQueue const &src);
		CommandQueue							&operator=(CommandQueue const &rhs);

		std::deque<Token const *> const			&getStack(void) const;
		void									push(Token const &tok);
		void									pop(void);
		Token const								*getFront(void);
		bool									isEmpty(void);

		class EmptyQueueException : public GeneralException
		{
			public :

				explicit EmptyQueueException(void);
				virtual ~EmptyQueueException(void) throw();
		};

	private :

		std::deque<Token const *>				_stack;
};

#endif
