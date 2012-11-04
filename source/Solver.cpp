#include "stdafx.h"
#include "Solver.h"

namespace BigNumbersParser
{
	template<>
	deque<Solver<Integer>::TempVariable> Solver<Integer>::tempVariables;		
	template<>
	deque<VariableNode<Integer> > Solver<Integer>::variables;		
	template<>
	vector<FunctionNode<Integer> > Solver<Integer>::functions;
	template<>
	map<string, Solver<Integer>::BuildinFunction> Solver<Integer>::buildinFunctions;
	template<>
	map<string, Solver<Integer>::BuildinVariable> Solver<Integer>::buildinVariables;
	
	template<>
	deque<Solver<Real>::TempVariable> Solver<Real>::tempVariables;		
	template<>
	deque<VariableNode<Real> > Solver<Real>::variables;		
	template<>
	vector<FunctionNode<Real> > Solver<Real>::functions;
	template<>
	map<string, Solver<Real>::BuildinFunction> Solver<Real>::buildinFunctions;
	template<>
	map<string, Solver<Real>::BuildinVariable> Solver<Real>::buildinVariables;

	template<>
	deque<Solver<Rational>::TempVariable> Solver<Rational>::tempVariables;		
	template<>
	deque<VariableNode<Rational> > Solver<Rational>::variables;		
	template<>
	vector<FunctionNode<Rational> > Solver<Rational>::functions;
	template<>
	map<string, Solver<Rational>::BuildinFunction> Solver<Rational>::buildinFunctions;
	template<>
	map<string, Solver<Rational>::BuildinVariable> Solver<Rational>::buildinVariables;

	/**
	 * Visitor's functor for FunctionCallNode<Integer>.
	 */
	template<>
	Integer Solver<Integer>::operator()(FunctionCallNode<Integer> const& op) const
	{
		Integer res;
		
		//find in the user defined functions		
		for (int i = 0; i < (int)functions.size(); ++i)
		{
			const FunctionNode<Integer>& func = functions[i];
			if (func.name.name == op.name.name)
			{
				if (func.arguments.size() != op.arguments.size())
					throw SyntaxException(WrongArgumentsCount, op.pos, op.line);
				
				IdentifierNodesIter funcIter = func.arguments.begin();
				for (ExpressionNodesIter callIter = op.arguments.begin(); callIter != op.arguments.end(); ++callIter, ++funcIter)
				{
					Integer arg = (*this)(*callIter);
					PushTempVariable(funcIter->name, arg);
				}
				res = (*this)(func.returnExpression);
				PopTempVariable(op.arguments.size());
				return res;
			}
		}

		//find in the build-in functions		
		BuildinFunction* func = FindBuildinFunction(op.name.name);
		if (func)
		{
			try
			{
				UnaryFunction u = boost::get<UnaryFunction>(*func);
				if (op.arguments.size() != 1)
					throw SyntaxException(WrongArgumentsCount, op.pos, op.line);
				
				ExpressionNodesIter callIter = op.arguments.begin();
				Integer arg = (*this)(*callIter);
				return (*u)(arg);
			}
			catch (boost::bad_get)
			{
			}
			
			try
			{
				BinaryFunction b = boost::get<BinaryFunction>(*func);
				if (op.arguments.size() != 2)
					throw SyntaxException(WrongArgumentsCount, op.pos, op.line);
				
				ExpressionNodesIter callIter = op.arguments.begin();
				Integer arg1 = (*this)(*callIter++);
				Integer arg2 = (*this)(*callIter);
				return (*b)(arg1, arg2);
			}
			catch (boost::bad_get)
			{
			}
		}

		//there is no such a function		
		throw SyntaxException(UnknownIdentifier, op.pos, op.line);
		
		return res;
	}

	/**
	 * Visitor's functor for FunctionCallNode<Real>.
	 */
	template<>
	Real Solver<Real>::operator()(FunctionCallNode<Real> const& op) const
	{
		Real res;
		
		//find in the user defined functions		
		for (int i = 0; i < (int)functions.size(); ++i)
		{
			const FunctionNode<Real>& func = functions[i];
			if (func.name.name == op.name.name)
			{
				if (func.arguments.size() != op.arguments.size())
					throw SyntaxException(WrongArgumentsCount);
				
				IdentifierNodesIter funcIter = func.arguments.begin();
				for (ExpressionNodesIter callIter = op.arguments.begin(); callIter != op.arguments.end(); ++callIter, ++funcIter)
				{
					Real arg = (*this)(*callIter);
					PushTempVariable(funcIter->name, arg);
				}
				res = (*this)(func.returnExpression);
				PopTempVariable(op.arguments.size());
				return res;
			}
		}
		
		//find in the build-in functions		
		BuildinFunction* func = FindBuildinFunction(op.name.name);
		if (func)
		{
			try
			{
				UnaryFunction u = boost::get<UnaryFunction>(*func);
				if (op.arguments.size() != 1)
					throw SyntaxException(WrongArgumentsCount, op.pos, op.line);
				
				ExpressionNodesIter callIter = op.arguments.begin();
				Real arg = (*this)(*callIter);
				return (*u)(arg);
			}
			catch (boost::bad_get)
			{
			}
			
			try
			{
				BinaryFunction b = boost::get<BinaryFunction>(*func);
				if (op.arguments.size() != 2)
					throw SyntaxException(WrongArgumentsCount, op.pos, op.line);
				
				ExpressionNodesIter callIter = op.arguments.begin();
				Real arg1 = (*this)(*callIter++);
				Real arg2 = (*this)(*callIter);
				return (*b)(arg1, arg2);
			}
			catch (boost::bad_get)
			{
			}
			
			try
			{
				RealTrigonometricFunc t = boost::get<RealTrigonometricFunc>(*func);
				if (op.arguments.size() != 1)
					throw SyntaxException(WrongArgumentsCount, op.pos, op.line);
				
				ExpressionNodesIter callIter = op.arguments.begin();
				Real arg = (*this)(*callIter);
				return (*t)(arg, RADIAN);
			}
			catch (boost::bad_get)
			{
			}
		}

		//there is no such a function		
		throw SyntaxException(UnknownIdentifier, op.pos, op.line);
		
		return res;
	}

