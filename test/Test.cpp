#include "Test.h"
#include "ParserTest.h"
#include <boost/shared_ptr.hpp>

#ifdef _WIN32
DbgBuf db;
ostream os(&db);
#endif

unit_test::test_suite* init_unit_test_suite(int args, char* argv[])
{
	using BigNumbersParser::Integer;
	
#ifdef _WIN32
	boost::unit_test::unit_test_log.set_stream(os);
	boost::unit_test::unit_test_log.set_threshold_level(log_messages);
#endif

	BOOST_TEST_SUITE("parserTest");
	
	boost::shared_ptr<ParserTest<Integer> > integerTest(new ParserTest<Integer>());
	framework::master_test_suite().add(BOOST_CLASS_TEST_CASE(&ParserTest<Integer>::RunTests, integerTest));

	boost::shared_ptr<ParserTest<Real> > realTest(new ParserTest<Real>());
	framework::master_test_suite().add(BOOST_CLASS_TEST_CASE(&ParserTest<Real>::RunTests, realTest));

	boost::shared_ptr<ParserTest<Rational> > rationalTest(new ParserTest<Rational>());
	framework::master_test_suite().add(BOOST_CLASS_TEST_CASE(&ParserTest<Rational>::RunTests, rationalTest));
	
	return 0;
}
