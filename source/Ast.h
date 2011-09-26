#ifndef AST_H
#define AST_H

#include "stdafx.h"
#include "Integer.h"
#include "Real.h"
#include "Rational.h"

namespace BigNumbersParser
{
	template<typename Number>
	struct IdentifierNode;
	template<typename Number>
	struct OperationNode;
	template<typename Number>
	struct VariableNode;
	template<typename Number>
	struct FunctionCallNode;
	template<typename Number>
	struct ExpressionNode;

	struct ExpressionPosition
	{
		ExpressionPosition()
		{
			pos = -1;
			line = -1;
		}
		
		int pos;
		int line;
	};
	
	template<typename Number>
	struct IdentifierNode : public ExpressionPosition
	{
		std::string name;
	};

	template<typename Number>
	struct UnaryOperationNode
	{
		typedef boost::variant<
			Number, 
			boost::recursive_wrapper<IdentifierNode<Number> >, 
			boost::recursive_wrapper<UnaryOperationNode<Number> >, 
			boost::recursive_wrapper<OperationNode<Number> >, 
			boost::recursive_wrapper<FunctionCallNode<Number> >, 
			boost::recursive_wrapper<ExpressionNode<Number> > > 
			Operand;
		
		char op;
		Operand operand;
	};
	
	template<typename Number>
	struct OperationNode : ExpressionPosition
	{
		typedef boost::variant<
			Number, 
			boost::recursive_wrapper<UnaryOperationNode<Number> >, 
			boost::recursive_wrapper<IdentifierNode<Number> >, 
			boost::recursive_wrapper<OperationNode<Number> >, 
			boost::recursive_wrapper<FunctionCallNode<Number> >, 
			boost::recursive_wrapper<ExpressionNode<Number> > > 
			Operand;
		
		char op;
		Operand operand;
	};
	
	template<typename Number>
	struct VariableNode
	{
		IdentifierNode<Number> name;
		ExpressionNode<Number> expression;
	};
	
	template<typename Number>
	struct FunctionNode
	{
		IdentifierNode<Number> name;
		std::list<IdentifierNode<Number> > arguments;
		ExpressionNode<Number> returnExpression;
	};

	template<typename Number>
	struct DefinitionNode
	{
		typedef boost::variant<
			boost::recursive_wrapper<VariableNode<Number> >, 
			boost::recursive_wrapper<FunctionNode<Number> > > 
			Definition;
		
		Definition definition;
	};
	
	template<typename Number>
	struct FunctionCallNode : ExpressionPosition
	{
		IdentifierNode<Number> name;
		std::list<ExpressionNode<Number> > arguments;
	};
	
	template<typename Number>
	struct ExpressionNode : ExpressionPosition
	{
		typedef Number value_type;
		typedef boost::variant<
			Number, 
			boost::recursive_wrapper<IdentifierNode<Number> >, 
			boost::recursive_wrapper<UnaryOperationNode<Number> >, 
			boost::recursive_wrapper<OperationNode<Number> >,
			boost::recursive_wrapper<FunctionCallNode<Number> >, 
			boost::recursive_wrapper<ExpressionNode<Number> > >
			Operand;
		
		Operand first;
		std::list<OperationNode<Number> > rest;
	};
	
	template<typename Number>
	struct ScriptNode
	{
		typedef Number value_type;
		typedef boost::variant<
			boost::recursive_wrapper<DefinitionNode<Number> >, 
			boost::recursive_wrapper<ExpressionNode<Number> > > 
			Operand;
		
		std::list<Operand> list;
	};
};

//Integer adaptors

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::UnaryOperationNode<BigNumbersParser::Integer>, 
	(char, op)(BigNumbersParser::UnaryOperationNode<BigNumbersParser::Integer>::Operand, operand))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::OperationNode<BigNumbersParser::Integer>, 
	(char, op)(BigNumbersParser::OperationNode<BigNumbersParser::Integer>::Operand, operand))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::VariableNode<BigNumbersParser::Integer>, 
	(BigNumbersParser::IdentifierNode<BigNumbersParser::Integer>, name)(BigNumbersParser::ExpressionNode<BigNumbersParser::Integer>, expression))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::FunctionNode<BigNumbersParser::Integer>, 
	(BigNumbersParser::IdentifierNode<BigNumbersParser::Integer>, name)
	(std::list<BigNumbersParser::IdentifierNode<BigNumbersParser::Integer> >, arguments)
	//(BigNumbersParser::ExpressionNode<BigNumbersParser::Integer>, expression)
	(BigNumbersParser::ExpressionNode<BigNumbersParser::Integer>, returnExpression))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::DefinitionNode<BigNumbersParser::Integer>, 
	(BigNumbersParser::DefinitionNode<BigNumbersParser::Integer>::Definition, definition))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::IdentifierNode<BigNumbersParser::Integer>, 
	(std::string, name))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::FunctionCallNode<BigNumbersParser::Integer>, 
	(BigNumbersParser::IdentifierNode<BigNumbersParser::Integer>, name)
	(std::list<BigNumbersParser::ExpressionNode<BigNumbersParser::Integer> >, arguments))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::ExpressionNode<BigNumbersParser::Integer>, 
	(BigNumbersParser::ExpressionNode<BigNumbersParser::Integer>::Operand, first)(std::list<BigNumbersParser::OperationNode<BigNumbersParser::Integer> >, rest))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::ScriptNode<BigNumbersParser::Integer>, 
	(std::list<BigNumbersParser::ScriptNode<BigNumbersParser::Integer>::Operand>, list))

