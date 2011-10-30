#include "stdafx.h"
#include "MathHelper.h"
#include <mpir.h>
#include "Integer.h"
#include "Real.h"
#include "Rational.h"

namespace BigNumbersParser
{
	map<int, int> MathHelper::bitPrecisions;
	map<int, int> MathHelper::decimalPrecisions;
	map<int, Real> MathHelper::realMiscs;
	
	/**
	 * Converts a string to a wstring.
	 * @param str The narrow string.
	 * @return Wide string.
	 */
	wstring MathHelper::AToW(const string& str)
	{
		wstring res;

		struct Widen
		{
			wchar_t operator()(char c)
			{
				return std::use_facet<std::ctype<char> >(std::locale()).widen(c);
			}
		};

		std::transform(str.begin(), str.end(), std::back_inserter(res), Widen());

		return res;
	}

	/**
	 * Converts a string to a wstring.
	 * @param str The narrow string.
	 * @return Wide string.
	 */
	wstring MathHelper::AToW(const char* str)
	{
		return AToW(string(str));
	}

	/**
	 * Converts a wstring to a string.
	 * @param str The wide string.
	 * @return Narrow string.
	 */
	string MathHelper::WToA(const wstring& str)
	{
		string res;

		struct Narrow
		{
			char operator()(wchar_t c)
			{
				return std::use_facet<std::ctype<wchar_t> >(std::locale()).narrow(c, '@');
			}
		};

		std::transform(str.begin(), str.end(), std::back_inserter(res), Narrow());

		return res;
	}

	/**
	 * Converts the decimal precision to the bit precision of the mpfr.
	 * @param precision The decimal precision.
	 * @return Bit precision.
	 */
	int MathHelper::ToBitPrecision(const int precision)
	{
		if (bitPrecisions[precision] != 0)
			return bitPrecisions[precision];
		
		string str = "1";
		for (int i = 0; i < precision; ++i)
			str += "0";
		
		mpz_t number;
		mpz_init(number);
		mpz_set_str(number, str.c_str(), 10);
		int res = mpz_sizeinbase(number, 2);
		bitPrecisions[precision] = res;
		mpz_clear(number);
		
		return res;
	}

	/**
	 * Converts the bit precision to the decimal precision.
	 * @param precision The bit precision.
	 * @return The decimal precision.
	 */
	int MathHelper::ToDecimalPrecision(const int precision)
	{
		if (decimalPrecisions[precision] != 0)
			return decimalPrecisions[precision];
		
		string str = "1";
		for (int i = 0; i < precision; ++i)
			str += "1";
		
		mpz_t number;
		mpz_init(number);
		mpz_set_str(number, str.c_str(), 2);
		int res = mpz_sizeinbase(number, 10);
		decimalPrecisions[precision] = res;
		mpz_clear(number);
		
		return res;
	}

	/**
	 * Gets the calculation error, which presents a number 0.00001, where the number of zeros after the point is the precision.
	 * @param num Number.
	 * @return The misc.
	 */
	template<>
	Real MathHelper::GetMisc(const Real& num)
	{
		map<int, Real>::iterator iter = realMiscs.find(num.GetBitPrecision());

		if (iter == realMiscs.end())
		{
			Real misc = pow(Real(num.GetBitPrecision(), (float)0.1), Real(num.GetBitPrecision(), (int)(num.GetPrecision() - 2)));
			realMiscs[num.GetBitPrecision()] = misc;

			return misc;
		}

		return iter->second;
	}

	/**
	 * Gets a misc of Integer number.
	 * @param num Number.
	 * @return The misc of zero.
	 */
	template<>
	Integer MathHelper::GetMisc(const Integer& num)
	{
		return Integer(0);
	}

	/**
	 * Gets a misc of Rational number.
	 * @param num Number.
	 * @return The misc of zero.
	 */
	template<>
	Rational MathHelper::GetMisc(const Rational& num)
	{
		return Rational(0);
	}
}