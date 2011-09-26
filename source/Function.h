#ifndef FUNCTION_H
#define FUNCTION_H

#include "Ast.h"

namespace BigNumbersParser
{
	template<typename Number>
	struct Function : qi::grammar<string::iterator, FunctionNode<Number>(), qi::space_type>
	{
		Function();

		qi::rule<string::iterator, FunctionNode<Number>(), qi::space_type> expression;
	};
};

#endif
