#include "stdafx.h"
#include "Expression.h"

namespace BigNumbersParser
{
	template<>
	Expression<BigNumbersParser::Integer>::Expression(string& expr) : Expression::base_type(expression)
	{
		using boost::spirit::qi::char_;
		using boost::spirit::qi::raw;
		using boost::spirit::qi::lexeme;
		using boost::spirit::qi::alnum;
		using boost::spirit::qi::alpha;
		using boost::spirit::qi::on_error;
		using boost::spirit::qi::fail;
		using boost::phoenix::function;
		using namespace boost::phoenix::arg_names;
		qi::_1_type _1;
		qi::_3_type _3;

		expression = 
			addition.alias();
		
		addition = 
			multiplication >> 
			*(
				(char_('+') > multiplication) | 
				(char_('-') > multiplication)
			);
		
		multiplication = 
			unary >> 
			*(
				multiply
			);

		multiply = 
			char_('*') > unary | 
			char_('/') > unary;
		
		unary = 
			number | 
			functionCall | 
			identifier | 
			unaryOperation | 
			'(' > expression > ')';
		
		number = 
			str;
		
		str = 
			+char_("0-9");

		identifier = 
			name;
		
		name = 
			raw[lexeme[(alpha | '_') >> *(alnum | '_')]];

		unaryOperation = 
			(qi::char_('+') > unary) | 
			(qi::char_('-') > unary);
		
		functionCall = 
			identifier >> 
			'(' >> -(expression % ',') > ')';

		//annotate the items with an expression's position
		on_success(unary, boost::phoenix::function<Annotation<BigNumbersParser::Integer> >(Annotation<BigNumbersParser::Integer>(expr.begin(), expr.end()))(qi::_val, _1));
		on_success(addition, boost::phoenix::function<Annotation<BigNumbersParser::Integer> >(Annotation<BigNumbersParser::Integer>(expr.begin(), expr.end()))(qi::_val, _1));
		on_success(multiplication, boost::phoenix::function<Annotation<BigNumbersParser::Integer> >(Annotation<BigNumbersParser::Integer>(expr.begin(), expr.end()))(qi::_val, _1));
		on_success(multiply, boost::phoenix::function<Annotation<BigNumbersParser::Integer> >(Annotation<BigNumbersParser::Integer>(expr.begin(), expr.end()))(qi::_val, _1));
		on_success(identifier, boost::phoenix::function<Annotation<BigNumbersParser::Integer> >(Annotation<BigNumbersParser::Integer>(expr.begin(), expr.end()))(qi::_val, _1));
		
		//work out the exceptions
		on_error<fail>(expression, 
			boost::phoenix::function<ErrorHandler<SyntaxException> >(ErrorHandler<SyntaxException>(expr.begin(), expr.end(), SyntaxError))(_3));
		
		//BOOST_SPIRIT_DEBUG_NODE(expression);
		//BOOST_SPIRIT_DEBUG_NODE(addition);
		//BOOST_SPIRIT_DEBUG_NODE(multiplication);
		//BOOST_SPIRIT_DEBUG_NODE(number);
		//BOOST_SPIRIT_DEBUG_NODE(functionCall);
		//BOOST_SPIRIT_DEBUG_NODE(identifier);
	}

