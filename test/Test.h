#ifndef TEST_H
#define TEST_H

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "../source/BigNumbersParser.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace boost;
using namespace boost::unit_test;
using namespace boost::test_tools;
using namespace BigNumbersParser;

extern unit_test::test_suite* init_unit_test_suite(int args, char* argv[]);

#define DEFAULT_TEST_PRECISION 10
#define DEFAULT_RESULT_DELTA 0.00000001

template<class Number>
struct ParserTestCase
{
	//ParserTestCase(wstring& _expression, wstring& _result) : 
	//	resultDelta(MathHelper::ToBitPrecision(DEFAULT_TEST_PRECISION), DEFAULT_RESULT_DELTA)
	//{
	//	expression = _expression;
	//	result = _result;
	//	precision = DEFAULT_TEST_PRECISION;
	//	anyResult = false;
	//	expectedException = -1;
	//}

	ParserTestCase(const char* _expression, const char* expectedResult, int prec) :
		resultDelta(MathHelper::ToBitPrecision(DEFAULT_TEST_PRECISION), (float)DEFAULT_RESULT_DELTA)
	{
		expression = _expression;
		expectedResults.push_back(expectedResult);
		precision = prec;
		anyResult = false;
	}

	ParserTestCase(const char* _expression, ParserExceptionCode id, int pos, int line = 0) :
		resultDelta(MathHelper::ToBitPrecision(DEFAULT_TEST_PRECISION), (float)DEFAULT_RESULT_DELTA), expectedException(id, pos, line)
	{
		expression = _expression;
		precision = DEFAULT_TEST_PRECISION;
		anyResult = false;
	}

	ParserTestCase(const char* _expression, int prec, int _exp, string expectedResult)
	{
		string p("0.");
		for (int i = 0; i < prec - 1; ++i)
			p += "0";
		p += "1";
		resultDelta = Number(p);
		expression = _expression;
		exp = _exp;
		expectedResults.push_back(expectedResult);
		precision = prec;
		anyResult = false;
	}

	//ParserTestCase(wchar_t* _expression, wchar_t* expectedResult) : 
	//	resultDelta(MathHelper::ToBitPrecision(DEFAULT_TEST_PRECISION), DEFAULT_RESULT_DELTA)
	//{
	//	expression = _expression;
	//	expectedResults.push_back(expectedResult);
	//	precision = DEFAULT_TEST_PRECISION;
	//	anyResult = false;
	//	expectedException = -1;
	//}

	//ParserTestCase(wchar_t* _expression, int _expectedException) : 
	//	resultDelta(MathHelper::ToBitPrecision(DEFAULT_TEST_PRECISION), DEFAULT_RESULT_DELTA)
	//{
	//	expression = _expression;
	//	precision = DEFAULT_TEST_PRECISION;
	//	expectedException = _expectedException;
	//	anyResult = false;
	//}

	//ParserTestCase(wchar_t* _expression, wchar_t* expectedResult, bool _anyResult) : 
	//	resultDelta(MathHelper::ToBitPrecision(DEFAULT_TEST_PRECISION), DEFAULT_RESULT_DELTA)
	//{
	//	expression = _expression;
	//	expectedResults.push_back(expectedResult);
	//	precision = DEFAULT_TEST_PRECISION;
	//	anyResult = _anyResult;
	//	expectedException = -1;
	//}

	//ParserTestCase(wchar_t* _expression, wchar_t* expectedResult, bool _anyResult, Number _resultDelta)
	//{
	//	expression = _expression;
	//	expectedResults.push_back(expectedResult);
	//	precision = DEFAULT_TEST_PRECISION;
	//	anyResult = _anyResult;
	//	resultDelta = _resultDelta;
	//	expectedException = -1;
	//}

	//ParserTestCase(wchar_t* _expression, wchar_t* expectedResult, bool _anyResult, double _resultDelta)
	//{
	//	expression = _expression;
	//	expectedResults.push_back(expectedResult);
	//	precision = DEFAULT_TEST_PRECISION;
	//	anyResult = _anyResult;
	//	resultDelta = Number(MathHelper::ToBitPrecision(DEFAULT_TEST_PRECISION), _resultDelta);
	//	expectedException = -1;
	//}

	//ParserTestCase(wchar_t* _expression, wchar_t* expectedResult, double _resultDelta)
	//{
	//	expression = _expression;
	//	expectedResults.push_back(expectedResult);
	//	precision = DEFAULT_TEST_PRECISION;
	//	anyResult = false;
	//	resultDelta = Number(MathHelper::ToBitPrecision(DEFAULT_TEST_PRECISION), _resultDelta);
	//	expectedException = -1;
	//}

	//ParserTestCase(wchar_t* _expression, wchar_t* expectedResult1, wchar_t* expectedResult2) : 
	//	resultDelta(MathHelper::ToBitPrecision(DEFAULT_TEST_PRECISION), DEFAULT_RESULT_DELTA)
	//{
	//	expression = _expression;
	//	expectedResults.push_back(expectedResult1);
	//	expectedResults.push_back(expectedResult2);
	//	precision = DEFAULT_TEST_PRECISION;
	//	anyResult = false;
	//	expectedException = -1;
	//}

	//ParserTestCase(wchar_t* _expression, wchar_t* expectedResult1, wchar_t* expectedResult2, wchar_t* expectedResult3) : 
	//	resultDelta(MathHelper::ToBitPrecision(DEFAULT_TEST_PRECISION), DEFAULT_RESULT_DELTA)
	//{
	//	expression = _expression;
	//	expectedResults.push_back(expectedResult1);
	//	expectedResults.push_back(expectedResult2);
	//	expectedResults.push_back(expectedResult3);
	//	precision = DEFAULT_TEST_PRECISION;
	//	anyResult = false;
	//	expectedException = -1;
	//}

	//ParserTestCase(wchar_t* _expression, wchar_t* expectedResult1, wchar_t* expectedResult2, wchar_t* expectedResult3, 
	//	wchar_t* expectedResult4) : resultDelta(MathHelper::ToBitPrecision(DEFAULT_TEST_PRECISION), DEFAULT_RESULT_DELTA)
	//{
	//	expression = _expression;
	//	expectedResults.push_back(expectedResult1);
	//	expectedResults.push_back(expectedResult2);
	//	expectedResults.push_back(expectedResult3);
	//	expectedResults.push_back(expectedResult4);
	//	precision = DEFAULT_TEST_PRECISION;
	//	anyResult = false;
	//	expectedException = -1;
	//}

	string expression;
	int precision;
	vector<string> expectedResults;
	vector<string> gottenResults;

  Number resultDelta;

	Number leftResult;
	Number rightResult;
	ParserException leftException;
	ParserException rightException;
	ParserException expectedException;
	int exp;
	string expectedResultStr;
	
	bool anyResult;
};

#ifdef _WIN32
class DbgBuf : public std::basic_streambuf<char, char_traits<char> >
{
public:
	virtual int_type overflow(int_type ch/* =  char_traits<char> ::eof */)
	{
		char mas[2];
		mas[0]=ch;
		mas[1]=0;
		OutputDebugStringA(mas);

		return 1;
	}
};
#endif

#endif
