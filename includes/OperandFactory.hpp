/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:46:57 by cledant           #+#    #+#             */
/*   Updated: 2017/05/20 13:28:21 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include <limits>
# include "AFactory.hpp"
# include "OperandInt8.hpp"
# include "OperandInt16.hpp"
# include "OperandInt32.hpp"
# include "OperandFloat.hpp"
# include "OperandDouble.hpp"

class OperandFactory : public AFactory
{
	public	:

		OperandFactory(void);
		virtual ~OperandFactory(void);

		class	OverflowException : public GeneralException
		{
			public :

				explicit OverflowException(void);
				virtual ~OverflowException(void) throw();
		};

		class	UnderflowException : public GeneralException
		{
			public :

				explicit UnderflowException(void);
				virtual ~UnderflowException(void) throw();
		};

		class	InvalidConversionException : public GeneralException
		{
			public :

				explicit InvalidConversionException(void);
				virtual ~InvalidConversionException(void) throw();
		};	

	private :

		virtual IOperand const		*createInt8(std::string const &value) const;
		virtual IOperand const		*createInt16(std::string const &value) const;
		virtual IOperand const		*createInt32(std::string const &value) const;
		virtual IOperand const		*createFloat(std::string const &value) const;
		virtual IOperand const		*createDouble(std::string const &value) const;
};

#endif
