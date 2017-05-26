/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandDouble.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:55:23 by cledant           #+#    #+#             */
/*   Updated: 2017/05/26 11:39:15 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandDouble.hpp"

OperandDouble::OperandDouble(void) : _value(0.0), _str_value("0.00000"), _zeroprecision(5)
{
	this->_factory = new OperandFactory();
}

OperandDouble::~OperandDouble(void)
{
	delete this->_factory;
}

OperandDouble::OperandDouble(OperandDouble const &src) : _value(src.getValue()), _str_value(src.toString()), _zeroprecision(src.getZeroPrecision())
{
	this->_factory = new OperandFactory();
}

OperandDouble			&OperandDouble::operator=(OperandDouble const &rhs)
{
	this->_value = rhs.getValue();
	this->_str_value = rhs.toString().c_str();
	this->_zeroprecision = rhs.getZeroPrecision();
	return (*this);
}

OperandDouble::OperandDouble(double const value, std::string const &str) : _value(value)
{
	this->_factory = new OperandFactory();
	if ((this->_zeroprecision = this->parsePrecision(str)) >= 5)
		this->_str_value = str;
	else
	{
		this->_zeroprecision = 5;
		this->_str_value = this->convertToString(this->_value, this->_zeroprecision);
	}
}

int						OperandDouble::getPrecision(void) const
{
	return (static_cast<int>(this->getType()));
}

eOperandType			OperandDouble::getType(void) const
{
	return (Double);
}

double					OperandDouble::getValue(void) const
{
	return (this->_value);
}

size_t					OperandDouble::getZeroPrecision(void) const
{
	return (this->_zeroprecision);
}

IOperand const			*OperandDouble::operator+(IOperand const &rhs) const
{
	double				result;
	int					fe;
	const IOperand		*op_result;
	size_t				precision;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value + dynamic_cast<const OperandDouble &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandDouble::OverflowException();
	precision = (dynamic_cast<OperandDouble const &>(rhs).getZeroPrecision() >
		this->_zeroprecision) ?
		dynamic_cast<OperandDouble const &>(rhs).getZeroPrecision() :
		this->_zeroprecision;
	op_result = this->_factory->createOperand(Double,
		dynamic_cast<OperandDouble const *>(this)->convertToString(result,
		precision));
	return (op_result);
}

IOperand const			*OperandDouble::operator-(IOperand const &rhs) const
{
	double				result;
	int					fe;
	const IOperand		*op_result;
	size_t				precision;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value - dynamic_cast<const OperandDouble &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandDouble::OverflowException();
	precision = (dynamic_cast<OperandDouble const &>(rhs).getZeroPrecision() >
		this->_zeroprecision) ?
		dynamic_cast<OperandDouble const &>(rhs).getZeroPrecision() :
		this->_zeroprecision;
	op_result = this->_factory->createOperand(Double,
		dynamic_cast<OperandDouble const *>(this)->convertToString(result,
		precision));
	return (op_result);
}

IOperand const			*OperandDouble::operator*(IOperand const &rhs) const
{
	double				result;
	int					fe;
	const IOperand		*op_result;
	size_t				precision;

	if (dynamic_cast<const OperandDouble &>(rhs).getValue() == 0.0 ||
			this->getValue() == 0.0)
	{
		op_result = this->_factory->createOperand(Double, "0");
		return (op_result);
	}
	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value * dynamic_cast<const OperandDouble &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandDouble::OverflowException();
	else if (fe & FE_UNDERFLOW)
		throw OperandDouble::UnderflowException();
	precision = (dynamic_cast<OperandDouble const &>(rhs).getZeroPrecision() >
		this->_zeroprecision) ?
		dynamic_cast<OperandDouble const &>(rhs).getZeroPrecision() :
		this->_zeroprecision;
	op_result = this->_factory->createOperand(Double,
		dynamic_cast<OperandDouble const *>(this)->convertToString(result,
		precision));
	return (op_result);
}

IOperand const			*OperandDouble::operator/(IOperand const &rhs) const
{
	double				result;
	int					fe;
	const IOperand		*op_result;
	size_t				precision;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value / dynamic_cast<const OperandDouble &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandDouble::OverflowException();
	else if (fe & FE_UNDERFLOW)
		throw OperandDouble::UnderflowException();
	else if (fe & FE_DIVBYZERO)
		throw OperandDouble::DivideByZeroException();
	else if (fe & FE_INVALID)
		throw OperandDouble::DivideByZeroException();
	precision = (dynamic_cast<OperandDouble const &>(rhs).getZeroPrecision() >
		this->_zeroprecision) ?
		dynamic_cast<OperandDouble const &>(rhs).getZeroPrecision() :
		this->_zeroprecision;
	op_result = this->_factory->createOperand(Double,
		dynamic_cast<OperandDouble const *>(this)->convertToString(result,
		precision));
	return (op_result);
}

IOperand const			*OperandDouble::operator%(IOperand const &rhs) const
{
	double				result;
	int					fe;
	const IOperand		*op_result;
	size_t				precision;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = std::fmod(this->_value, dynamic_cast<const OperandDouble &>(rhs).getValue());
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandDouble::OverflowException();
	else if (fe & FE_UNDERFLOW)
		throw OperandDouble::UnderflowException();
	else if (fe & FE_DIVBYZERO)
		throw OperandDouble::DivideByZeroException();
	else if (fe & FE_INVALID)
		throw OperandDouble::DivideByZeroException();
	precision = (dynamic_cast<OperandDouble const &>(rhs).getZeroPrecision() >
		this->_zeroprecision) ?
		dynamic_cast<OperandDouble const &>(rhs).getZeroPrecision() :
		this->_zeroprecision;
	op_result = this->_factory->createOperand(Double,
		dynamic_cast<OperandDouble const *>(this)->convertToString(result,
		precision));
	return (op_result);
}

std::string const		&OperandDouble::toString(void) const
{
	return (this->_str_value);
}

size_t					OperandDouble::parsePrecision(std::string const &value) const
{
	size_t		pos_dot;
	size_t		pos_paren;

	pos_dot = value.find(".") + 1;
	pos_paren = value.size();
	return (pos_paren - pos_dot);
}

std::string				OperandDouble::convertToString(double value,
							size_t precision) const
{
	std::ostringstream		out;
	std::string				conv;

	out << std::fixed << std::setprecision(static_cast<int>(precision)) << value;
	conv = out.str();
	return (conv);
}

OperandDouble::OverflowException::OverflowException(void)
{
	this->_msg = "Runtime Exception : OperandDouble : This operation would cause an overflow !";
}

OperandDouble::OverflowException::~OverflowException(void) throw()
{
}

OperandDouble::UnderflowException::UnderflowException(void)
{
	this->_msg = "Runtime Exception : OperandDouble : This operation would cause an underflow !";
}

OperandDouble::UnderflowException::~UnderflowException(void) throw()
{
}

OperandDouble::DivideByZeroException::DivideByZeroException(void)
{
		this->_msg = "Runtime Exception : OperandDouble : This operation would cause a division by zero !";
}

OperandDouble::DivideByZeroException::~DivideByZeroException(void) throw()
{
}
