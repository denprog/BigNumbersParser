#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include "ParserException.h"

namespace BigNumbersParser
{
	template<typename Exception>
	struct ErrorHandler
	{
		ErrorHandler(string::iterator _first, string::iterator _last, ParserExceptionCode _id) : first(_first), last(_last)
		{
			//pos = -1;
			//line = -1;
			id = _id;
		}
		
		void operator()(string::iterator p) const
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
			
			//pos = i;
			//line = j;
			
			throw Exception(id, i, j);
		}

		template<typename>
		struct result
		{
			typedef void type;
		};

		typedef void result_type;
		string::iterator first;
		string::iterator last;
		//mutable int pos;
		//mutable int line;
		ParserExceptionCode id;
	};
}

#endif