//Real adaptors

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::UnaryOperationNode<BigNumbersParser::Real>, 
	(char, op)(BigNumbersParser::UnaryOperationNode<BigNumbersParser::Real>::Operand, operand))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::OperationNode<BigNumbersParser::Real>, 
	(char, op)(BigNumbersParser::OperationNode<BigNumbersParser::Real>::Operand, operand))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::VariableNode<BigNumbersParser::Real>, 
	(BigNumbersParser::IdentifierNode<BigNumbersParser::Real>, name)(BigNumbersParser::ExpressionNode<BigNumbersParser::Real>, expression))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::FunctionNode<BigNumbersParser::Real>, 
	(BigNumbersParser::IdentifierNode<BigNumbersParser::Real>, name)
	(std::list<BigNumbersParser::IdentifierNode<BigNumbersParser::Real> >, arguments)
	//(BigNumbersParser::ExpressionNode<BigNumbersParser::Real>, expression)
	(BigNumbersParser::ExpressionNode<BigNumbersParser::Real>, returnExpression))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::DefinitionNode<BigNumbersParser::Real>, 
	(BigNumbersParser::DefinitionNode<BigNumbersParser::Real>::Definition, definition))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::IdentifierNode<BigNumbersParser::Real>, 
	(std::string, name))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::FunctionCallNode<BigNumbersParser::Real>, 
	(BigNumbersParser::IdentifierNode<BigNumbersParser::Real>, name)
	(std::list<BigNumbersParser::ExpressionNode<BigNumbersParser::Real> >, arguments))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::ExpressionNode<BigNumbersParser::Real>, 
	(BigNumbersParser::ExpressionNode<BigNumbersParser::Real>::Operand, first)(std::list<BigNumbersParser::OperationNode<BigNumbersParser::Real> >, rest))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::ScriptNode<BigNumbersParser::Real>, 
	(std::list<BigNumbersParser::ScriptNode<BigNumbersParser::Real>::Operand>, list))

//Rational adaptors

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::UnaryOperationNode<BigNumbersParser::Rational>, 
	(char, op)(BigNumbersParser::UnaryOperationNode<BigNumbersParser::Rational>::Operand, operand))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::OperationNode<BigNumbersParser::Rational>, 
	(char, op)(BigNumbersParser::OperationNode<BigNumbersParser::Rational>::Operand, operand))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::VariableNode<BigNumbersParser::Rational>, 
	(BigNumbersParser::IdentifierNode<BigNumbersParser::Rational>, name)(BigNumbersParser::ExpressionNode<BigNumbersParser::Rational>, expression))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::FunctionNode<BigNumbersParser::Rational>, 
	(BigNumbersParser::IdentifierNode<BigNumbersParser::Rational>, name)
	(std::list<BigNumbersParser::IdentifierNode<BigNumbersParser::Rational> >, arguments)
	//(BigNumbersParser::ExpressionNode<BigNumbersParser::Rational>, expression)
	(BigNumbersParser::ExpressionNode<BigNumbersParser::Rational>, returnExpression))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::DefinitionNode<BigNumbersParser::Rational>, 
	(BigNumbersParser::DefinitionNode<BigNumbersParser::Rational>::Definition, definition))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::IdentifierNode<BigNumbersParser::Rational>, 
	(std::string, name))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::FunctionCallNode<BigNumbersParser::Rational>, 
	(BigNumbersParser::IdentifierNode<BigNumbersParser::Rational>, name)
	(std::list<BigNumbersParser::ExpressionNode<BigNumbersParser::Rational> >, arguments))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::ExpressionNode<BigNumbersParser::Rational>, 
	(BigNumbersParser::ExpressionNode<BigNumbersParser::Rational>::Operand, first)(std::list<BigNumbersParser::OperationNode<BigNumbersParser::Rational> >, rest))

BOOST_FUSION_ADAPT_STRUCT(BigNumbersParser::ScriptNode<BigNumbersParser::Rational>, 
	(std::list<BigNumbersParser::ScriptNode<BigNumbersParser::Rational>::Operand>, list))

#endif
