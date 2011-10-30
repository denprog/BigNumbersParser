#include "stdafx.h"
#include "Rational.h"

namespace BigNumbersParser
{
	/**
	 * Default constructor.
	 */
	Rational::Rational()
	{
		mpq_init(number);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	/**
	 * Copy constructor.
	 * @param source Source.
	 */
	Rational::Rational(const Rational& source)
	{
		mpq_init(number);
		mpq_set(number, source.number);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	/**
	 * Constructor from int.
	 * @param num Number.
	 */
	Rational::Rational(const int num)
	{
		mpq_init(number);
		mpq_set_si(number, num, 1);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	/**
	 * Constructor from double.
	 * @param precision The precision.
	 * @param num	Number.
	 */
	Rational::Rational(const int precision, const double num)
	{
		mpq_init(number);
		mpq_set_d(number, num);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	/**
	 * Constructor from int.
	 * @param precision The precision.
	 * @param num	Number.
	 */
	Rational::Rational(const int precision, const int num)
	{
		mpq_init(number);
		mpq_set_si(number, num, 1);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	/**
	 * Constructor from string.
	 * @param num Number.
	 */
	Rational::Rational(const string& num)
	{
		mpq_init(number);
		mpq_set_str(number, num.c_str(), 10);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	/**
	 * Destructor.
	 */
	Rational::~Rational()
	{
		mpq_clear(number);
	}
		
	/**
	 * = casting operator.
	 * @param source Source.
	 * @return The result number.
	 */
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

	/**
	 * = casting operator.
	 * @param source Source.
	 * @return The result number.
	 */
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

	/**
	 * + operator.
	 * @return The result number.
	 */
	Rational Rational::operator+()
	{
		Rational res(*this);

		return res;
	}

	/**
	 * - operator.
	 * @return The result number.
	 */
	Rational Rational::operator-()
	{
		Rational res(*this);

		mpq_neg(res.number, number);

		return res;
	}

	/**
	 * Addition operator.
	 * @param num1 The first value.
	 * @param num2 A value to add to it.
	 * @return The result of the operation.
	 */
	Rational operator+(const Rational& num1, const Rational& num2)
	{
		Rational res;

		mpq_add(res.number, num1.number, num2.number);

		return res;
	}

	/**
	 * Addition operator.
	 * @param num1 The first value.
	 * @param num2 A value to add to it.
	 * @return The result of the operation.
	 */
	Rational operator+(const Rational& num1, const int num2)
	{
		Rational res;
		Rational _num2(num2);

		mpq_add(res.number, num1.number, _num2.number);

		return res;
	}

	/**
	 * Addition operator.
	 * @param num1 The first value.
	 * @param num2 A value to add to it.
	 * @return The result of the operation.
	 */
	Rational operator+(const int num1, const Rational& num2)
	{
		Rational res;
		Rational _num1(num1);

		mpq_add(res.number, _num1.number, num2.number);

		return res;
	}

	/**
	 * Subtraction operator.
	 * @param num1 The first value.
	 * @param num2 A value to subtract from it.
	 * @return The result of the operation.
	 */
	Rational operator-(const Rational& num1, const Rational& num2)
	{
		Rational res;

		mpq_sub(res.number, num1.number, num2.number);

		return res;
	}

	/**
	 * Subtraction operator.
	 * @param num1 The first value.
	 * @param num2 A value to subtract from it.
	 * @return The result of the operation.
	 */
	Rational operator-(const Rational& num1, const int num2)
	{
		Rational res;
		Rational _num2(num2);

		mpq_sub(res.number, num1.number, _num2.number);

		return res;
	}

	/**
	 * Subtraction operator.
	 * @param num1 The first value.
	 * @param num2 A value to subtract from it.
	 * @return The result of the operation.
	 */
	Rational operator-(const int num1, const Rational& num2)
	{
		Rational res;
		Rational _num1(num1);

		mpq_sub(res.number, _num1.number, num2.number);

		return res;
	}

	/**
	 * Multiplication operator.
	 * @param num1 The first value to multiply.
	 * @param num2 The second value to multiply.
	 * @return The result of the operation.
	 */
	Rational operator*(const Rational& num1, const Rational& num2)
	{
		Rational res;

		mpq_mul(res.number, num1.number, num2.number);

		return res;
	}

	/**
	 * Multiplication operator.
	 * @param num1 The first value to multiply.
	 * @param num2 The second value to multiply.
	 * @return The result of the operation.
	 */
	Rational operator*(const Rational& num1, const int num2)
	{
		Rational res;
		Rational _num2(num2);

		mpq_mul(res.number, num1.number, _num2.number);

		return res;
	}

	/**
	 * Multiplication operator.
	 * @param num1 The first value to multiply.
	 * @param num2 The second value to multiply.
	 * @return The result of the operation.
	 */
	Rational operator*(const int num1, const Rational& num2)
	{
		Rational res;
		Rational _num1(num1);

		mpq_mul(res.number, _num1.number, num2.number);

		return res;
	}

	/**
	 * Division operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Rational operator/(const Rational& num1, const Rational& num2)
	{
		Rational res;

		if (num2 == 0)
			throw MathException(DivisionByZero);

		mpq_div(res.number, num1.number, num2.number);

		return res;
	}

	/**
	 * Division operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Rational operator/(const Rational& num1, const int num2)
	{
		Rational res;
		Rational _num2(num2);

		if (num2 == 0)
			throw MathException(DivisionByZero);

		mpq_div(res.number, num1.number, _num2.number);

		return res;
	}

	/**
	 * Division operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Rational operator/(const int num1, const Rational& num2)
	{
		Rational res;
		Rational _num1(num1);

		if (num2 == 0)
			throw MathException(DivisionByZero);

		mpq_div(res.number, _num1.number, num2.number);

		return res;
	}

	/**
	 * += operator.
	 * @param num A value to add to it.
	 */
	void Rational::operator+=(const Rational& num)
	{
		*this = *this + num;
	}

	/**
	 * Equality operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are considered equivalent.
	 */
	bool operator==(const Rational& num1, const Rational& num2)
	{
		return mpq_cmp(num1.number, num2.number) == 0;
	}

	/**
	 * Equality operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are considered equivalent.
	 */
	bool operator==(const Rational& num1, const int num2)
	{
		return mpq_cmp_si(num1.number, num2, 1) == 0;
	}

	/**
	 * Equality operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are considered equivalent.
	 */
	bool operator==(const int num1, const Rational& num2)
	{
		return mpq_cmp_si(num2.number, num1, 1) == 0;
	}

	/**
	 * Not equality operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are not considered equivalent.
	 */
	bool operator!=(const Rational& num1, const Rational& num2)
	{
		return mpq_cmp(num1.number, num2.number) != 0;
	}

	/**
	 * Not equality operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are not considered equivalent.
	 */
	bool operator!=(const Rational& num1, const int num2)
	{
		return mpq_cmp_si(num1.number, num2, 1) != 0;
	}

	/**
	 * Not equality operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are not considered equivalent.
	 */
	bool operator!=(const int num1, const Rational& num2)
	{
		return mpq_cmp_si(num2.number, num1, 1) == 0;
	}

	/**
	 * Greater-than comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than to the second.
	 */
	bool operator>(const Rational& num1, const Rational& num2)
	{
		return mpq_cmp(num1.number, num2.number) > 0;
	}

	/**
	 * Greater-than comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than to the second.
	 */
	bool operator>(const Rational& num1, const int num2)
	{
		return mpq_cmp_si(num1.number, num2, 1) > 0;
	}

	/**
	 * Greater-than comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than to the second.
	 */
	bool operator>(const int num1, const Rational& num2)
	{
		return mpq_cmp_si(num2.number, num1, 1) < 0;
	}

	/**
	 * Greater-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than or equal to the second.
	 */
	bool operator>=(const Rational& num1, const Rational& num2)
	{
		return mpq_cmp(num1.number, num2.number) >= 0;
	}

	/**
	 * Greater-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than or equal to the second.
	 */
	bool operator>=(const Rational& num1, const int num2)
	{
		return mpq_cmp_si(num1.number, num2, 1) >= 0;
	}

	/**
	 * Greater-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than or equal to the second.
	 */
	bool operator>=(const int num1, const Rational& num2)
	{
		return mpq_cmp_si(num2.number, num1, 1) <= 0;
	}

	/**
	 * Less-than comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than the second.
	 */
	bool operator<(const Rational& num1, const Rational& num2)
	{
		return mpq_cmp(num1.number, num2.number) < 0;
	}

	/**
	 * Less-than comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than the second.
	 */
	bool operator<(const Rational& num1, const int num2)
	{
		return mpq_cmp_si(num1.number, num2, 1) < 0;
	}

	/**
	 * Less-than comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than the second.
	 */
	bool operator<(const int num1, const Rational& num2)
	{
		return mpq_cmp_si(num2.number, num1, 1) > 0;
	}

	/**
	 * Less-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than or equal to the second.
	 */
	bool operator<=(const Rational& num1, const Rational& num2)
	{
		return mpq_cmp(num1.number, num2.number) <= 0;
	}

	/**
	 * Less-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than or equal to the second.
	 */
	bool operator<=(const Rational& num1, const int num2)
	{
		return mpq_cmp_si(num1.number, num2, 1) <= 0;
	}

	/**
	 * Less-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than or equal to the second.
	 */
	bool operator<=(const int num1, const Rational& num2)
	{
		return mpq_cmp_si(num2.number, num1, 1) >= 0;
	}

	/**
	 * Gets the numerator of the number.
	 * @return The numerator.
	 */
	Integer Rational::GetNumerator()
	{
		Integer numerator;
		mpz_t numer;
		mpz_init(numer);

		mpq_get_num(numer, number);
		numerator = numer;

		return numerator;
	}
	
	/**
	 * Gets the denomerator of the number.
	 * @return The denomerator.
	 */
	Integer Rational::GetDenomerator()
	{
		Integer denomerator;
		mpz_t denom;
		mpz_init(denom);

		mpq_get_den(denom, number);
		denomerator = denom;

		return denomerator;
	}

	/**
	 * Convert this number into a string representation.
	 * @return A string representation of this number.
	 */
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
	/**
	 * Updates the numberStr field.
	 */
	void Rational::UpdateNumberStr()
	{
		numberStr = ToString();
	}
	#endif
}
