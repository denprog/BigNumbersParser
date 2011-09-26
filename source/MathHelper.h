#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <string>
#include <map>
#include <algorithm>
#include <mpfr.h>

using namespace std;

#define DEFAULT_BASE 10
#define DEFAULT_INCREASE_PRECISION 5
#define DEFAULT_RND MPFR_RNDN
#define DEFAULT_INCREASE_PRECISION 5

#ifdef _DEBUG
#define TRACE_OUTPUT
#endif

enum AngleMeasure
{
	NONE_ANGLE_MEASURE = -1, 
	RADIAN = 0, 
	DEGREE, 
	GRAD
};

namespace BigNumbersParser
{
	class Real;
	
	class MathHelper
	{
	public:
		static wstring AToW(const string& str);
		static wstring AToW(const char* str);
		static string WToA(const wstring& str);
		
		static int ToBitPrecision(const int precision);
		static int ToDecimalPrecision(const int precision);

		template<class TNumber>
		static TNumber GetMisc(const TNumber& num);
		
	private:
		static map<int, int> bitPrecisions;
		static map<int, int> decimalPrecisions;
		static map<int, Real> realMiscs;
	};
}

#endif
