#ifndef DEFINITION_H
#define DEFINITION_H

#include "Ast.h"
#include "Expression.h"

namespace BigNumbersParser
{
	template<typename Number>
	struct Definition : qi::grammar<string::iterator, DefinitionNode<Number>(), qi::space_type>
	{
		Definition(string& expr) : base_type(definition), expression(expr), returnExpression(expr)
		{
			using boost::spirit::qi::lit;
			using boost::spirit::qi::raw;
			using boost::spirit::qi::lexeme;
			using boost::spirit::qi::alnum;
			using boost::spirit::qi::alpha;
			using boost::spirit::qi::on_error;
			using boost::spirit::qi::fail;
			
			definition = 
				variable | 
				function;
			
			function = 
				identifier >> 
				'(' >> argumentList >> ')' >> 
				(lit('=') >  
				'{' > "return" > returnExpression > ';' > '}');
			
			argumentList = 
				-(identifier % ',');
			
			variable = 
				identifier >> 
				('=' > expression);
				
			identifier = 
				name;
			
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
