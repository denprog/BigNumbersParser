#ifndef PARSEREXCEPTION_H
#define PARSEREXCEPTION_H

namespace BigNumbersParser
{
	enum ParserExceptionCode
	{
		None = -1, 
		SyntaxError = 1, 
		WrongArgumentsCount = 2, 
		UnknownIdentifier = 3, 
		ExpressionExpected = 4,
		DivisionByZero = 100, 
		Overflow = 101, 
		ArgumentIsOver = 102, 
		ConversionDoesNotFit = 103
	};
	
	struct ParserException
	{
		ParserException()
		{
			id = None;
			pos = -1;
			line = -1;
		}
		
		ParserException(ParserExceptionCode _id, int _pos, int _line)
		{
			id = _id;
			pos = _pos;
			line = _line;
		}
		
		friend bool operator==(const ParserException& e1, const ParserException& e2)
		{
			return e1.id == e2.id && e1.pos == e2.pos && e1.line == e2.line;
		}
		
		ParserExceptionCode id;
		int pos;
		int line;
	};
	
	struct SyntaxException : public ParserException
	{
		SyntaxException(ParserExceptionCode _id, int _pos = -1, int _line = -1) : ParserException(_id, _pos, _line)
		{
		}
	};
	
	struct MathException : public ParserException
	{
		MathException(ParserExceptionCode _id) : ParserException(_id, -1, -1)
		{
		}

		MathException(ParserExceptionCode _id, int _pos, int _line) : ParserException(_id, _pos, _line)
		{
		}
	};
}

#endif
