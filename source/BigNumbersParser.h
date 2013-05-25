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
	/**
	 * Big numbers parser.
	 */
	template<typename Number>
	struct Parser
	{
		Parser(const int precision);
		
		/**
		 * Parses an expression.
		 * @param [in,out] expression The expression.
		 * @param precision	(optional) the precision.
		 * @return The result.
		 */
		Number Parse(string expression, const int precision = -1);

		/**
		 * Sets a precision.
		 * @param precision The precision.
		 */
		void SetPrecision(const int precision)
		{
			solver.SetPrecision(precision);
		}
		
		Solver<Number> solver;	///< The solver
	};
};

#endif
