/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:46:57 by cledant           #+#    #+#             */
/*   Updated: 2017/05/05 12:57:25 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include <limits>
# include "AFactory.hpp"
# include "OperandInt16.hpp"
# include "OperandFloat.hpp"

class OperandFactory : public AFactory
{
	public	:

		OperandFactory(void);
		virtual ~OperandFactory(void);

		class	OverflowException : public std::exception
		{
			public :

				explicit OverflowException(void);
				virtual ~OverflowException(void) throw();
				OverflowException(OverflowException const &src);
				OverflowException &operator=(OverflowException const &rhs);
				virtual const char		*what(void) const throw();

			protected :

				std::string		_msg;
		};

		class	UnderflowException : public std::exception
		{
			public :

				explicit UnderflowException(void);
				virtual ~UnderflowException(void) throw();
				UnderflowException(UnderflowException const &src);
				UnderflowException &operator=(UnderflowException const &rhs);
				virtual const char		*what(void) const throw();

			protected :

				std::string		_msg;
		};

	private :

//		virtual IOperand const		*createInt8(std::string const &value) const;
		virtual IOperand const		*createInt16(std::string const &value) const;
//		virtual IOperand const		*createInt32(std::string const &value) const;
		virtual IOperand const		*createFloat(std::string const &value) const;
//		virtual IOperand const		*createDouble(std::string const &value) const;
};

#endif
