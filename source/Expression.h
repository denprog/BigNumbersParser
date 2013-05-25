#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "stdafx.h"
#include "Ast.h"
#include "ErrorHandler.h"
#include "Annotation.h"

namespace BigNumbersParser
{
	/**
	 * Spirit grammar for expression.
	 */
	template<typename Number>
	struct Expression : qi::grammar<string::iterator, ExpressionNode<Number>(), qi::space_type>
	{
		Expression(string& expr);

		typedef boost::variant<
			Number, 
			boost::recursive_wrapper<IdentifierNode<Number> >, 
			boost::recursive_wrapper<UnaryOperationNode<Number> >, 
			boost::recursive_wrapper<OperationNode<Number> >, 
			boost::recursive_wrapper<FunctionCallNode<Number> >, 
			boost::recursive_wrapper<ExpressionNode<Number> > >
			Operand;
		
		qi::rule<string::iterator, ExpressionNode<Number>(), qi::space_type> expression, term, addition, multiplication;
		qi::rule<string::iterator, Operand(), qi::space_type> unary;
		qi::rule<string::iterator, OperationNode<Number>(), qi::space_type> multiply;
		qi::rule<string::iterator, UnaryOperationNode<Number>(), qi::space_type> unaryOperation;
		qi::rule<string::iterator, IdentifierNode<Number>(), qi::space_type> identifier;
		qi::rule<string::iterator, FunctionCallNode<Number>(), qi::space_type> functionCall;
		qi::rule<string::iterator, string(), qi::space_type> str, expNumber;
		qi::rule<string::iterator, string(), qi::space_type> name;
		qi::rule<string::iterator, Number(), qi::space_type> number;
	};
};

#endif
