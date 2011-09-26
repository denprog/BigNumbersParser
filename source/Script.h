#ifndef SCRIPT_H
#define SCRIPT_H

#include "Ast.h"
#include "Expression.h"
#include "Definition.h"

using namespace std;

namespace BigNumbersParser
{
	template<typename Number>
	struct Script : qi::grammar<string::iterator, ScriptNode<Number>(), qi::space_type>
	{
		//Script(ErrorHandler& errorHandler);
		Script(string& expr) : Script::base_type(script), definition(expr), expression(expr)
		{
			script = 
				*(
					definition >> ";" | 
					expression >> ";"
				);
		}

		Expression<Number> expression;
		Definition<Number> definition;
		qi::rule<string::iterator, ScriptNode<Number>(), qi::space_type> script;
	};
};

#endif
