#include "stdafx.h"
#include "Function.h"

namespace BigNumbersParser
{
	template<>
	Function<BigNumbersParser::Integer>::Function() : Function::base_type(expression)
	{
	}
};
