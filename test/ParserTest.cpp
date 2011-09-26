#include "ParserTest.h"

template<>
boost::test_tools::predicate_result ParserTest<BigNumbersParser::Integer>::CompareResults(const ParserTestCase<BigNumbersParser::Integer>& testCase)
{
	using BigNumbersParser::Integer;
	char buf1[200], buf2[200];
	
	Integer result = testCase.leftResult;
	Integer expected = testCase.rightResult;

	if (testCase.expectedException.id != None)
	{
		if (testCase.expectedException == testCase.leftException)	
			return true;

		boost::test_tools::predicate_result res(false);

		string resultStr = result.ToString();
		string expectedStr = expected.ToString();

		sprintf(buf1, "Result parser exception id = %d", testCase.expectedException.id);
		sprintf(buf2, "Expected parser exception id = %d", testCase.leftException.id);
		res.message() << testCase.expression.c_str() << " != " << buf1 << ":" << buf2;

		return res;
	}

	if (result != expected)
	{
		boost::test_tools::predicate_result res(false);

		string resultStr;
		res.message() << "\n";

		resultStr += testCase.expectedResults[0];
		
		if (testCase.expectedException.id == -1)
		{
			if (testCase.leftException.id != -1)
			{
				sprintf(buf1, "Left parser exception id = %d", testCase.leftException.id);
				res.message() << testCase.expression.c_str() << " != " << 
					resultStr.c_str() << " : " << expected.ToString().c_str() << " != " << buf1;
			}
			else
			{
				res.message() << testCase.expression.c_str() << " != " << 
					resultStr.c_str() << " : " << result.ToString().c_str() << " != " << 
					expected.ToString().c_str();
			}
		}

		if (testCase.rightException.id != -1)
		{
			sprintf(buf1, "Right parser exception id = %d", testCase.rightException.id);
			res.message() << testCase.expression.c_str() << " != " << 
				resultStr.c_str() << " : " << result.ToString().c_str() << " != " << buf1;

			return res;
		}

		if (testCase.expectedException.id != -1)
		{
			sprintf(buf1, "Expected parser exception id = %d", testCase.expectedException.id);
			res.message() << testCase.expression.c_str() << "!= " << buf1;
		}

		return res;
	}

	return true;
}

template<>
boost::test_tools::predicate_result ParserTest<BigNumbersParser::Real>::CompareResults(const ParserTestCase<BigNumbersParser::Real>& testCase)
{
	char buf1[200], buf2[200];
	
	Real result = testCase.leftResult;

	if (!testCase.expectedResultStr.empty())
	{
		boost::test_tools::predicate_result res(false);
		
		if (testCase.leftException.id != None)
		{
			sprintf(buf1, "Result exception id = %d", testCase.leftException.id);
			res.message() << testCase.expression.c_str() << " != " << 
				testCase.expectedResultStr.c_str() << " : " << buf1;
			return res;
		}
		
		string r = result.ToString(testCase.exp, testCase.precision);
		if (r == testCase.expectedResultStr)
			return true;
		
		res.message() << testCase.expression.c_str() << " != " << 
			testCase.expectedResultStr.c_str() << " : " << r.c_str();
		
		return res;
	}

	Real expected = testCase.rightResult;

	if (testCase.expectedException.id != None)
	{
		if (testCase.expectedException == testCase.leftException)	
			return true;

		boost::test_tools::predicate_result res(false);

		string resultStr = result.ToString();
		string expectedStr = expected.ToString();

		sprintf(buf1, "Result exception id = %d", testCase.expectedException.id);
		sprintf(buf2, "Expected exception id = %d", testCase.leftException.id);
		res.message() << testCase.expression.c_str() << " != " << buf2 << " : " << buf1 << " != " << buf2;

		return res;
	}

	if (result != expected)
	{
		if (abs(result - expected) <= abs(testCase.resultDelta))
			return true;

		boost::test_tools::predicate_result res(false);

		string resultStr;
		res.message() << "\n";

		resultStr += testCase.expectedResults[0];
		
		if (testCase.expectedException.id == -1)
		{
			if (testCase.leftException.id != -1)
			{
				sprintf(buf1, "Left parser exception id = %d", testCase.leftException.id);
				res.message() << testCase.expression.c_str() << " != " << 
					resultStr.c_str() << " : " << expected.ToString().c_str() << " != " << buf1;
			}
			else
			{
				res.message() << testCase.expression.c_str() << " != " << 
					resultStr.c_str() << " : " << result.ToString().c_str() << " != " << 
					expected.ToString().c_str();
			}
		}

		if (testCase.rightException.id != -1)
		{
			sprintf(buf1, "Right parser exception id = %d", testCase.rightException.id);
			res.message() << testCase.expression.c_str() << " != " << 
				resultStr.c_str() << " : " << result.ToString().c_str() << " != " << buf1;

			return res;
		}

		if (testCase.expectedException.id != -1)
		{
			sprintf(buf1, "Expected parser exception id = %d", testCase.expectedException.id);
			res.message() << testCase.expression.c_str() << " != " << buf1;
		}

		return res;
	}

	return true;
}

