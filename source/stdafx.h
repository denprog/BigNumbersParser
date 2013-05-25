#ifndef STDAFX_H
#define STDAFX_H

//#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_SPIRIT_DEBUG

//#include <boost/spirit/include/phoenix.hpp>
//#include <boost/spirit/include/qi.hpp>
//#include <boost/spirit/include/qi_int.hpp>
//#include <boost/spirit/include/qi_uint.hpp>
//#include <boost/spirit/include/qi_string.hpp>
//#include <boost/spirit/include/qi_attr.hpp>
//#include <boost/spirit/include/classic_symbols.hpp>
//#include <boost/spirit/include/classic_utility.hpp>
//#include <boost/variant/recursive_variant.hpp>
//#include <boost/variant/apply_visitor.hpp>
//#include <boost/fusion/container/vector.hpp>
//#include <boost/fusion/include/vector.hpp>
//#include <boost/fusion/include/adapt_struct.hpp>
//#include <boost/function.hpp>

#if defined(_MSC_VER)
# pragma warning(disable: 4345)
#endif

//#include <boost/function.hpp>
//#include <boost/shared_ptr.hpp>
//#include <boost/spirit/include/phoenix_core.hpp>
//#include <boost/spirit/include/phoenix_function.hpp>
//#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi_no_case.hpp>
#include <boost/foreach.hpp>
#include <boost/any.hpp>
#include <boost/function.hpp>

#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <stack>
#include <deque>
#include <list>
#include <map>
//#include <boost/variant.hpp>

#include "mpir.h"
#include "mpfr.h"

namespace spirit = boost::spirit;
namespace qi = spirit::qi;

#endif
