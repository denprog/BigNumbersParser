#ifndef SCRIPT_H
#define SCRIPT_H

#include "Ast.h"
#include "Expression.h"
#include "Definition.h"

using namespace std;

namespace BigNumbersParser
{
	/**
	 * Spirit grammar for main script.
	 */
	template<typename Number>
	struct Script : qi::grammar<string::iterator, ScriptNode<Number>(), qi::space_type>
	{
		/**
		 * Constructor.
		 * @param [in] expr The expression.
		 */
		Script(string& expr) : Script::base_type(script), definition(expr), expression(expr)
		{
			script = 
				*(
					definition >> ";" | 
					expression >> ";"
				);
		}

		Definition<Number> definition;
    Expression<Number> expression;
		qi::rule<string::iterator, ScriptNode<Number>(), qi::space_type> script;
	};
};

#endif