template<>
boost::test_tools::predicate_result ParserTest<Rational>::CompareResults(const ParserTestCase<Rational>& testCase)
{
	char buf1[200], buf2[200];
	
	Rational result = testCase.leftResult;
	Rational expected = testCase.rightResult;

	if (testCase.expectedException.id != None)
	{
		if (testCase.expectedException == testCase.leftException)	
			return true;

		boost::test_tools::predicate_result res(false);

		string resultStr = result.ToString();
		string expectedStr = expected.ToString();

		sprintf(buf1, "Result parser exception id = %d", testCase.expectedException.id);
		sprintf(buf2, "Expected parser exception id = %d", testCase.leftException.id);
		res.message() << testCase.expression.c_str() << " != " << buf1 << ":" << buf2;

		return res;
	}

	if (result != expected)
	{
		boost::test_tools::predicate_result res(false);

		string resultStr;
		res.message() << "\n";

		resultStr += testCase.expectedResults[0];
		
		if (testCase.expectedException.id == -1)
		{
			if (testCase.leftException.id != -1)
			{
				sprintf(buf1, "Left parser exception id = %d", testCase.leftException.id);
				res.message() << testCase.expression.c_str() << " != " << 
					resultStr.c_str() << " : " << expected.ToString().c_str() << " != " << buf1;
			}
			else
			{
				res.message() << testCase.expression.c_str() << " != " << 
					resultStr.c_str() << " : " << result.ToString().c_str() << " != " << 
					expected.ToString().c_str();
			}
		}

		if (testCase.rightException.id != -1)
		{
			sprintf(buf1, "Right parser exception id = %d", testCase.rightException.id);
			res.message() << testCase.expression.c_str() << " != " << 
				resultStr.c_str() << " : " << result.ToString().c_str() << " != " << buf1;

			return res;
		}

		if (testCase.expectedException.id == -1)
		{
			res.message() << testCase.expression.c_str() << " != " << 
				resultStr.c_str() << " : " << result.ToString().c_str() << " != " << 
				expected.ToString().c_str();
		}
		else
		{
			sprintf(buf1, "Expected parser exception id = %d", testCase.expectedException.id);
			res.message() << testCase.expression.c_str() << "!= " << buf1;
		}

		return res;
	}

	return true;
}

template<>
void ParserTest<BigNumbersParser::Integer>::FillTestTable()
{
	using BigNumbersParser::Integer;

	//arithmetic
	AddTestCase("123;", "123;");
	AddTestCase("123456", "123456");
	AddTestCase("5555555555555555555555555555555555555555", 
		"5555555555555555555555555555555555555555");
	AddTestCase("5555555555555555555555555555555555555555+3333333333333333333333333333333333333333", 
		"8888888888888888888888888888888888888888");
	
	AddTestCase("2+3;", "5;");
	AddTestCase("12+34+56+78+90", "270");
	AddTestCase("123-45", "78");
	AddTestCase("45-123", "-78");
	AddTestCase("-3;", "-3;");
	
	AddTestCase("12-3", "9");
	
	AddTestCase("2*3", "6");

	AddTestCase("10/2", "5");

	AddTestCase("2+3*5", "17");
	AddTestCase("25-5+4*5/2;", "30;");

	AddTestCase("(5+3)*2;", "16;");
	AddTestCase("5+(3*2);", "11;");
	AddTestCase("(5+3)*(20-10/2);", "120;");
	
	AddTestCase("12+34+56+78+90", "270");
	AddTestCase("12*34*56*78*90", "160392960");

	//variables
	AddTestCase("m=5+4;m+6;", "15");
	AddTestCase("m=5+4;m=1;m+6;", "7");
	AddTestCase("s=1;p=5;m=s+p;m+6;", "12");
	AddTestCase("s=1;p=5;m=2+s;5+m+6;", "14");
	AddTestCase("s=1;p=5;m=2+s;5+m+p+6;", "19");
	AddTestCase("s=1;p=5;m=2+p;5+s+m+6;", "19");

	//functions
	AddTestCase("pow(2,3)", "8");
	AddTestCase("pow(2+3,4)", "625");
	AddTestCase("pow(5-7,4+2)", "64");
	AddTestCase("pow(pow(5 - 7, 2), 4 + 2)", "4096");
	
	AddTestCase(
		"func(a)=\
		{\
			return a * 3;\
		};\
		func(5);", 
		"15;");
	AddTestCase(
		"func(a,b)=\
		{\
			return a * b;\
		};\
		func(5,6);", 
		"30;");
	AddTestCase(
		"f1(a,b)=\
		{\
			return a * b;\
		};\
		f2(a)=\
		{\
			return a * 2;\
		};\
		x=f1(5,6);\
		y=f2(20);\
		x+y;", 
		"70;");
	AddTestCase(
		"f1(a,b)=\
		{\
			return a - b;\
		};\
		f2(arg1,arg2,arg3)=\
		{\
			return arg1 * f1(arg2,arg3);\
		};\
		f2(5,6,7);", 
		"-5;");

	//errors
	AddTestCase("2+;", SyntaxError, 2);
	AddTestCase("1/0;", DivisionByZero, 1);
}

