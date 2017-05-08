/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 12:38:57 by cledant           #+#    #+#             */
/*   Updated: 2017/05/08 14:44:25 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "Stack.hpp"

class Stack : public AStack
{
	public :

		Stack(void);
		virtual ~Stack(void);

		void						push(eOperandType type,
										std::string const &value) const;
		void						pop(void);
		void						dump(void);
		void						assert(eOperandType type,
										std::string const &value) const;
		void						dump(void);
		void						assert(void);
		void						add(void);
		void						sub(void);
		void						mul(void);
		void						div(void);
		void						mod(void);
		void						print(void);
};

#endif
