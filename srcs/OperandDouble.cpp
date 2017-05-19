/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandDouble.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:55:23 by cledant           #+#    #+#             */
/*   Updated: 2017/05/17 20:37:26 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandDouble.hpp"

OperandDouble::OperandDouble(void) : _value(0.0), _str_value("0.0"), _precision(1)
{
	this->_factory = new OperandFactory();
}

OperandDouble::~OperandDouble(void)
{
	delete this->_factory;
}

OperandDouble::OperandDouble(OperandDouble const &src) : _value(src.getValue()), _str_value(src.toString()), _precision(src.getPrecision())
{
	this->_factory = new OperandFactory();
}

OperandDouble			&OperandDouble::operator=(OperandDouble const &rhs)
{
	this->_value = rhs.getValue();
	this->_str_value = rhs.toString().c_str();
	this->_precision = rhs.getPrecision();
	return (*this);
}

OperandDouble::OperandDouble(double const value, std::string const &str) : _value(value)
{
	this->_factory = new OperandFactory();
	this->_precision = this->parsePrecision(str);
	this->_str_value = str;
}

int						OperandDouble::getPrecision(void) const
{
	return (this->_precision);
}

eOperandType			OperandDouble::getType(void) const
{
	return (Double);
}

double					OperandDouble::getValue(void) const
{
	return (this->_value);
}

IOperand const			*OperandDouble::operator+(IOperand const &rhs) const
{
	double				result;
	int					fe;
	const IOperand		*op_result;
	int					precision;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value + dynamic_cast<const OperandDouble &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandDouble::OverflowException();
	precision = (rhs.getPrecision() > this->_precision) ? rhs.getPrecision() :
		this->_precision;
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
	int					precision;

	std::feclearexcept(FE_ALL_EXCEPT);
	result = this->_value - dynamic_cast<const OperandDouble &>(rhs).getValue();
	fe = fetestexcept(FE_ALL_EXCEPT);
	if (fe & FE_OVERFLOW)
		throw OperandDouble::OverflowException();
	precision = (rhs.getPrecision() > this->_precision) ? rhs.getPrecision() :
		this->_precision;
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
	int					precision;

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
	precision = (rhs.getPrecision() > this->_precision) ? rhs.getPrecision() :
		this->_precision;
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
	int					precision;

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
	precision = (rhs.getPrecision() > this->_precision) ? rhs.getPrecision() :
		this->_precision;
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
	int					precision;

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
	precision = (rhs.getPrecision() > this->_precision) ? rhs.getPrecision() :
		this->_precision;
	op_result = this->_factory->createOperand(Double,
		dynamic_cast<OperandDouble const *>(this)->convertToString(result,
		precision));
	return (op_result);
}

std::string const		&OperandDouble::toString(void) const
{
	return (this->_str_value);
}

int						OperandDouble::parsePrecision(std::string const &value) const
{
	size_t		pos_dot;
	size_t		pos_paren;

	pos_dot = value.find(".") + 1;
	pos_paren = value.size();
	return (static_cast<int>(pos_paren - pos_dot));
}

std::string				OperandDouble::convertToString(double value,
							int precision) const
{
	std::ostringstream		out;
	std::string				conv;

	out << std::fixed << std::setprecision(precision) << value;
	conv = out.str();
	return (conv);
}


OperandDouble::OverflowException::OverflowException(void) : std::overflow_error("OperandDouble : This operation would cause an overflow !")
{
}

OperandDouble::OverflowException::~OverflowException(void) throw()
{
}

OperandDouble::UnderflowException::UnderflowException(void) : std::underflow_error("OperandDouble : This operation would cause an underflow !")
{
}

OperandDouble::UnderflowException::~UnderflowException(void) throw()
{
}

OperandDouble::DivideByZeroException::DivideByZeroException(void) : std::invalid_argument("OpeandDouble : This operation would cause a division by zero !")
{
}

OperandDouble::DivideByZeroException::~DivideByZeroException(void) throw()
{
}
