#include "stdafx.h"
#include "BigNumbersParser.h"

namespace BigNumbersParser
{
  Integer pow(const Integer& num1, const Integer& num2);

  Real pow(const Real& num1, const Real& num2);

  Real sin(const Real& num, AngleMeasure angleMeasure);
  Real cos(const Real& num, AngleMeasure angleMeasure);
  Real tg(const Real& num, AngleMeasure angleMeasure);
  Real ctg(const Real& num, AngleMeasure angleMeasure);
  Real sec(const Real& num, AngleMeasure angleMeasure);
  Real cosec(const Real& num, AngleMeasure angleMeasure);
  Real arcsin(const Real& num, AngleMeasure angleMeasure);
  Real arccos(const Real& num, AngleMeasure angleMeasure);
  Real arctg(const Real& num, AngleMeasure angleMeasure);
  Real arcctg(const Real& num, AngleMeasure angleMeasure);
  Real arcsec(const Real& num, AngleMeasure angleMeasure);
  Real arccosec(const Real& num, AngleMeasure angleMeasure);
  Real sh(const Real& num, AngleMeasure angleMeasure);
  Real ch(const Real& num, AngleMeasure angleMeasure);
  Real th(const Real& num, AngleMeasure angleMeasure);
  Real cth(const Real& num, AngleMeasure angleMeasure);
  Real sch(const Real& num, AngleMeasure angleMeasure);
  Real csch(const Real& num, AngleMeasure angleMeasure);
  Real arsh(const Real& num, AngleMeasure angleMeasure);
  Real arch(const Real& num, AngleMeasure angleMeasure);
  Real arth(const Real& num, AngleMeasure angleMeasure);
  Real arcth(const Real& num, AngleMeasure angleMeasure);
  Real arsch(const Real& num, AngleMeasure angleMeasure);
  Real arcsch(const Real& num, AngleMeasure angleMeasure);

  Real pi(const int precision);
  Real exp(const int precision);

  Real exp(const Real& num);

  Real ln(const Real& num);
  Real lg(const Real& num);
  Real log(const Real& num1, const Real& num2);
  Real sqrt(const Real& num);
  Real root(const Real& num1, const Real& num2);

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

	template<>
	Integer Parser<Integer>::Parse(string expression, const int precision)
	{
		if (expression.empty() | expression == ";")
			throw SyntaxException(ExpressionExpected, 0, 0);
		
		Integer res;
		string::iterator iter = expression.begin();
		string::iterator end = expression.end();
		qi::space_type space;

		Script<Integer> script(expression);
		ScriptNode<Integer> scriptNode;

		phrase_parse(iter, end, script, space, scriptNode);
		res = solver(scriptNode, precision);

		return res;
	}

	template<>
	Real Parser<Real>::Parse(string expression, const int precision)
	{
		if (expression.empty() | expression == ";")
			throw SyntaxException(ExpressionExpected, 0, 0);
		
		Real res;
		string::iterator iter = expression.begin();
		string::iterator end = expression.end();
		qi::space_type space;

		Script<Real> script(expression);
		ScriptNode<Real> scriptNode;

		phrase_parse(iter, end, script, space, scriptNode);
		res = solver(scriptNode, precision);

		return res;
	}

	template<>
	Rational Parser<Rational>::Parse(string expression, const int precision)
	{
		if (expression.empty() | expression == ";")
			throw SyntaxException(ExpressionExpected, 0, 0);
		
		Rational res;
		string::iterator iter = expression.begin();
		string::iterator end = expression.end();
		qi::space_type space;

		Script<Rational> script(expression);
		ScriptNode<Rational> scriptNode;

		phrase_parse(iter, end, script, space, scriptNode);
		res = solver(scriptNode, precision);

		return res;
	}
};
