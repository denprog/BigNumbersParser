#ifndef ANNOTATION_H
#define ANNOTATION_H

#include "Ast.h"

namespace BigNumbersParser
{
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

		Annotation(string::iterator _first, string::iterator _last) : first(_first), last(_last)
		{
		}

		void UpdatePosition(string::iterator p, ExpressionPosition const& position) const
		{
			UpdatePosition(p, (ExpressionPosition&)position);
		}
		
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
		
		void operator()(Operand& op, string::iterator pos) const
		{
			boost::apply_visitor(OperandVisitor<Number>(this, pos), op);
		}

		void operator()(IdentifierNode<Number>& op, string::iterator pos) const
		{
			UpdatePosition(pos, op);
		}

		void operator()(ExpressionNode<Number>& expr, string::iterator pos) const
		{
			UpdatePosition(pos, expr);
		}

		void operator()(OperationNode<Number>& op, string::iterator pos) const
		{
			UpdatePosition(pos, op);
		}

		void operator()(FunctionCallNode<Number>& op, string::iterator pos) const
		{
			UpdatePosition(pos, op);
		}

		//void operator()(UnaryOperationNode<Number>& op, string::iterator pos) const
		//{
		//}

		template<typename Number>
		struct OperandVisitor
		{
			OperandVisitor(Annotation<Number> const* _annotation, string::iterator _iter) : annotation(_annotation), iter(_iter)
			{
			}
			
			void operator()(OperationNode<Number> const& op) const
			{
				annotation->UpdatePosition(iter, op);
			}

			void operator()(UnaryOperationNode<Number> const& op) const
			{
			}

			void operator()(IdentifierNode<Number> const& op) const
			{
				annotation->UpdatePosition(iter, op);
			}

			void operator()(FunctionCallNode<Number> const& op) const
			{
				annotation->UpdatePosition(iter, op);
			}
			
			void operator()(ExpressionNode<Number> const& op) const
			{
			}

			void operator()(Number const& op) const
			{
				//((Number)op).SetPrecision(10);
			}
			
			typedef void result_type;
			Annotation<Number> const* annotation;
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
