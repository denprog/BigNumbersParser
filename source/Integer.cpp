#include "stdafx.h"
#include "Integer.h"

namespace BigNumbersParser
{
	Integer::Integer()
	{
		mpz_init(number);

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif
	}

	Integer::Integer(const int precision, const int num)
	{
		mpz_init(number);
		mpz_set_si(number, num);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	Integer::Integer(const int precision, const double num)
	{
		mpz_init(number);
		mpz_set_d(number, num);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	Integer::Integer(const int num)
	{
		mpz_init(number);
		mpz_set_si(number, num);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	Integer::Integer(const Integer& source)
	{
		mpz_init(number);
		mpz_set(number, source.number);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	Integer::Integer(const string& num)
	{
		mpz_init(number);
		mpz_set_str(number, num.c_str(), 10);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	Integer::~Integer()
	{
		mpz_clear(number);
	}

	Integer& Integer::operator=(const Integer& source)
	{
		if (this == &source)
			return *this;

		mpz_clear(number);
		mpz_init(number);

		mpz_set(number, source.number);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif

		return *this;
	}

	Integer& Integer::operator=(const std::string& num)
	{
		mpz_init(number);
		mpz_set_str(number, num.c_str(), 10);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif

		return *this;
	}

	Integer& Integer::operator=(const mpz_t& source)
	{
		mpz_set(number, source);

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif

		return *this;
	}

	Integer Integer::operator+()
	{
		Integer res(*this);

		return res;
	}

	Integer Integer::operator-()
	{
		Integer res(*this);

		mpz_neg(res.number, number);

		return res;
	}

	Integer operator+(const Integer& num1, const Integer& num2)
	{
		Integer res;

		mpz_add(res.number, num1.number, num2.number);

		return res;
	}

	Integer operator+(const Integer& num1, const int num2)
	{
		Integer res;
		Integer _num2(num2);

		mpz_add(res.number, num1.number, _num2.number);

		return res;
	}

	Integer operator+(const int num1, const Integer& num2)
	{
		Integer res;
		Integer _num1(num1);

		mpz_add(res.number, _num1.number, num2.number);

		return res;
	}

	Integer operator-(const Integer& num1, const Integer& num2)
	{
		Integer res;

		mpz_sub(res.number, num1.number, num2.number);

		return res;
	}

	Integer operator-(const Integer& num1, const int num2)
	{
		Integer res;
		Integer _num2(num2);

		mpz_sub(res.number, num1.number, _num2.number);

		return res;
	}

	Integer operator-(const int num1, const Integer& num2)
	{
		Integer res;
		Integer _num1(num1);

		mpz_sub(res.number, _num1.number, num2.number);

		return res;
	}

	Integer operator*(const Integer& num1, const Integer& num2)
	{
		Integer res;

		mpz_mul(res.number, num1.number, num2.number);

		return res;
	}

	Integer operator*(const Integer& num1, const int num2)
	{
		Integer res;

		mpz_mul_si(res.number, num1.number, num2);

		return res;
	}

	Integer operator*(const int num1, const Integer& num2)
	{
		Integer res;

		mpz_mul_si(res.number, num2.number, num1);

		return res;
	}

	Integer operator/(const Integer& num1, const Integer& num2)
	{
		Integer res;

		if (num2 == 0)
			throw MathException(DivisionByZero);

		//mpz_div(res.number, num1.number, num2.number);
		mpz_divexact(res.number, num1.number, num2.number);

		return res;
	}

	Integer operator/(const Integer& num1, const int num2)
	{
		Integer res;
		Integer _num2(num2);

		if (num2 == 0)
		{
			//throw MathException(MATH_ERROR_OVERFLOW);
		}

		//mpz_div(res.number, num1.number, _num2.number);
		mpz_divexact(res.number, num1.number, _num2.number);

		return res;
	}

	Integer operator/(const int num1, const Integer& num2)
	{
		Integer res;
		Integer _num1(num1);

		if (num2 == 0)
		{
			//throw MathException(MATH_ERROR_OVERFLOW);
		}

		//mpz_div(res.number, _num1.number, num2.number);
		mpz_divexact(res.number, _num1.number, num2.number);

		return res;
	}

	Integer operator%(const Integer& num1, const Integer& num2)
	{
		Integer res;

		if (num2 == 0)
		{
			//throw MathException(MATH_ERROR_OVERFLOW);
		}

		mpz_mod(res.number, num1.number, num2.number);

		return res;
	}

	Integer operator%(const Integer& num1, const int num2)
	{
		Integer res;
		Integer _num2(num2);

		if (num2 == 0)
		{
			//throw MathException(MATH_ERROR_OVERFLOW);
		}

		mpz_mod(res.number, num1.number, _num2.number);

		return res;
	}

	Integer operator%(const int num1, const Integer& num2)
	{
		Integer res;
		Integer _num1(num1);

		if (num2 == 0)
		{
			//throw MathException(MATH_ERROR_OVERFLOW);
		}

		mpz_mod(res.number, _num1.number, num2.number);

		return res;
	}

	void Integer::operator+=(const Integer& num)
	{
		*this = *this + num;
	}

	void Integer::operator-=(const Integer& num)
	{
		*this = *this - num;
	}

	void Integer::operator*=(const Integer& num)
	{
		*this = *this * num;
	}

	void Integer::operator/=(const Integer& num)
	{
		*this = *this / num;
	}

	void Integer::operator%=(const Integer& num)
	{
		*this = *this % num;
	}

	void Integer::operator=(const int num)
	{
		mpz_set_si(number, num);
	}

	Integer::operator int() const
	{
		if (mpz_fits_slong_p(number) == 0)
		{
			//throw MathException(MATH_ERROR_CONVERSION_DOES_NOT_FITS);
		}

		return mpz_get_si(number);
	}

	Integer pow(const Integer& num1, const Integer& num2)
	{
		Integer res;

		mpz_pow_ui(res.number, num1.number, (int)num2);

		return res;
	}

	Integer abs(const Integer& num)
	{
		Integer res;

		mpz_abs(res.number, num.number);

		return res;
	}

	Integer fact(const Integer& num)
	{
		Integer res;

		mpz_fac_ui(res.number, (int)num);

		return res;
	}

	int Integer::GetPrecision() const
	{
		return 0;
	}
	
	void Integer::SetPrecision(int precision)
	{
	}

	bool Integer::IsNan()
	{
		return false;
	}

	string Integer::ToString() const
	{
		int len = mpz_sizeinbase(number, 10) + 1;
		char *tmp = (char*)malloc(len + 1);

		char* str = mpz_get_str(tmp, 10, number);
		string res(str);
		free(tmp);

		return res;
	}

#ifdef _DEBUG
	string Integer::ToString(int exp, int accuracy) const
	{
		string res;
		
		return res;
	}
#endif

	Integer Integer::FromString(const std::string& str)
	{
		return Integer(str);
	}

#ifdef TRACE_OUTPUT
	void Integer::UpdateNumberStr()
	{
		numberStr = ToString();
	}
#endif
}
