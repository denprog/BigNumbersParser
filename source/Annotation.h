#ifndef ANNOTATION_H
#define ANNOTATION_H

#include "Ast.h"

namespace BigNumbersParser
{
	/**
	 * Annotation for nodes. Used in purposes of searching a node by a text position.
	 */
	template<typename Number>
	struct Annotation
	{
		typedef boost::variant<
			Number, 
			boost::recursive_wrapper<IdentifierNode<Number> >, 
			boost::recursive_wrapper<UnaryOperationNode<Number> >, 
			boost::recursive_wrapper<OperationNode<Number> >, 
			boost::recursive_wrapper<FunctionCallNode<Number> >, 
			boost::recursive_wrapper<ExpressionNode<Number> > >
			Operand;

		/**
		 * Constructor.
		 * @param _first The beginning of the expression.
		 * @param _last The end of the expression.
		 */
		Annotation(string::iterator _first, string::iterator _last) : first(_first), last(_last)
		{
		}

		/**
		 * Updates the position in the expression.
		 * @param p	The iterator position.
		 * @param [in,out] position The expression position.
		 */
		void UpdatePosition(string::iterator p, ExpressionPosition const& position) const
		{
			UpdatePosition(p, (ExpressionPosition&)position);
		}
		
		/**
		 * Updates the position in the expression.
		 * @param p	The iterator position.
		 * @param [in,out] position The expression position.
		 */
		void UpdatePosition(string::iterator p, ExpressionPosition& position) const
		{
			int i = 0, j = 0;
			string::iterator k = first;
			
			while (k != p)
			{
				char ch = *k;
				if (ch == '\r')
				{
					++k;
					if (ch == '\n')
						++k;
					++j;
				}
				
				++k;
				++i;
			}
			
			position.pos = i;
			position.line = j;
		}
		
		/**
		 * Updates the position in the expression.
		 * @param op The node.
		 * @param [in] position The iterator position.
		 */
		void operator()(Operand& op, string::iterator pos) const
		{
			boost::apply_visitor(OperandVisitor<Number>(this, pos), op);
		}

		/**
		 * Updates the position in the expression.
		 * @param op The node.
		 * @param [in] position The iterator position.
		 */
		void operator()(IdentifierNode<Number>& op, string::iterator pos) const
		{
			UpdatePosition(pos, op);
		}

		/**
		 * Updates the position in the expression.
		 * @param op The node.
		 * @param [in] position The iterator position.
		 */
		void operator()(ExpressionNode<Number>& expr, string::iterator pos) const
		{
			UpdatePosition(pos, expr);
		}

		/**
		 * Updates the position in the expression.
		 * @param op The node.
		 * @param [in] position The iterator position.
		 */
		void operator()(OperationNode<Number>& op, string::iterator pos) const
		{
			UpdatePosition(pos, op);
		}

		/**
		 * Updates the position in the expression.
		 * @param op The node.
		 * @param [in] position The iterator position.
		 */
		void operator()(FunctionCallNode<Number>& op, string::iterator pos) const
		{
			UpdatePosition(pos, op);
		}

		//void operator()(UnaryOperationNode<Number>& op, string::iterator pos) const
		//{
		//}

		/**
		 * Operand visitor.
		 */
		template<typename Num>
		struct OperandVisitor
		{
			/**
			 * Constructor.
			 * @param _annotation The annotation.
			 * @param _iter The iterator position.
			 */
			OperandVisitor(Annotation<Num> const* _annotation, string::iterator _iter) : annotation(_annotation), iter(_iter)
			{
			}
			
			/**
			 * The visitor's functor for OperationNode.
			 */
			void operator()(OperationNode<Num> const& op) const
			{
				annotation->UpdatePosition(iter, op);
			}

			/**
			 * The visitor's functor for UnaryOperationNode.
			 */
			void operator()(UnaryOperationNode<Num> const& op) const
			{
			}

			/**
			 * The visitor's functor for IdentifierNode.
			 */
			void operator()(IdentifierNode<Num> const& op) const
			{
				annotation->UpdatePosition(iter, op);
			}

			/**
			 * The visitor's functor for FunctionCallNode.
			 */
			void operator()(FunctionCallNode<Num> const& op) const
			{
				annotation->UpdatePosition(iter, op);
			}
			
			/**
			 * The visitor's functor for ExpressionNode.
			 */
			void operator()(ExpressionNode<Num> const& op) const
			{
			}

			/**
			 * The visitor's functor for Number.
			 */
			void operator()(Num const& op) const
			{
				//((Number)op).SetPrecision(10);
			}
			
			typedef void result_type;
			Annotation<Num> const* annotation;
			string::iterator iter;
		};

		template<typename, typename>
		struct result
		{
			typedef void type;
		};

		//typedef void result;
		string::iterator first;
		string::iterator last;
	};
}

#endif
