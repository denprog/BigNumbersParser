#ifndef SOLVER_H
#define SOLVER_H

#include "Ast.h"
#include "Script.h"

namespace BigNumbersParser
{
	typedef Integer (*IntegerBinaryFunc)(const Integer& num1, const Integer& num2);
	typedef Real (*RealUnaryFunc)(const Real& num1);
	typedef Real (*RealBinaryFunc)(const Real& num1, const Real& num2);
	typedef Real (*RealTrigonometricFunc)(const Real& num1, const AngleMeasure angleMeasure);
	
	typedef Integer (*IntegerVariable)();
	typedef Real (*RealPrecisionVariable)(const int precision);
	typedef Rational (*RationalVariable)();

	template<typename Number>
	struct SolverSymbols
	{
		typedef pair<std::string, Number> TempVariable;

		//build-in functions' typedefs
		typedef Number (*UnaryFunction)(const Number& num);
		typedef Number (*BinaryFunction)(const Number& num1, const Number& num2);
		typedef Number (*TrigonometricFunction)(const Number& num1, const AngleMeasure angleMeasure);
		typedef boost::variant<UnaryFunction, BinaryFunction, TrigonometricFunction> BuildinFunction;
		
		//build-in variables' typedefs
		typedef Number (*Variable)();
		typedef Number (*PrecisionVariable)(const int precision);
		typedef boost::variant<Variable, PrecisionVariable> BuildinVariable;

		mutable deque<TempVariable> tempVariables; ///< The temporary variables
		mutable deque<VariableNode<Number> > variables;	///< The variables
		mutable vector<FunctionNode<Number> > functions; ///< The functions

		map<string, BuildinFunction> buildinFunctions; ///< The buildin functions
		map<string, BuildinVariable> buildinVariables; ///< The buildin variables
	};
		
	/**
	 * Solver.
	 */
	template<typename Number>
	struct Solver : public boost::static_visitor<Number>
	{
		typedef typename std::list<ExpressionNode<Number> >::const_iterator ExpressionNodesIter;		
		typedef typename std::list<IdentifierNode<Number> >::const_iterator IdentifierNodesIter;
		
		typedef typename SolverSymbols<Number>::TempVariable TempVariable;
		typedef typename SolverSymbols<Number>::UnaryFunction UnaryFunction;
		typedef typename SolverSymbols<Number>::BinaryFunction BinaryFunction;
		typedef typename SolverSymbols<Number>::TrigonometricFunction TrigonometricFunction;
		typedef typename SolverSymbols<Number>::BuildinFunction BuildinFunction;
		
		typedef typename SolverSymbols<Number>::PrecisionVariable PrecisionVariable;
		typedef typename SolverSymbols<Number>::BuildinVariable BuildinVariable;
		typedef typename SolverSymbols<Number>::Variable Variable;
		
		SolverSymbols<Number>* symbols;
		
		/**
		 * Constructor.
		 * @param _precision The precision.
		 * @param _leftValue (optional) the left value.
		 */
		Solver(int _precision, Number _leftValue = Number(), SolverSymbols<Number>* _symbols = NULL);
		
		/**
		 * Sets a precision.
		 * @param prec The prec.
		 */
		void SetPrecision(int prec)
		{
			precision = prec;
		}
		
		/**
		 * Visitor's functor for Number.
		 */
		Number operator()(Number n) const
		{
			n.SetPrecision(precision);
			return n;
		}

		/**
		 * Visitor's functor for ExpressionNode.
		 */
		Number operator()(ExpressionNode<Number> const& expr) const
		{
			//calculate all the expression's nodes
			Number res = boost::apply_visitor(*this, expr.first);
			BOOST_FOREACH(typename OperationNode<Number>::Operand const& op, expr.rest)
			{
				res = boost::apply_visitor(Solver<Number>(precision, res, symbols), op);
			}
			
			return res;
		}
		
		/**
		 * Visitor's functor for DefinitionNode.
		 */
		Number operator()(DefinitionNode<Number> const& op) const
		{
			//pass the definition to the special functor
			boost::apply_visitor(*this, op.definition);
			return Number();
		}

		/**
		 * Visitor's functor for VariableNode.
		 */
		Number operator()(VariableNode<Number> const& op) const
		{
			//store the variable
			PushVariable(op);
			return Number();
		}
		
		/**
		 * Visitor's functor for FunctionNode.
		 */
		Number operator()(FunctionNode<Number> const& op) const
		{
			//store the function
			AddFunction(op);
			return Number();
		}

		/**
		 * Visitor's functor for UnaryOperationNode.
		 */
		Number operator()(UnaryOperationNode<Number> const& op) const
		{
			Number right = boost::apply_visitor(*this, op.operand);
			switch (op.op)
			{
			case '+':
				return right;
			case '-':
				return -right;
			}
			
			return Number();
		}

