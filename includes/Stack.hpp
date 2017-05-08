/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 12:38:57 by cledant           #+#    #+#             */
/*   Updated: 2017/05/08 17:21:03 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "AStack.hpp"

class Stack : public AStack
{
	public :

		Stack(void);
		virtual ~Stack(void);

		virtual void				push(eOperandType type,
										std::string const &value);
/*		void						pop(void);
		void						dump(void);
		void						assert(eOperandType type,
										std::string const &value);
		void						dump(void);
		void						assert(void);
		void						add(void);
		void						sub(void);
		void						mul(void);
		void						div(void);
		void						mod(void);
		void						print(void);*/
};

#endif