	/**
	 * Visitor's functor for FunctionCallNode<Rational>.
	 */
	template<>
	Rational Solver<Rational>::operator()(FunctionCallNode<Rational> const& op) const
	{
		Rational res;
		
		//find in the user defined functions		
		for (int i = 0; i < (int)functions.size(); ++i)
		{
			const FunctionNode<Rational>& func = functions[i];
			if (func.name.name == op.name.name)
			{
				if (func.arguments.size() != op.arguments.size())
					throw SyntaxException(WrongArgumentsCount, op.pos, op.line);
				
				IdentifierNodesIter funcIter = func.arguments.begin();
				for (ExpressionNodesIter callIter = op.arguments.begin(); callIter != op.arguments.end(); ++callIter, ++funcIter)
				{
					Rational arg = (*this)(*callIter);
					PushTempVariable(funcIter->name, arg);
				}
				res = (*this)(func.returnExpression);
				PopTempVariable(op.arguments.size());
				return res;
			}
		}

		//find in the build-in functions		
		BuildinFunction* func = FindBuildinFunction(op.name.name);
		if (func)
		{
			try
			{
				UnaryFunction u = boost::get<UnaryFunction>(*func);
				if (op.arguments.size() != 1)
					throw SyntaxException(WrongArgumentsCount, op.pos, op.line);
				
				ExpressionNodesIter callIter = op.arguments.begin();
				Rational arg = (*this)(*callIter);
				return (*u)(arg);
			}
			catch (boost::bad_get)
			{
			}
			
			try
			{
				BinaryFunction b = boost::get<BinaryFunction>(*func);
				if (op.arguments.size() != 2)
					throw SyntaxException(WrongArgumentsCount, op.pos, op.line);
				
				ExpressionNodesIter callIter = op.arguments.begin();
				Rational arg1 = (*this)(*callIter++);
				Rational arg2 = (*this)(*callIter);
				return (*b)(arg1, arg2);
			}
			catch (boost::bad_get)
			{
			}
		}

		//there is no such a function		
		throw SyntaxException(UnknownIdentifier, op.pos, op.line);
		
		return res;
	}

	/**
	 * Visitor's functor for IdentifierNode<Integer>.
	 */
	template<>
	Integer Solver<Integer>::operator()(IdentifierNode<Integer> const& op) const
	{
		TempVariable* t = FindTempVariable(op.name);
		if (t)
			return t->second;
		
		//find in user defined variables
		VariableNode<Integer>* v = FindVariable(op.name);
		if (v)
			return (*this)(v->expression);
		
		BuildinVariable* var = FindBuildinVariable(op.name);
		if (var)
		{
			try
			{
				IntegerVariable v = boost::get<Variable>(*var);
				return (*v)();
			}
			catch (boost::bad_get)
			{
			}
		}
		
		//there is no such an identifier
		throw SyntaxException(UnknownIdentifier, op.pos, op.line);
		
		return 0;
	}

	/**
	 * Visitor's functor for IdentifierNode<Real>.
	 */
	template<>
	Real Solver<Real>::operator()(IdentifierNode<Real> const& op) const
	{
		TempVariable* t = FindTempVariable(op.name);
		if (t)
			return t->second;
		
		//find in the user defined variables
		VariableNode<Real>* v = FindVariable(op.name);
		if (v)
			return (*this)(v->expression);
		
		//find in the build-in variables
		BuildinVariable* var = FindBuildinVariable(op.name);
		if (var)
		{
			try
			{
				RealPrecisionVariable v = boost::get<PrecisionVariable>(*var);
				return (*v)(precision);
			}
			catch (boost::bad_get)
			{
			}
		}
		
		//there is no such an identifier
		throw SyntaxException(UnknownIdentifier, op.pos, op.line);
		
		return Real();
	}

	/**
	 * Visitor's functor for IdentifierNode<Rational>.
	 */
	template<>
	Rational Solver<Rational>::operator()(IdentifierNode<Rational> const& op) const
	{
		TempVariable* t = FindTempVariable(op.name);
		if (t)
			return t->second;
		
		//find in user defined variables
		VariableNode<Rational>* v = FindVariable(op.name);
		if (v)
			return (*this)(v->expression);
		
		BuildinVariable* var = FindBuildinVariable(op.name);
		if (var)
		{
			try
			{
				RationalVariable v = boost::get<Variable>(*var);
				return (*v)();
			}
			catch (boost::bad_get)
			{
			}
		}
		
		//there is no such an identifier
		throw SyntaxException(UnknownIdentifier, op.pos, op.line);
		
		return 0;
	}
}