		/**
		 * Visitor's functor for OperationNode.
		 * @exception MathException Thrown when the mathematics error condition occurs.
		 */
		Number operator()(OperationNode<Number> const& op) const
		{
			Number right = boost::apply_visitor(*this, op.operand);
			
			try
			{
				//calculate the operation
				switch (op.op)
				{
				case '+':
					return leftValue + right;
				case '-':
					return leftValue - right;
				case '*':
					return leftValue * right;
				case '/':
					return leftValue / right;
				}
			}
			catch (MathException e)
			{
				throw MathException(e.id, op.pos, op.line);
			}
			
			return Number();
		}

		Number operator()(FunctionCallNode<Number> const& op) const;

		Number operator()(IdentifierNode<Number> const& op) const;
		
		/**
		 * The beginning of the solving.
		 */
		Number operator()(ScriptNode<Number> const& script, int prec = -1) const
		{
			if (prec != -1)
				precision = prec;
			
			Number res;
			//calculate all the script nodes
			BOOST_FOREACH(typename ScriptNode<Number>::Operand const& op, script.list)
			{
				res = boost::apply_visitor(*this, op);
			}
			
			return res;
		}

		/**
		 * Pushes a temporary variable.
		 * @param name The name.
		 * @param [in,out] value The value.
		 */
		void PushTempVariable(const string& name, Number& value) const
		{
			symbols->tempVariables.push_back(TempVariable(name, value));
		}
		
		/**
		 * Pops a number of the temporary variables.
		 * @param count (optional) number of variables.
		 */
		void PopTempVariable(int count = 1) const
		{
			for (int i = 0; i < count; ++i)
				symbols->tempVariables.pop_back();
		}
		
		/**
		 * Searches for the temporary variable.
		 * @param name The name.
		 * @return null if it fails, else the found temporary variable.
		 */
		TempVariable* FindTempVariable(const string& name) const
		{
			for (int i = symbols->tempVariables.size() - 1; i >= 0; --i)
			{
				if (symbols->tempVariables[i].first == name)
					return &symbols->tempVariables[i];
			}
			
			return NULL;
		}

		/**
		 * Pushes a variable.
		 * @param var The variable.
		 */
		void PushVariable(VariableNode<Number> const& var) const
		{
			symbols->variables.push_back(var);
		}
		
		/**
		 * Pops the variable.
		 */
		void PopVariable() const
		{
			symbols->variables.pop_back();
		}

		/**
		 * Searches for the first variable.
		 * @param name The name.
		 * @return null if it fails, else the found variable.
		 */
		VariableNode<Number>* FindVariable(const string& name) const
		{
			for (int i = symbols->variables.size() - 1; i >= 0; --i)
			{
				if (symbols->variables[i].name.name == name)
					return &symbols->variables[i];
			}
			
			return NULL;
		}
		
		/**
		 * Adds a function.
		 * @param func The function.
		 */
		void AddFunction(FunctionNode<Number> const& func) const
		{
			for (int i = 0; i < (int)symbols->functions.size(); ++i)
			{
				if (symbols->functions[i].name.name == func.name.name)
				{
					symbols->functions[i] = func;
					return;
				}
			}

			symbols->functions.push_back((FunctionNode<Number>&)func);
		}
		
		/**
		 * Adds a buildin function.
		 * @param name The name.
		 * @param [in,out] func The function.
		 */
		void AddBuildinFunction(const char* name, UnaryFunction& func)
		{
			symbols->buildinFunctions[string(name)] = func;
		}

		/**
		 * Adds a buildin function.
		 * @param name The name.
		 * @param [in,out] func The function.
		 */
		void AddBuildinFunction(const char* name, BinaryFunction& func)
		{
			symbols->buildinFunctions[string(name)] = func;
		}

		/**
		 * Adds a buildin function.
		 * @param name The name.
		 * @param [in,out] func The function.
		 */
		void AddBuildinFunction(const char* name, TrigonometricFunction& func)
		{
			symbols->buildinFunctions[string(name)] = func;
		}
		
		/**
		 * Searches for the first buildin function.
		 * @param name The name.
		 * @return null if it fails, else the found buildin function.
		 */
		BuildinFunction* FindBuildinFunction(const string& name) const
		{
			typename map<string, BuildinFunction>::const_iterator iter = symbols->buildinFunctions.find(name);
			if (iter == symbols->buildinFunctions.end())
				return NULL;
			return (BuildinFunction*)&(*iter).second;
		}

		/**
		 * Adds a buildin variable.
		 * @param name The name.
		 * @param [in,out] var The variable.
		 */
		void AddBuildinVariable(const char* name, PrecisionVariable& var)
		{
			symbols->buildinVariables[string(name)] = var;
		}
		
		/**
		 * Searches for the first buildin variable.
		 * @param name The name.
		 * @return null if it fails, else the found buildin variable.
		 */
		BuildinVariable* FindBuildinVariable(const string& name) const
		{
			typename map<string, BuildinVariable>::const_iterator iter = symbols->buildinVariables.find(name);
			if (iter == symbols->buildinVariables.end())
				return NULL;
			return (BuildinVariable*)&(*iter).second;
		}
		
		mutable int precision; ///< The precision
		Number leftValue; ///< The left solved value
	};
};

#endif
