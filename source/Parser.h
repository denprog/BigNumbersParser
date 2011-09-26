#ifndef PARSER_H
#define PARSER_H

#include "stdafx.h"
#include "Integer.h"
#include "Rational.h"
#include "Real.h"
#include "Ast.h"
#include "Script.h"
#include "Solver.h"
#include "ErrorHandler.h"

using namespace std;

namespace spirit = boost::spirit;
namespace qi = spirit::qi;
namespace phx = boost::phoenix;
namespace fusion = boost::fusion;

namespace BigNumbersParser
{
	template<typename Number>
	struct Parser
	{
		Parser(const int precision);
		
		Number Parse(string& expression, const int precision = -1)
		{
			Number res;
			string::iterator iter = expression.begin();
			string::iterator end = expression.end();
			qi::space_type space;
			
			Script<Number> script(expression);
			ScriptNode<Number> scriptNode;
			
			bool r = phrase_parse(iter, end, script, space, scriptNode);
			res = solver(scriptNode, precision);
			
			return res;
		}

		Solver<Number> solver;
	};
};

#endif
