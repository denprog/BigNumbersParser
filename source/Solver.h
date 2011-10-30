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

	/**
	 * Solver.
	 */
	template<typename Number>
	struct Solver : public boost::static_visitor<Number>
	{
		typedef typename std::list<ExpressionNode<Number> >::const_iterator ExpressionNodesIter;		
		typedef typename std::list<IdentifierNode<Number> >::const_iterator IdentifierNodesIter;
		
		//build-in functions' typedefs
		typedef typename Number (*UnaryFunction)(const Number& num);
		typedef typename Number (*BinaryFunction)(const Number& num1, const Number& num2);
		typedef typename Number (*TrigonometricFunc)(const Number& num1, const AngleMeasure angleMeasure);
		typedef boost::variant<UnaryFunction, BinaryFunction, TrigonometricFunc> BuildinFunction;
		
		//build-in variables' typedefs
		typedef typename Number (*Variable)();
		typedef typename Number (*PrecisionVariable)(const int precision);
		typedef boost::variant<Variable, PrecisionVariable> BuildinVariable;

		/**
		 * Constructor.
		 * @param _precision The precision.
		 * @param _leftValue (optional) the left value.
		 */
		Solver(int _precision, Number _leftValue = Number()) : precision(_precision), leftValue(_leftValue)
		{
		}
		
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
			BOOST_FOREACH(OperationNode<Number>::Operand const& op, expr.rest)
			{
				res = boost::apply_visitor(Solver<Number>(precision, res), op);
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
			
			return 0;
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
			
			return 0;
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
			BOOST_FOREACH(ScriptNode<Number>::Operand const& op, script.list)
			{
				res = boost::apply_visitor(*this, op);
			}
			
			return res;
		}

		typedef pair<string, Number> TempVariable;

		/**
		 * Pushes a temporary variable.
		 * @param name The name.
		 * @param [in,out] value The value.
		 */
		void PushTempVariable(const string& name, Number& value) const
		{
			tempVariables.push_back(TempVariable(name, value));
		}
		
		/**
		 * Pops a number of the temporary variables.
		 * @param count (optional) number of variables.
		 */
		void PopTempVariable(int count = 1) const
		{
			for (int i = 0; i < count; ++i)
				tempVariables.pop_back();
		}
		
		/**
		 * Searches for the temporary variable.
		 * @param name The name.
		 * @return null if it fails, else the found temporary variable.
		 */
		TempVariable* FindTempVariable(const string& name) const
		{
			for (int i = tempVariables.size() - 1; i >= 0; --i)
			{
				if (tempVariables[i].first == name)
					return &tempVariables[i];
			}
			
			return NULL;
		}

		/**
		 * Pushes a variable.
		 * @param var The variable.
		 */
		void PushVariable(VariableNode<Number> const& var) const
		{
			variables.push_back(var);
		}
		
		/**
		 * Pops the variable.
		 */
		void PopVariable() const
		{
			variables.pop_back();
		}

		/**
		 * Searches for the first variable.
		 * @param name The name.
		 * @return null if it fails, else the found variable.
		 */
		VariableNode<Number>* FindVariable(const string& name) const
		{
			for (int i = variables.size() - 1; i >=0; --i)
			{
				if (variables[i].name.name == name)
					return &variables[i];
			}
			
			return NULL;
		}
		
		/**
		 * Adds a function.
		 * @param func The function.
		 */
		void AddFunction(FunctionNode<Number> const& func) const
		{
			for (int i = 0; i < (int)functions.size(); ++i)
			{
				if (functions[i].name.name == func.name.name)
				{
					functions[i] = func;
					return;
				}
			}

			functions.push_back((FunctionNode<Number>&)func);
		}
		
		/**
		 * Adds a buildin function.
		 * @param name The name.
		 * @param [in,out] func The function.
		 */
		void AddBuildinFunction(const char* name, UnaryFunction& func)
		{
			buildinFunctions[string(name)] = func;
		}

		/**
		 * Adds a buildin function.
		 * @param name The name.
		 * @param [in,out] func The function.
		 */
		void AddBuildinFunction(const char* name, BinaryFunction& func)
		{
			buildinFunctions[string(name)] = func;
		}

		/**
		 * Adds a buildin function.
		 * @param name The name.
		 * @param [in,out] func The function.
		 */
		void AddBuildinFunction(const char* name, TrigonometricFunc& func)
		{
			buildinFunctions[string(name)] = func;
		}
		
		/**
		 * Searches for the first buildin function.
		 * @param name The name.
		 * @return null if it fails, else the found buildin function.
		 */
		BuildinFunction* FindBuildinFunction(const string& name) const
		{
			map<string, BuildinFunction>::const_iterator iter = buildinFunctions.find(name);
			if (iter == buildinFunctions.end())
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
			buildinVariables[string(name)] = var;
		}
		
		/**
		 * Searches for the first buildin variable.
		 * @param name The name.
		 * @return null if it fails, else the found buildin variable.
		 */
		BuildinVariable* FindBuildinVariable(const string& name) const
		{
			map<string, BuildinVariable>::const_iterator iter = buildinVariables.find(name);
			if (iter == buildinVariables.end())
				return NULL;
			return (BuildinVariable*)&(*iter).second;
		}
		
		static deque<TempVariable> tempVariables; ///< The temporary variables
		static deque<VariableNode<Number> > variables;	///< The variables
		static vector<FunctionNode<Number> > functions; ///< The functions
		
		static map<string, BuildinFunction> buildinFunctions; ///< The buildin functions
		static map<string, BuildinVariable> buildinVariables; ///< The buildin variables
		
		mutable int precision; ///< The precision
		Number leftValue; ///< The left solved value
	};
};

#endif
