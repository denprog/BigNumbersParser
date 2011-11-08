#ifndef DEFINITION_H
#define DEFINITION_H

#include "Ast.h"
#include "Expression.h"

namespace BigNumbersParser
{
	/**
	 * Spirit grammar for definitions.
	 */
	template<typename Number>
	struct Definition : qi::grammar<string::iterator, DefinitionNode<Number>(), qi::space_type>
	{
		/**
		 * Constructor.
		 * @param [in] expr The expression.
		 */
		Definition(string& expr) : Definition::base_type(definition), expression(expr), returnExpression(expr)
		{
			using boost::spirit::qi::lit;
			using boost::spirit::qi::raw;
			using boost::spirit::qi::lexeme;
			using boost::spirit::qi::alnum;
			using boost::spirit::qi::alpha;
			using boost::spirit::qi::on_error;
			using boost::spirit::qi::fail;
			
			//the definition is a variable or a function
			definition = 
				variable | 
				function;
			
			//the function definition
			function = 
				identifier >> 
				'(' >> argumentList >> ')' >> 
				(lit('=') >  
				'{' > "return" > returnExpression > ';' > '}');
			
			//the function's argument list
			argumentList = 
				-(identifier % ',');
			
			//the variable definition
			variable = 
				identifier >> 
				('=' > expression);
			
			//identifier is a name
			identifier = 
				name;
			
			//name is a letter-numeric string with an letter in the beginning
			name = 
				raw[lexeme[(alpha | '_') >> *(alnum | '_')]];

			//BOOST_SPIRIT_DEBUG_NODE(definition);
			//BOOST_SPIRIT_DEBUG_NODE(argumentList);
			//BOOST_SPIRIT_DEBUG_NODE(identifier);
			//BOOST_SPIRIT_DEBUG_NODE(name);
		}

		qi::rule<string::iterator, DefinitionNode<Number>(), qi::space_type> definition;
		qi::rule<string::iterator, FunctionNode<Number>(), qi::space_type> function;
		qi::rule<string::iterator, VariableNode<Number>(), qi::space_type> variable;
		qi::rule<string::iterator, string(), qi::space_type> name;
		qi::rule<string::iterator, IdentifierNode<Number>(), qi::space_type> identifier;
		qi::rule<string::iterator, std::list<IdentifierNode<Number> >(), qi::space_type> argumentList;
		//qi::rule<string::iterator, ExpressionNode<Number>(), qi::space_type> body;
		Expression<Number> expression;
		Expression<Number> returnExpression;
	};
};

#endif
