#ifndef PARSERTEST_H
#define PARSERTEST_H

#include "Test.h"
#include "../source/Integer.h"
#include "../source/Real.h"
#include "../source/Rational.h"

template<typename Number>
class ParserTest
{
public:
	ParserTest()
	{
		parser = new Parser<Number>(10);
	}
	
	~ParserTest()
	{
		delete parser;
	}
	
public:
	void RunTests()
	{
		FillTestTable();

		for (int i = 0; i < (int)testTable.size(); ++i)
		{
			GetResult(testTable[i]);
			BOOST_CHECK(CompareResults(testTable[i]));
		}
	}
	
	void GetResult(ParserTestCase<Number>& testCase)
	{
		try
		{
			Number leftRes = parser->Parse(string(testCase.expression), testCase.precision);
			testCase.leftResult = leftRes;
		}
		catch (ParserException e)
		{
			testCase.leftException = e;
		}

		if (testCase.expectedResults.size() > 0)
		{
			try
			{
				Number rightRes = parser->Parse(string(testCase.expectedResults[0]), testCase.precision);
				testCase.rightResult = rightRes;
			}
			catch (ParserException e)
			{
				testCase.rightException = e;
			}
		}
	}
	
	boost::test_tools::predicate_result CompareResults(const ParserTestCase<Number>& testCase);

private:
	void FillTestTable();
	
	void AddTestCase(const char* leftExpression, const char* rightExpression, int precision = -1)
	{
		testTable.push_back(ParserTestCase<Number>(leftExpression, rightExpression, precision));
	}

	void AddTestCase(const char* leftExpression, ParserExceptionCode expectedExceptionId, int pos, int line = 0)
	{
		testTable.push_back(ParserTestCase<Number>(leftExpression, expectedExceptionId, pos, line));
	}

	void AddTestCase(const char* leftExpression, int precision, int exp, const char* expectedResultStr)
	{
		testTable.push_back(ParserTestCase<Number>(leftExpression, precision, exp, string(expectedResultStr)));
	}

private:
	Parser<Number>* parser;
	vector< ParserTestCase<Number> > testTable;
};

#endif