	template<>
	Expression<BigNumbersParser::Real>::Expression(string& expr) : Expression::base_type(expression)
	{
		using boost::spirit::qi::char_;
		using boost::spirit::qi::raw;
		using boost::spirit::qi::lexeme;
		using boost::spirit::qi::alnum;
		using boost::spirit::qi::alpha;
		using boost::spirit::qi::on_error;
		using boost::spirit::qi::fail;
		using boost::phoenix::function;
		using namespace boost::phoenix::arg_names;
		qi::_1_type _1;
		qi::_3_type _3;

		expression = 
			addition.alias();
		
		addition = 
			multiplication >> 
			*(
				(char_('+') > multiplication) | 
				(char_('-') > multiplication)
			);
		
		multiplication = 
			unary >> 
			*(
				multiply
			);

		multiply = 
			char_('*') > unary | 
			char_('/') > unary;
		
		unary = 
			number | 
			functionCall | 
			identifier | 
			unaryOperation | 
			'(' > expression > ')';
		
		number = 
			str;
		
		str = 
			+char_("0-9.");

		identifier = 
			name;
		
		name = 
			raw[lexeme[(alpha | '_') >> *(alnum | '_')]];

		unaryOperation = 
			(qi::char_('+') > unary) | 
			(qi::char_('-') > unary);
		
		functionCall = 
			identifier >> 
			'(' >> -(expression % ',') > ')';

		on_success(unary, boost::phoenix::function<Annotation<BigNumbersParser::Real> >(Annotation<BigNumbersParser::Real>(expr.begin(), expr.end()))(qi::_val, _1));
		on_success(addition, boost::phoenix::function<Annotation<BigNumbersParser::Real> >(Annotation<BigNumbersParser::Real>(expr.begin(), expr.end()))(qi::_val, _1));
		on_success(multiplication, boost::phoenix::function<Annotation<BigNumbersParser::Real> >(Annotation<BigNumbersParser::Real>(expr.begin(), expr.end()))(qi::_val, _1));
		on_success(multiply, boost::phoenix::function<Annotation<BigNumbersParser::Real> >(Annotation<BigNumbersParser::Real>(expr.begin(), expr.end()))(qi::_val, _1));
		on_success(functionCall, boost::phoenix::function<Annotation<BigNumbersParser::Real> >(Annotation<BigNumbersParser::Real>(expr.begin(), expr.end()))(qi::_val, _1));
		on_success(identifier, boost::phoenix::function<Annotation<BigNumbersParser::Real> >(Annotation<BigNumbersParser::Real>(expr.begin(), expr.end()))(qi::_val, _1));
		
		on_error<fail>(expression, 
			boost::phoenix::function<ErrorHandler<SyntaxException> >(ErrorHandler<SyntaxException>(expr.begin(), expr.end(), SyntaxError))(_3));
		
		//BOOST_SPIRIT_DEBUG_NODE(expression);
		//BOOST_SPIRIT_DEBUG_NODE(addition);
		//BOOST_SPIRIT_DEBUG_NODE(multiplication);
		//BOOST_SPIRIT_DEBUG_NODE(number);
		//BOOST_SPIRIT_DEBUG_NODE(functionCall);
		//BOOST_SPIRIT_DEBUG_NODE(identifier);
	}

	template<>
	Expression<BigNumbersParser::Rational>::Expression(string& expr) : Expression::base_type(expression)
	{
		using boost::spirit::qi::char_;
		using boost::spirit::qi::raw;
		using boost::spirit::qi::lexeme;
		using boost::spirit::qi::alnum;
		using boost::spirit::qi::alpha;
		using boost::spirit::qi::on_error;
		using boost::spirit::qi::fail;
		using boost::phoenix::function;
		using namespace boost::phoenix::arg_names;
		qi::_1_type _1;
		qi::_3_type _3;

		expression = 
			addition.alias();
		
		addition = 
			multiplication >> 
			*(
				(char_('+') > multiplication) | 
				(char_('-') > multiplication)
			);
		
		multiplication = 
			unary >> 
			*(
				multiply
			);

		multiply = 
			char_('*') > unary | 
			char_('/') > unary;
		
		unary = 
			number | 
			functionCall | 
			identifier | 
			unaryOperation | 
			'(' > expression > ')';
		
		number = 
			str;
		
		str = 
			+char_("0-9");

		identifier = 
			name;
		
		name = 
			raw[lexeme[(alpha | '_') >> *(alnum | '_')]];

		unaryOperation = 
			(qi::char_('+') > unary) | 
			(qi::char_('-') > unary);
		
		functionCall = 
			identifier >> 
			'(' >> -(expression % ',') > ')';

		//annotate the items with an expression's position
		on_success(unary, boost::phoenix::function<Annotation<BigNumbersParser::Rational> >(Annotation<BigNumbersParser::Rational>(expr.begin(), expr.end()))(qi::_val, _1));
		on_success(addition, boost::phoenix::function<Annotation<BigNumbersParser::Rational> >(Annotation<BigNumbersParser::Rational>(expr.begin(), expr.end()))(qi::_val, _1));
		on_success(multiplication, boost::phoenix::function<Annotation<BigNumbersParser::Rational> >(Annotation<BigNumbersParser::Rational>(expr.begin(), expr.end()))(qi::_val, _1));
		on_success(multiply, boost::phoenix::function<Annotation<BigNumbersParser::Rational> >(Annotation<BigNumbersParser::Rational>(expr.begin(), expr.end()))(qi::_val, _1));
		on_success(identifier, boost::phoenix::function<Annotation<BigNumbersParser::Rational> >(Annotation<BigNumbersParser::Rational>(expr.begin(), expr.end()))(qi::_val, _1));
		
		//work out the exceptions
		on_error<fail>(expression, 
			boost::phoenix::function<ErrorHandler<SyntaxException> >(ErrorHandler<SyntaxException>(expr.begin(), expr.end(), SyntaxError))(_3));
		
		//BOOST_SPIRIT_DEBUG_NODE(expression);
		//BOOST_SPIRIT_DEBUG_NODE(addition);
		//BOOST_SPIRIT_DEBUG_NODE(multiplication);
		//BOOST_SPIRIT_DEBUG_NODE(number);
		//BOOST_SPIRIT_DEBUG_NODE(functionCall);
		//BOOST_SPIRIT_DEBUG_NODE(identifier);
	}
};
