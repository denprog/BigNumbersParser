#include "stdafx.h"
#include "Rational.h"

namespace BigNumbersParser
{
	Rational::Rational()
	{
		mpq_init(number);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	Rational::Rational(const Rational& source)
	{
		mpq_init(number);
		mpq_set(number, source.number);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	Rational::Rational(const int num)
	{
		mpq_init(number);
		mpq_set_si(number, num, 1);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	Rational::Rational(const int precision, const double num)
	{
		mpq_init(number);
		mpq_set_d(number, num);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	Rational::Rational(const int precision, const int num)
	{
		mpq_init(number);
		mpq_set_si(number, num, 1);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	Rational::Rational(const string& num)
	{
		mpq_init(number);
		mpq_set_str(number, num.c_str(), 10);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	Rational::~Rational()
	{
		mpq_clear(number);
	}
		
	Rational& Rational::operator=(const Rational& source)
	{
		if (this == &source)
			return *this;

		mpq_clear(number);
		mpq_init(number);

		mpq_set(number, source.number);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif

		return *this;
	}

	Rational& Rational::operator=(const string& source)
	{
		if (source.find(L'.') != -1)
		{
			string intPart, fractPart;
			int i = 0;

			while (i < (int)source.length() && source[i] != '.')
			{
				intPart += source[i];
				++i;
			}

			++i;

			while (i < (int)source.length())
			{
				fractPart += source[i];
				++i;
			}

			if (fractPart != "")
			{
				int n = fractPart.length();
				string t("1");

				for (int j = 0; j < n; ++j)
					t += '0';

				*this = Rational(fractPart) / Rational(t) + Rational(intPart);

				return *this;
			}
		}

		mpq_set_str(number, source.c_str(), DEFAULT_BASE);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif

		return *this;
	}

	Rational Rational::operator+()
	{
		Rational res(*this);

		return res;
	}

	Rational Rational::operator-()
	{
		Rational res(*this);

		mpq_neg(res.number, number);

		return res;
	}

	Rational operator+(const Rational& num1, const Rational& num2)
	{
		Rational res;

		mpq_add(res.number, num1.number, num2.number);

		return res;
	}

	Rational operator+(const Rational& num1, const int num2)
	{
		Rational res;
		Rational _num2(num2);

		mpq_add(res.number, num1.number, _num2.number);

		return res;
	}

	Rational operator+(const int num1, const Rational& num2)
	{
		Rational res;
		Rational _num1(num1);

		mpq_add(res.number, _num1.number, num2.number);

		return res;
	}

	Rational operator-(const Rational& num1, const Rational& num2)
	{
		Rational res;

		mpq_sub(res.number, num1.number, num2.number);

		return res;
	}

	Rational operator-(const Rational& num1, const int num2)
	{
		Rational res;
		Rational _num2(num2);

		mpq_sub(res.number, num1.number, _num2.number);

		return res;
	}

	Rational operator-(const int num1, const Rational& num2)
	{
		Rational res;
		Rational _num1(num1);

		mpq_sub(res.number, _num1.number, num2.number);

		return res;
	}

	Rational operator*(const Rational& num1, const Rational& num2)
	{
		Rational res;

		mpq_mul(res.number, num1.number, num2.number);

		return res;
	}

	Rational operator*(const Rational& num1, const int num2)
	{
		Rational res;
		Rational _num2(num2);

		mpq_mul(res.number, num1.number, _num2.number);

		return res;
	}

	Rational operator*(const int num1, const Rational& num2)
	{
		Rational res;
		Rational _num1(num1);

		mpq_mul(res.number, _num1.number, num2.number);

		return res;
	}

	Rational operator/(const Rational& num1, const Rational& num2)
	{
		Rational res;

		if (num2 == 0)
		{
		//	throw MathException(MATH_ERROR_OVERFLOW);
		}

		mpq_div(res.number, num1.number, num2.number);

		return res;
	}

	Rational operator/(const Rational& num1, const int num2)
	{
		Rational res;
		Rational _num2(num2);

		if (num2 == 0)
		{
		//	throw MathException(MATH_ERROR_OVERFLOW);
		}

		mpq_div(res.number, num1.number, _num2.number);

		return res;
	}

	Rational operator/(const int num1, const Rational& num2)
	{
		Rational res;
		Rational _num1(num1);

		if (num2 == 0)
		{
		//	throw MathException(MATH_ERROR_OVERFLOW);
		}

		mpq_div(res.number, _num1.number, num2.number);

		return res;
	}

	void Rational::operator+=(const Rational& num)
	{
		*this = *this + num;
	}

	bool operator==(const Rational& num1, const Rational& num2)
	{
		return mpq_cmp(num1.number, num2.number) == 0;
	}

	bool operator==(const Rational& num1, const int num2)
	{
		return mpq_cmp_si(num1.number, num2, 1) == 0;
	}

	bool operator==(const int num1, const Rational& num2)
	{
		return mpq_cmp_si(num2.number, num1, 1) == 0;
	}

	bool operator!=(const Rational& num1, const Rational& num2)
	{
		return mpq_cmp(num1.number, num2.number) != 0;
	}

	bool operator!=(const Rational& num1, const int num2)
	{
		return mpq_cmp_si(num1.number, num2, 1) != 0;
	}

	bool operator!=(const int num1, const Rational& num2)
	{
		return mpq_cmp_si(num2.number, num1, 1) == 0;
	}

	bool operator>(const Rational& num1, const Rational& num2)
	{
		return mpq_cmp(num1.number, num2.number) > 0;
	}

	bool operator>(const Rational& num1, const int num2)
	{
		return mpq_cmp_si(num1.number, num2, 1) > 0;
	}

	bool operator>(const int num1, const Rational& num2)
	{
		return mpq_cmp_si(num2.number, num1, 1) < 0;
	}

	bool operator>=(const Rational& num1, const Rational& num2)
	{
		return mpq_cmp(num1.number, num2.number) >= 0;
	}

	bool operator>=(const Rational& num1, const int num2)
	{
		return mpq_cmp_si(num1.number, num2, 1) >= 0;
	}

	bool operator>=(const int num1, const Rational& num2)
	{
		return mpq_cmp_si(num2.number, num1, 1) <= 0;
	}

	bool operator<(const Rational& num1, const Rational& num2)
	{
		return mpq_cmp(num1.number, num2.number) < 0;
	}

	bool operator<(const Rational& num1, const int num2)
	{
		return mpq_cmp_si(num1.number, num2, 1) < 0;
	}

	bool operator<(const int num1, const Rational& num2)
	{
		return mpq_cmp_si(num2.number, num1, 1) > 0;
	}

	bool operator<=(const Rational& num1, const Rational& num2)
	{
		return mpq_cmp(num1.number, num2.number) <= 0;
	}

	bool operator<=(const Rational& num1, const int num2)
	{
		return mpq_cmp_si(num1.number, num2, 1) <= 0;
	}

	bool operator<=(const int num1, const Rational& num2)
	{
		return mpq_cmp_si(num2.number, num1, 1) >= 0;
	}

	Integer Rational::GetNumerator()
	{
		Integer numerator;
		mpz_t numer;
		mpz_init(numer);

		mpq_get_num(numer, number);
		numerator = numer;

		return numerator;
	}
	
	Integer Rational::GetDenomerator()
	{
		Integer denomerator;
		mpz_t denom;
		mpz_init(denom);

		mpq_get_den(denom, number);
		denomerator = denom;

		return denomerator;
	}

	string Rational::ToString() const
	{
		char* tmp = (char*)malloc(mpz_sizeinbase(mpq_numref(number), 10) + 
			mpz_sizeinbase(mpq_denref(number), 10) + 3);

		char* str = mpq_get_str(tmp, 10, number);
		string res(str);
		free(str);

		return res;
	}

	#ifdef TRACE_OUTPUT
	void Rational::UpdateNumberStr()
	{
		numberStr = ToString();
	}
	#endif
}
