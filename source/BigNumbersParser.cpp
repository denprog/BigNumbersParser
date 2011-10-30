#include "stdafx.h"
#include "BigNumbersParser.h"

namespace BigNumbersParser
{
	/**
	 * Constructor.
	 * @tparam BigNumbersParser::Integer Integer type of the big numbers parser.
	 * @param precision The precision.
	 */
	template<>
	Parser<BigNumbersParser::Integer>::Parser(const int precision) : solver(precision)
	{
		IntegerBinaryFunc binaryFunc = &pow;
		solver.AddBuildinFunction("pow", binaryFunc);
	}

	/**
	 * Constructor.
	 * @tparam BigNumbersParser::Real Real type of the big numbers parser.
	 * @param precision The precision.
	 */
	template<>
	Parser<BigNumbersParser::Real>::Parser(const int precision) : solver(precision)
	{
		RealPrecisionVariable var;
		var = &pi;
		solver.AddBuildinVariable("pi", var);
		var = &exp;
		solver.AddBuildinVariable("e", var);
		
		RealUnaryFunc unaryFunc;
		unaryFunc = &exp;
		solver.AddBuildinFunction("exp", unaryFunc);
		unaryFunc = &ln;
		solver.AddBuildinFunction("ln", unaryFunc);
		unaryFunc = &lg;
		solver.AddBuildinFunction("lg", unaryFunc);
		unaryFunc = &sqrt;
		solver.AddBuildinFunction("sqrt", unaryFunc);
		
		RealTrigonometricFunc trigonometricFunc;
		trigonometricFunc = &sin;
		solver.AddBuildinFunction("sin", trigonometricFunc);
		trigonometricFunc = &cos;
		solver.AddBuildinFunction("cos", trigonometricFunc);
		trigonometricFunc = &tg;
		solver.AddBuildinFunction("tg", trigonometricFunc);
		trigonometricFunc = &ctg;
		solver.AddBuildinFunction("ctg", trigonometricFunc);
		trigonometricFunc = &sec;
		solver.AddBuildinFunction("sec", trigonometricFunc);
		trigonometricFunc = &cosec;
		solver.AddBuildinFunction("cosec", trigonometricFunc);
		trigonometricFunc = &arcsin;
		solver.AddBuildinFunction("arcsin", trigonometricFunc);
		trigonometricFunc = &arccos;
		solver.AddBuildinFunction("arccos", trigonometricFunc);
		trigonometricFunc = &arctg;
		solver.AddBuildinFunction("arctg", trigonometricFunc);
		trigonometricFunc = &arcctg;
		solver.AddBuildinFunction("arcctg", trigonometricFunc);
		trigonometricFunc = &arcsec;
		solver.AddBuildinFunction("arcsec", trigonometricFunc);
		trigonometricFunc = &arccosec;
		solver.AddBuildinFunction("arccosec", trigonometricFunc);
		trigonometricFunc = &sh;
		solver.AddBuildinFunction("sh", trigonometricFunc);
		trigonometricFunc = &ch;
		solver.AddBuildinFunction("ch", trigonometricFunc);
		trigonometricFunc = &th;
		solver.AddBuildinFunction("th", trigonometricFunc);
		trigonometricFunc = &cth;
		solver.AddBuildinFunction("cth", trigonometricFunc);
		trigonometricFunc = &sch;
		solver.AddBuildinFunction("sch", trigonometricFunc);
		trigonometricFunc = &csch;
		solver.AddBuildinFunction("csch", trigonometricFunc);
		trigonometricFunc = &arsh;
		solver.AddBuildinFunction("arsh", trigonometricFunc);
		trigonometricFunc = &arch;
		solver.AddBuildinFunction("arch", trigonometricFunc);
		trigonometricFunc = &arth;
		solver.AddBuildinFunction("arth", trigonometricFunc);
		trigonometricFunc = &arcth;
		solver.AddBuildinFunction("arcth", trigonometricFunc);
		trigonometricFunc = &arsch;
		solver.AddBuildinFunction("arsch", trigonometricFunc);
		trigonometricFunc = &arcsch;
		solver.AddBuildinFunction("arcsch", trigonometricFunc);
	
		RealBinaryFunc binaryFunc = &pow;
		solver.AddBuildinFunction("pow", binaryFunc);
		binaryFunc = &log;
		solver.AddBuildinFunction("log", binaryFunc);
		binaryFunc = &root;
		solver.AddBuildinFunction("root", binaryFunc);
	}

	/**
	 * Constructor.
	 * @tparam BigNumbersParser::Rational Rational type of the big numbers parser.
	 * @param precision The precision.
	 */
	template<>
	Parser<BigNumbersParser::Rational>::Parser(const int precision) : solver(precision)
	{
	}
};