template<>
void ParserTest<Real>::FillTestTable()
{
	//arithmetic
	AddTestCase("123;", "123;");
	AddTestCase("123.;", "123;");
	AddTestCase("1234567890123456789.1234567890123456789012345678901234567890;", 
		"1234567890123456789.1234567890123456789012345678901234567890;");
	AddTestCase("123456", "123456");
	AddTestCase("5555555555555555555555555555555555555555", 
		"5555555555555555555555555555555555555555");
	//AddTestCase("5555555555555555555555555555555555555555+3333333333333333333333333333333333333333", 
	//	"8888888888888888888888888888888888888888");
	
	AddTestCase("2+3;", "5;");
	AddTestCase("2.+3;", "5;");
	AddTestCase("2+3.;", "5;");
	AddTestCase("2.3+3;", "5.3;");
	AddTestCase("2+3.4;", "5.4;");
	AddTestCase("12+34+56+78+90", "270");
	AddTestCase("123-45", "78");
	AddTestCase("45-123", "-78");
	AddTestCase("-3;", "-3;");
	AddTestCase("5.555555555555555555555555555555555555555+3.333333333333333333333333333333333333333", 
		"8.888888888888888888888888888888888888888");
	
	AddTestCase("12-3", "9");
	
	AddTestCase("2*3", "6");

	AddTestCase("10/2", "5");

	AddTestCase("2+3*5", "17");
	AddTestCase("25-5+4*5/2;", "30;");

	AddTestCase("(5.6+3.567)*2.345;", "21.496615;", 10);
	AddTestCase("5.3435+(3.653*2);", "12.6495;", 10);
	AddTestCase("(5.12+3.5632)*(20.345-10.234/2.5435);", "141.7220712892;", 10);

	AddTestCase("5.12*(20.345-10.234/2.5435);", 10, 3, "83.5656215451E+0");
	AddTestCase("3.456789/5.345677657;", 30, 3, "0.646651223998409524751484655409E+0");
	AddTestCase("(5.12+3.5632)*(20.345-10.234/2.5435);", 10, 3, "141.7220712892E+0");

	//variables
	AddTestCase("m=5+4;m+6;", "15");
	AddTestCase("m=5+4;m=1;m+6;", "7");
	AddTestCase("s=1;p=5;m=s+p;m+6;", "12");
	AddTestCase("s=1;p=5;m=2+s;5+m+6;", "14");
	AddTestCase("s=1;p=5;m=2+s;5+m+p+6;", "19");
	AddTestCase("s=1;p=5;m=2+p;5+s+m+6;", "19");
	AddTestCase("pi;", 10, 3, "3.1415926536E+0");
	
	//functions
	AddTestCase("pow(2,3)", "8");
	AddTestCase("pow(2.3,3.5);", 10, 3, "18.4521691056E+0");
	AddTestCase("pow(2+3,4)", "625");
	AddTestCase("pow(5-7,4+2)", "64");
	AddTestCase("pow(pow(5 - 7, 2), 4 + 2)", "4096");
	AddTestCase("pow(pow(5.34 - 7.53, 2), 4.256 + 2)", 10, 3, "1.8181795339E+4");
	
	AddTestCase("sqrt(2)", 10, 3, "1.4142135624E+0");
	AddTestCase("sqrt(10.231)", 10, 3, "3.1985934409E+0");
	
	AddTestCase("root(2,3)", 10, 3, "1.2599210499E+0");
	AddTestCase("root(27,3)", 10, 3, "3.E+0");

	AddTestCase(
		"func(a)=\
		{\
			return a * 3;\
		};\
		func(5);", 
		"15;");
	AddTestCase(
		"func(a,b)=\
		{\
			return a * b;\
		};\
		func(5,6);", 
		"30;");
	AddTestCase(
		"f1(a,b)=\
		{\
			return a * b;\
		};\
		f2(a)=\
		{\
			return a * 2;\
		};\
		x=f1(5,6);\
		y=f2(20);\
		x+y;", 
		"70;");
	AddTestCase(
		"f1(a,b)=\
		{\
			return a - b;\
		};\
		f2(arg1,arg2,arg3)=\
		{\
			return arg1 * f1(arg2,arg3);\
		};\
		f2(5,6,7);", 
		"-5;");

	//errors
	AddTestCase("po(2,3);", UnknownIdentifier, 0);
	AddTestCase("pow(2);", WrongArgumentCount, 0);
	AddTestCase("2+;", SyntaxError, 2);
	AddTestCase("1/0;", DivisionByZero, 1);
}

template<>
void ParserTest<Rational>::FillTestTable()
{
	AddTestCase("123;", "123;");
	AddTestCase("1/2;", "1/2;");
	AddTestCase("1/2 + 3/4;", "5/4;");
	AddTestCase("5/2 - 1/4;", "9/4;");
}
