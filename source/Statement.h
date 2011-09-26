#ifndef STATEMENT_H
#define STATEMENT_H

#include "Ast.h"

namespace BigNumbersParser
{
	template<typename Number>
	struct Statement : qi::grammar<std::string::iterator, VariableNode<Number>(), qi::space_type>
	{
		Statement()
		{
		}

		qi::rule<string::iterator, VariableNode<Number>(), qi::space_type> variable;
	};
};

#endif
