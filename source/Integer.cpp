#include "stdafx.h"
#include "Integer.h"

namespace BigNumbersParser
{
	/**
	 * Default constructor.
	 */
	Integer::Integer()
	{
		mpz_init(number);

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif
	}

	/**
	 * Constructor.
	 * @param precision The precision.
	 * @param num Number.
	 */
	Integer::Integer(const int precision, const int num)
	{
		mpz_init(number);
		mpz_set_si(number, num);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	/**
	 * Constructor.
	 * @param precision The precision.
	 * @param num Number.
	 */
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

	/**
	 * Copy constructor.
	 * @param source Source.
	 */
	Integer::Integer(const Integer& source)
	{
		mpz_init(number);
		mpz_set(number, source.number);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	/**
	 * Constructor.
	 * @param num Number.
	 */
	Integer::Integer(const string& num)
	{
		mpz_init(number);
		mpz_set_str(number, num.c_str(), 10);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	/**
	 * Destructor.
	 */
	Integer::~Integer()
	{
		mpz_clear(number);
	}

	/**
	 * = casting operator from Integer.
	 * @param source Source for the operation.
	 * @return The result of the operation.
	 */
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

	/**
	 * = casting operator from std::string.
	 * @param num Number.
	 * @return The result of the operation.
	 */
	Integer& Integer::operator=(const std::string& num)
	{
		mpz_init(number);
		mpz_set_str(number, num.c_str(), 10);

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif

		return *this;
	}

	/**
	 * = casting operator from mpz_t.
	 * @param source Source.
	 * @return The result of the operation.
	 */
	Integer& Integer::operator=(const mpz_t& source)
	{
		mpz_set(number, source);

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif

		return *this;
	}

	/**
	 * + casting operator.
	 * @return The result of the operation.
	 */
	Integer Integer::operator+()
	{
		Integer res(*this);

		return res;
	}

	/**
	 * - casting operator.
	 * @return The result of the operation.
	 */
	Integer Integer::operator-()
	{
		Integer res(*this);

		mpz_neg(res.number, number);

		return res;
	}

	/**
	 * Addition operator.
	 * @param num1 The first value.
	 * @param num2 A value to add to it.
	 * @return The result of the operation.
	 */
	Integer operator+(const Integer& num1, const Integer& num2)
	{
		Integer res;

		mpz_add(res.number, num1.number, num2.number);

		return res;
	}

	/**
	 * Addition operator.
	 * @param num1 The first value.
	 * @param num2 A value to add to it.
	 * @return The result of the operation.
	 */
	Integer operator+(const Integer& num1, const int num2)
	{
		Integer res;
		Integer _num2(num2);

		mpz_add(res.number, num1.number, _num2.number);

		return res;
	}

	/**
	 * Addition operator.
	 * @param num1 The first value.
	 * @param num2 A value to add to it.
	 * @return The result of the operation.
	 */
	Integer operator+(const int num1, const Integer& num2)
	{
		Integer res;
		Integer _num1(num1);

		mpz_add(res.number, _num1.number, num2.number);

		return res;
	}

	/**
	 * Subtraction operator.
	 * @param num1 The first value.
	 * @param num2 A value to subtract from it.
	 * @return The result of the operation.
	 */
	Integer operator-(const Integer& num1, const Integer& num2)
	{
		Integer res;

		mpz_sub(res.number, num1.number, num2.number);

		return res;
	}

	/**
	 * Subtraction operator.
	 * @param num1 The first value.
	 * @param num2 A value to subtract from it.
	 * @return The result of the operation.
	 */
	Integer operator-(const Integer& num1, const int num2)
	{
		Integer res;
		Integer _num2(num2);

		mpz_sub(res.number, num1.number, _num2.number);

		return res;
	}

	/**
	 * Subtraction operator.
	 * @param num1 The first value.
	 * @param num2 A value to subtract from it.
	 * @return The result of the operation.
	 */
	Integer operator-(const int num1, const Integer& num2)
	{
		Integer res;
		Integer _num1(num1);

		mpz_sub(res.number, _num1.number, num2.number);

		return res;
	}

	/**
	 * Multiplication operator.
	 * @param num1 The first value to multiply.
	 * @param num2 The second value to multiply.
	 * @return The result of the operation.
	 */
	Integer operator*(const Integer& num1, const Integer& num2)
	{
		Integer res;

		mpz_mul(res.number, num1.number, num2.number);

		return res;
	}

	/**
	 * Multiplication operator.
	 * @param num1 The first value to multiply.
	 * @param num2 The second value to multiply.
	 * @return The result of the operation.
	 */
	Integer operator*(const Integer& num1, const int num2)
	{
		Integer res;

		mpz_mul_si(res.number, num1.number, num2);

		return res;
	}

	/**
	 * Multiplication operator.
	 * @param num1 The first value to multiply.
	 * @param num2 The second value to multiply.
	 * @return The result of the operation.
	 */
	Integer operator*(const int num1, const Integer& num2)
	{
		Integer res;

		mpz_mul_si(res.number, num2.number, num1);

		return res;
	}

	/**
	 * Division operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Integer operator/(const Integer& num1, const Integer& num2)
	{
		Integer res;

		if (num2 == 0)
			throw MathException(DivisionByZero);

		//mpz_div(res.number, num1.number, num2.number);
		mpz_divexact(res.number, num1.number, num2.number);

		return res;
	}

	/**
	 * Division operator.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Integer operator/(const Integer& num1, const int num2)
	{
		Integer res;
		Integer _num2(num2);

		if (num2 == 0)
			throw MathException(DivisionByZero);

		//mpz_div(res.number, num1.number, _num2.number);
		mpz_divexact(res.number, num1.number, _num2.number);

		return res;
	}

	/**
	 * Division operator.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Integer operator/(const int num1, const Integer& num2)
	{
		Integer res;
		Integer _num1(num1);

		if (num2 == 0)
			throw MathException(DivisionByZero);

		//mpz_div(res.number, _num1.number, num2.number);
		mpz_divexact(res.number, _num1.number, num2.number);

		return res;
	}

	/**
	 * Modulus operator.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Integer operator%(const Integer& num1, const Integer& num2)
	{
		Integer res;

		if (num2 == 0)
			throw MathException(DivisionByZero);

		mpz_mod(res.number, num1.number, num2.number);

		return res;
	}

	/**
	 * Modulus operator.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Integer operator%(const Integer& num1, const int num2)
	{
		Integer res;
		Integer _num2(num2);

		if (num2 == 0)
			throw MathException(DivisionByZero);

		mpz_mod(res.number, num1.number, _num2.number);

		return res;
	}

	/**
	 * Modulus operator.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Integer operator%(const int num1, const Integer& num2)
	{
		Integer res;
		Integer _num1(num1);

		if (num2 == 0)
			throw MathException(DivisionByZero);

		mpz_mod(res.number, _num1.number, num2.number);

		return res;
	}

	/**
	 * += operator.
	 * @param num A value to add to it.
	 */
	void Integer::operator+=(const Integer& num)
	{
		*this = *this + num;
	}

	/**
	 * -= operator.
	 * @param num A value to subtract from it.
	 */
	void Integer::operator-=(const Integer& num)
	{
		*this = *this - num;
	}

	/**
	 * *= operator.
	 * @param num A value to multiply.
	 */
	void Integer::operator*=(const Integer& num)
	{
		*this = *this * num;
	}

	/**
	 * /= operator.
	 * @param num The denominator.
	 */
	void Integer::operator/=(const Integer& num)
	{
		*this = *this / num;
	}

	/**
	 * %= operator.
	 * @param num The denominator.
	 */
	void Integer::operator%=(const Integer& num)
	{
		*this = *this % num;
	}

	bool operator==(const Integer& num1, const Integer& num2)
	{
		return mpz_cmp(num1.number, num2.number) == 0;
	}

	bool operator==(const Integer& num1, const int num2)
	{
		return mpz_cmp_si(num1.number, num2) == 0;
	}

	bool operator==(const int num1, const Integer& num2)
	{
		return mpz_cmp_si(num2.number, num1) == 0;
	}

	bool operator!=(const Integer& num1, const Integer& num2)
	{
		return mpz_cmp(num1.number, num2.number) != 0;
	}

	bool operator!=(const Integer& num1, const int num2)
	{
		return mpz_cmp_si(num1.number, num2) != 0;
	}

	bool operator!=(const int num1, const Integer& num2)
	{
		return mpz_cmp_si(num2.number, num1) == 0;
	}

	bool operator>(const Integer& num1, const Integer& num2)
	{
		return mpz_cmp(num1.number, num2.number) > 0;
	}

	bool operator>(const Integer& num1, const int num2)
	{
		return mpz_cmp_si(num1.number, num2) > 0;
	}

	bool operator>(const int num1, const Integer& num2)
	{
		return mpz_cmp_si(num2.number, num1) < 0;
	}

	bool operator>=(const Integer& num1, const Integer& num2)
	{
		return mpz_cmp(num1.number, num2.number) >= 0;
	}

	bool operator>=(const Integer& num1, const int num2)
	{
		return mpz_cmp_si(num1.number, num2) >= 0;
	}

	bool operator>=(const int num1, const Integer& num2)
	{
		return mpz_cmp_si(num2.number, num1) <= 0;
	}

	bool operator<(const Integer& num1, const Integer& num2)
	{
		return mpz_cmp(num1.number, num2.number) < 0;
	}

	bool operator<(const Integer& num1, const int num2)
	{
		return mpz_cmp_si(num1.number, num2) < 0;
	}

	bool operator<(const int num1, const Integer& num2)
	{
		return mpz_cmp_si(num2.number, num1) > 0;
	}

	bool operator<=(const Integer& num1, const Integer& num2)
	{
		return mpz_cmp(num1.number, num2.number) <= 0;
	}

	bool operator<=(const Integer& num1, const int num2)
	{
		return mpz_cmp_si(num1.number, num2) <= 0;
	}

	bool operator<=(const int num1, const Integer& num2)
	{
		return mpz_cmp_si(num2.number, num1) >= 0;
	}

	/**
	 * = operator.
	 * @param num Number.
	 */
	void Integer::operator=(const int num)
	{
		mpz_set_si(number, num);
	}

	/**
	 * Gets the int.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @return number of type int.
	 */
	Integer::operator int() const
	{
		if (mpz_fits_slong_p(number) == 0)
			throw MathException(ConversionDoesNotFits);

		return mpz_get_si(number);
	}

	/**
	 * Power function.
	 * @param num1 Base.
	 * @param num2 Exponent.
	 * @return Base raised to exponent.
	 */
	Integer pow(const Integer& num1, const Integer& num2)
	{
		Integer res;

		mpz_pow_ui(res.number, num1.number, (int)num2);

		return res;
	}

	/**
	 * Absolute number function.
	 * @param num The argument.
	 * @return Absolute value.
	 */
	Integer abs(const Integer& num)
	{
		Integer res;

		mpz_abs(res.number, num.number);

		return res;
	}

	/**
	 * Factorial function.
	 * @param num The argument.
	 * @return Factorial value.
	 */
	Integer fact(const Integer& num)
	{
		Integer res;

		mpz_fac_ui(res.number, (int)num);

		return res;
	}

	/**
	 * Gets the precision.
	 * @return Zero.
	 */
	int Integer::GetPrecision() const
	{
		return 0;
	}
	
	/**
	 * Sets a precision.
	 * @param precision The precision.
	 */
	void Integer::SetPrecision(int precision)
	{
	}

	/**
	 * Query if this object is nan.
	 * @return true if nan, false if not.
	 */
	bool Integer::IsNan()
	{
		return false;
	}

	/**
	 * Convert this number into a string representation.
	 * @return A string representation of this number.
	 */
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
	/**
	 * Convert this object into a string representation 1.23e+123.
	 * @param exp	The exponent.
	 * @param accuracy The accuracy.
	 * @return A string representation of this object.
	 */
	string Integer::ToString(int exp, int accuracy) const
	{
		string res;
		
		return res;
	}
#endif

	/**
	 * Initializes this number from a string.
	 * @param str The string.
	 * @return The number.
	 */
	Integer Integer::FromString(const std::string& str)
	{
		return Integer(str);
	}

#ifdef TRACE_OUTPUT
	/**
	 * Updates the numberStr field.
	 */
	void Integer::UpdateNumberStr()
	{
		numberStr = ToString();
	}
#endif
}
