#include "stdafx.h"
#include "Real.h"

namespace BigNumbersParser
{
	/**
	 * Default constructor.
	 */
	Real::Real()
	{
		mpfr_init2(number, mpfr_get_default_prec());
		mpfr_set_si(number, 0, GMP_RNDN);

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif
	}

	/**
	 * Constructor.
	 * @param precision The precision.
	 */
	Real::Real(int precision)
	{
		mpfr_init2(number, max((int)mpfr_get_default_prec(), precision));
		//mpfr_init2(number, precision);
		mpfr_set_si(number, 0, GMP_RNDN);
		//addPrecision = 0;

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif
	}

	/**
	 * Constructor from char*.
	 * @param precision The precision.
	 * @param num	The number.
	 */
	Real::Real(int precision, const char* num)
	{
		mpfr_init2(number, max((int)mpfr_get_default_prec(), precision));
		//mpfr_init2(number, strlen(num) + 1);
		mpfr_set_str(number, num, DEFAULT_BASE, MPFR_RNDZ);
		stringNumber = num;
		//mpfr_prec_round(number, precision / 2, GMP_RNDN);
		//addPrecision = (int)strchr(num, '.');
		//if (!addPrecision)
		//	addPrecision = strlen(num);
		//else
		//	addPrecision -= (int)num;

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif
	}

	/**
	 * Constructor from int.
	 * @param precision The precision.
	 * @param num	The number.
	 */
	Real::Real(int precision, int num)
	{
		mpfr_init2(number, max((int)mpfr_get_default_prec(), precision));
		//mpfr_init2(number, precision);
		mpfr_set_si(number, num, GMP_RNDN);
		//addPrecision = 1;

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif
	}

	/**
	 * Constructor from float.
	 * @param precision The precision.
	 * @param num	The number.
	 */
	Real::Real(int precision, float num)
	{
		mpfr_init2(number, max((int)mpfr_get_default_prec(), precision));
		//mpfr_init2(number, precision);
		mpfr_set_d(number, num, GMP_RNDN);
		//addPrecision = 1;

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif
	}

	/**
	 * Constructor from string.
	 * @param num The number.
	 */
	Real::Real(const string& num)
	{
		stringNumber = num;
		mpfr_init2(number, max((int)mpfr_get_default_prec(), MathHelper::ToBitPrecision(num.length() * 2)) + 1);
		mpfr_set_str(number, num.c_str(), DEFAULT_BASE, MPFR_RNDA);

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif
	}

	/**
	 * Copy constructor.
	 * @param source The source number.
	 */
	Real::Real(const Real& source)
	{
		mpfr_init2(number, source.GetBitPrecision());
		mpfr_set(number, source.number, GMP_RNDN);
		//addPrecision = source.addPrecision;
		stringNumber = source.stringNumber;
		
#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif
	}

	/**
	 * Destructor.
	 */
	Real::~Real()
	{
		mpfr_clear(number);
	}

	/**
	 * = operator.
	 * @param source Source for the number.
	 * @return The result number.
	 */
	Real& Real::operator=(const Real& source)
	{
		if (this == &source)
			return *this;

		mpfr_clear(number);
		mpfr_init2(number, source.GetBitPrecision());
		mpfr_set(number, source.number, GMP_RNDN);
		//addPrecision = source.addPrecision;
		stringNumber = source.stringNumber;

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif

		return *this;
	}

	/**
	 * = operator from int.
	 * @param num The number.
	 * @return The result number.
	 */
	Real& Real::operator=(const int num)
	{
		mpfr_set_si(number, num, GMP_RNDN);
		//addPrecision = 1;

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif

		return *this;
	}

	/**
	 * = operator from double.
	 * @param num The number.
	 * @return The result number.
	 */
	Real& Real::operator=(const double num)
	{
		mpfr_set_d(number, num, GMP_RNDN);
		//addPrecision = 1;

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif

		return *this;
	}

	/**
	 * = operator from char*.
	 * @param num The number.
	 * @return The result number.
	 */
	Real& Real::operator=(const char* num)
	{
		mpfr_t t;
		mpfr_init2(t, GetBitPrecision());

		if (mpfr_set_str(t, num, DEFAULT_BASE, GMP_RNDN) == 0)
		{
			mpfr_set(number, t, GMP_RNDN);
			mpfr_clear(t);
		}
		else
		{
			mpfr_clear(t);
		}

		stringNumber = num;

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif

		return *this;
	}

	/**
	 * = operator from std::string.
	 * @param num The number.
	 * @return The result number.
	 */
	Real& Real::operator=(const string& num)
	{
		mpfr_t t;

		if ((int)num.length() + 1 > GetPrecision())
		{
			SetBitPrecision(MathHelper::ToBitPrecision(num.length() * 2));
			mpfr_init2(t, GetBitPrecision());
		}
		else
			mpfr_init2(t, GetBitPrecision());

		if (mpfr_set_str(t, num.c_str(), DEFAULT_BASE, GMP_RNDN) == 0)
		{
			mpfr_set(number, t, GMP_RNDN);
			mpfr_clear(t);
		}
		else
		{
			mpfr_clear(t);
		}

		stringNumber = num;

#ifdef TRACE_OUTPUT
		UpdateNumberStr();
#endif

		return *this;
	}

	/**
	 * + operator.
	 * @return The result number.
	 */
	Real Real::operator+()
	{
		return *this;
	}

	/**
	 * - operator.
	 * @return The result number.
	 */
	Real Real::operator-()
	{
		Real res(GetBitPrecision());

		mpfr_neg(res.number, number, GMP_RNDN);

		return res;
	}

	/**
	 * ++ operator.
	 * @return The result number.
	 */
	Real Real::operator++()
	{
		*this += 1;

		return *this;
	}

	/**
	 * -- operator.
	 * @return The result number.
	 */
	Real Real::operator--()
	{
		*this -= 1;

		return *this;
	}

	/**
	 * Addition operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first value.
	 * @param num2 A value to add to it.
	 * @return The result of the operation.
	 */
	Real operator+(const Real& num1, const Real& num2)
	{
		Real res(max(num1.GetBitPrecision() + 2, num2.GetBitPrecision()) + 2);

		while (mpfr_add(res.number, num1.number, num2.number, DEFAULT_RND) != 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Addition operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first value.
	 * @param num2 A value to add to it.
	 * @return The result of the operation.
	 */
	Real operator+(const Real& num1, const int num2)
	{
		Real res(num1.GetBitPrecision());

		while (mpfr_add_si(res.number, num1.number, num2, DEFAULT_RND) != 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Addition operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first value.
	 * @param num2 A value to add to it.
	 * @return The result of the operation.
	 */
	Real operator+(const int num1, const Real& num2)
	{
		Real res(num2.GetBitPrecision());

		while (mpfr_add_si(res.number, num2.number, num1, DEFAULT_RND) != 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Addition operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first value.
	 * @param num2 A value to add to it.
	 * @return The result of the operation.
	 */
	Real operator+(const Real& num1, const float num2)
	{
		Real res(num1.GetBitPrecision());

		while (mpfr_add_d(res.number, num1.number, num2, DEFAULT_RND) != 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Addition operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first value.
	 * @param num2 A value to add to it.
	 * @return The result of the operation.
	 */
	Real operator+(const float num1, const Real& num2)
	{
		Real res(num2.GetBitPrecision());

		while (mpfr_add_d(res.number, num2.number, num1, DEFAULT_RND) != 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Subtraction operator.
	 * @param num1 The first value.
	 * @param num2 A value to subtract from it.
	 * @return The result of the operation.
	 */
	Real operator-(const Real& num1, const Real& num2)
	{
		Real res(max(num1.GetBitPrecision(), num2.GetBitPrecision()) + 1);

		mpfr_sub(res.number, num1.number, num2.number, GMP_RNDN);

	#ifdef TRACE_OUTPUT
		res.UpdateNumberStr();
	#endif

		return res;
	}

	/**
	 * Subtraction operator.
	 * @param num1 The first value.
	 * @param num2 A value to subtract from it.
	 * @return The result of the operation.
	 */
	Real operator-(const Real& num1, const int num2)
	{
		Real res(num1.GetBitPrecision());

		mpfr_sub_si(res.number, num1.number, num2, DEFAULT_RND);

		return res;
	}

	/**
	 * Subtraction operator.
	 * @param num1 The first value.
	 * @param num2 A value to subtract from it.
	 * @return The result of the operation.
	 */
	Real operator-(const int num1, const Real& num2)
	{
		Real res(num2.GetBitPrecision());

		mpfr_si_sub(res.number, num1, num2.number, DEFAULT_RND);

		return res;
	}

	/**
	 * Subtraction operator.
	 * @param num1 The first value.
	 * @param num2 A value to subtract from it.
	 * @return The result of the operation.
	 */
	Real operator-(const Real& num1, const float num2)
	{
		Real res(num1.GetBitPrecision());

		mpfr_sub_d(res.number, num1.number, num2, DEFAULT_RND);

		return res;
	}

	/**
	 * Subtraction operator.
	 * @param num1 The first value.
	 * @param num2 A value to subtract from it.
	 * @return The result of the operation.
	 */
	Real operator-(const float num1, const Real& num2)
	{
		Real res(num2.GetBitPrecision());

		mpfr_d_sub(res.number, num1, num2.number, DEFAULT_RND);

		return res;
	}

	/**
	 * Multiplication operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first value to multiply.
	 * @param num2 The second value to multiply.
	 * @return The result of the operation.
	 */
	Real operator*(const Real& num1, const Real& num2)
	{
		Real res(max(num1.GetBitPrecision() * 2, num2.GetBitPrecision()) * 2);

		while (mpfr_mul(res.number, num1.number, num2.number, DEFAULT_RND) != 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Multiplication operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first value to multiply.
	 * @param num2 The second value to multiply.
	 * @return The result of the operation.
	 */
	Real operator*(const Real& num1, const int num2)
	{
		Real res(num1.GetBitPrecision());

		while (mpfr_mul_si(res.number, num1.number, num2, DEFAULT_RND) != 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Multiplication operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first value to multiply.
	 * @param num2 The second value to multiply.
	 * @return The result of the operation.
	 */
	Real operator*(const int num1, const Real& num2)
	{
		Real res(num2.GetBitPrecision());

		while (mpfr_mul_si(res.number, num2.number, num1, DEFAULT_RND) != 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Multiplication operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first value to multiply.
	 * @param num2 The second value to multiply.
	 * @return The result of the operation.
	 */
	Real operator*(const Real& num1, const float num2)
	{
		Real res(num1.GetBitPrecision());

		while (mpfr_mul_d(res.number, num1.number, num2, DEFAULT_RND) != 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Multiplication operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first value to multiply.
	 * @param num2 The second value to multiply.
	 * @return The result of the operation.
	 */
	Real operator*(const float num1, const Real& num2)
	{
		Real res(num2.GetBitPrecision());

		while (mpfr_mul_d(res.number, num2.number, num1, DEFAULT_RND) != 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Division operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Real operator/(const Real& num1, const Real& num2)
	{
		Real res(max(num1.GetBitPrecision() + 2, num2.GetBitPrecision() + 2));

		mpfr_div(res.number, num1.number, num2.number, GMP_RNDN);

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(DivisionByZero);

	#ifdef TRACE_OUTPUT
		res.UpdateNumberStr();
	#endif

		return res;
	}

	/**
	 * Division operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Real operator/(const Real& num1, const int num2)
	{
		Real res(num1.GetBitPrecision());

		mpfr_div_si(res.number, num1.number, num2, DEFAULT_RND);

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		return res;
	}

	/**
	 * Division operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Real operator/(const int num1, const Real& num2)
	{
		Real res(num2.GetBitPrecision());

		mpfr_si_div(res.number, num1, num2.number, DEFAULT_RND);

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		return res;
	}

	/**
	 * Division operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Real operator/(const Real& num1, const float num2)
	{
		Real res(num1.GetBitPrecision());

		mpfr_div_d(res.number, num1.number, num2, DEFAULT_RND);

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		return res;
	}

	/**
	 * Division operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The numerator.
	 * @param num2 The denominator.
	 * @return The result of the operation.
	 */
	Real operator/(const float num1, const Real& num2)
	{
		Real res(num2.GetBitPrecision());

		mpfr_d_div(res.number, num1, num2.number, DEFAULT_RND);

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		return res;
	}
	
	/**
	 * += operator.
	 * @param num A value to add to it.
	 */
	void Real::operator+=(const Real& num)
	{
		*this = *this + num;
	}

	/**
	 * += operator.
	 * @param num A value to add to it.
	 */
	void Real::operator+=(const int num)
	{
		*this = *this + num;
	}

	/**
	 * += operator.
	 * @param num A value to add to it.
	 */
	void Real::operator+=(const float num)
	{
		*this = *this + num;
	}

	/**
	 * -= operator.
	 * @param num A value to subtract from it.
	 */
	void Real::operator-=(const Real& num)
	{
		*this = *this - num;
	}

	/**
	 * -= operator.
	 * @param num A value to subtract from it.
	 */
	void Real::operator-=(const int num)
	{
		*this = *this - num;
	}

	/**
	 * -= operator.
	 * @param num A value to subtract from it.
	 */
	void Real::operator-=(const float num)
	{
		*this = *this - num;
	}

	/**
	 * *= operator.
	 * @param num A value to multiply.
	 */
	void Real::operator*=(const Real& num)
	{
		*this = *this * num;
	}

	/**
	 * *= operator.
	 * @param num A value to multiply.
	 */
	void Real::operator*=(const int num)
	{
		*this = *this * num;
	}

	/**
	 * *= operator.
	 * @param num A value to multiply.
	 */
	void Real::operator*=(const float num)
	{
		*this = *this * num;
	}

	/**
	 * /= operator.
	 * @param num The denominator.
	 */
	void Real::operator/=(const Real& num)
	{
		*this = *this / num;
	}

	/**
	 * /= operator.
	 * @param num The denominator.
	 */
	void Real::operator/=(const int num)
	{
		*this = *this / num;
	}

	/**
	 * /= operator.
	 * @param num The denominator.
	 */
	void Real::operator/=(const float num)
	{
		*this = *this / num;
	}

	/**
	 * Gets the int.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @return number of type int.
	 */
	Real::operator int() const
	{
		if (IsInteger())
			return mpfr_get_si(number, DEFAULT_RND);
		else
			throw MathException(ConversionDoesNotFits);
	}

	/**
	 * Equality operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are considered equivalent.
	 */
	bool operator==(const Real& num1, const Real& num2)
	{
		if (num1.IsNaN() || num2.IsNaN())
			throw MathException(Overflow);

		return mpfr_equal_p(num1.number, num2.number) != 0;
	}

	/**
	 * Equality operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are considered equivalent.
	 */
	bool operator==(const Real& num1, const int num2)
	{
		if (num1.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_si(num1.number, num2) == 0;
	}

	/**
	 * Equality operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are considered equivalent.
	 */
	bool operator==(const int num1, const Real& num2)
	{
		if (num2.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_si(num2.number, num1) == 0;
	}

	/**
	 * Equality operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are considered equivalent.
	 */
	bool operator==(const Real& num1, const float num2)
	{
		if (num1.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_d(num1.number, num2) == 0;
	}

	/**
	 * Equality operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are considered equivalent.
	 */
	bool operator==(const float num1, const Real& num2)
	{
		if (num2.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_d(num2.number, num1) == 0;
	}

	/**
	 * Equality operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are considered equivalent.
	 */
	bool operator==(const Real& num1, const double num2)
	{
		if (num1.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_d(num1.number, num2) == 0;
	}

	/**
	 * Equality operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are considered equivalent.
	 */
	bool operator==(const double num1, const Real& num2)
	{
		if (num2.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_d(num2.number, num1) == 0;
	}

	/**
	 * Equality operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are considered equivalent.
	 */
	bool operator==(const Real& num1, const char* num2)
	{
		return num1 == Real(num1.GetBitPrecision(), num2);
	}

	/**
	 * Equality operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are considered equivalent.
	 */
	bool operator==(const char* num1, const Real& num2)
	{
		return Real(num2.GetBitPrecision(), num1) == num2;
	}

	/**
	 * Not equality operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are not considered equivalent.
	 */
	bool operator!=(const Real& num1, const Real& num2)
	{
		if (num1.IsNaN() || num2.IsNaN())
			throw MathException(Overflow);

		return mpfr_equal_p(num1.number, num2.number) == 0;
	}

	/**
	 * Not equality operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are not considered equivalent.
	 */
	bool operator!=(const Real& num1, const int num2)
	{
		if (num1.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_si(num1.number, num2) != 0;
	}

	/**
	 * Not equality operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are not considered equivalent.
	 */
	bool operator!=(const int num1, const Real& num2)
	{
		if (num2.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_si(num2.number, num1) != 0;
	}

	/**
	 * Not equality operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are not considered equivalent.
	 */
	bool operator!=(const Real& num1, const float num2)
	{
		if (num1.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_d(num1.number, num2) != 0;
	}

	/**
	 * Not equality operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the parameters are not considered equivalent.
	 */
	bool operator!=(const float num1, const Real& num2)
	{
		if (num2.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_d(num2.number, num1) != 0;
	}

	/**
	 * Greater-than comparison operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than to the second.
	 */
	bool operator>(const Real& num1, const Real& num2)
	{
		if (num1.IsNaN() || num2.IsNaN())
			throw MathException(Overflow);

		return mpfr_greater_p(num1.number, num2.number) != 0;
	}

	/**
	 * Greater-than comparison operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than to the second.
	 */
	bool operator>(const Real& num1, const int num2)
	{
		if (num1.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_si(num1.number, num2) > 0;
	}

	/**
	 * Greater-than comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than to the second.
	 */
	bool operator>(const int num1, const Real& num2)
	{
		Real _num1(num2.GetBitPrecision(), num1);

		return _num1 > num2;
	}

	/**
	 * Greater-than comparison operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than to the second.
	 */
	bool operator>(const Real& num1, const float num2)
	{
		if (num1.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_d(num1.number, num2) > 0;
	}

	/**
	 * Greater-than comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than to the second.
	 */
	bool operator>(const float num1, const Real& num2)
	{
		Real _num1(num2.GetBitPrecision(), num1);

		return _num1 > num2;
	}

	/**
	 * Greater-than-or-equal comparison operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than or equal to the second.
	 */
	bool operator>=(const Real& num1, const Real& num2)
	{
		if (num1.IsNaN() || num2.IsNaN())
			throw MathException(Overflow);

		return mpfr_greaterequal_p(num1.number, num2.number) != 0;
	}

	/**
	 * Greater-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than or equal to the second.
	 */
	bool operator>=(const Real& num1, const int num2)
	{
		return (num1 > num2) || (num1 == num2);
	}

	/**
	 * Greater-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than or equal to the second.
	 */
	bool operator>=(const int num1, const Real& num2)
	{
		return (num1 > num2) || (num1 == num2);
	}

	/**
	 * Greater-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than or equal to the second.
	 */
	bool operator>=(const Real& num1, const float num2)
	{
		return (num1 > num2) || (num1 == num2);
	}

	/**
	 * Greater-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is greater than or equal to the second.
	 */
	bool operator>=(const float num1, const Real& num2)
	{
		return (num1 > num2) || (num1 == num2);
	}

	/**
	 * Less-than comparison operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than the second.
	 */
	bool operator<(const Real& num1, const Real& num2)
	{
		if (num1.IsNaN() || num2.IsNaN())
			throw MathException(Overflow);

		return mpfr_less_p(num1.number, num2.number) != 0;
	}

	/**
	 * Less-than comparison operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than the second.
	 */
	bool operator<(const Real& num1, const int num2)
	{
		if (num1.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_si(num1.number, num2) < 0;
	}

	/**
	 * Less-than comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than the second.
	 */
	bool operator<(const int num1, const Real& num2)
	{
		Real _num1(num2.GetBitPrecision(), num1);

		return _num1 < num2;
	}

	/**
	 * Less-than comparison operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than the second.
	 */
	bool operator<(const Real& num1, const float num2)
	{
		if (num1.IsNaN())
			throw MathException(Overflow);

		return mpfr_cmp_d(num1.number, num2) < 0;
	}

	/**
	 * Less-than comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than the second.
	 */
	bool operator<(const float num1, const Real& num2)
	{
		Real _num1(num2.GetBitPrecision(), num1);

		return _num1 < num2;
	}

	/**
	 * Less-than-or-equal comparison operator.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than or equal to the second.
	 */
	bool operator<=(const Real& num1, const Real& num2)
	{
		if (num1.IsNaN() || num2.IsNaN())
			throw MathException(Overflow);

		return mpfr_lessequal_p(num1.number, num2.number) != 0;
	}

	/**
	 * Less-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than or equal to the second.
	 */
	bool operator<=(const Real& num1, const int num2)
	{
		return (num1 < num2) || (num1 == num2);
	}

	/**
	 * Less-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than or equal to the second.
	 */
	bool operator<=(const int num1, const Real& num2)
	{
		return (num1 < num2) || (num1 == num2);
	}

	/**
	 * Less-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than or equal to the second.
	 */
	bool operator<=(const Real& num1, const float num2)
	{
		return (num1 < num2) || (num1 == num2);
	}

	/**
	 * Less-than-or-equal comparison operator.
	 * @param num1 The first instance to compare.
	 * @param num2 The second instance to compare.
	 * @return true if the first parameter is less than or equal to the second.
	 */
	bool operator<=(const float num1, const Real& num2)
	{
		return (num1 < num2) || (num1 == num2);
	}

	/**
	 * Exponent function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num The argument.
	 * @return The number raised to the exponent.
	 */
	Real exp(const Real& num)
	{
		Real res(num.GetBitPrecision());

		while (mpfr_exp(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		//mpfr_exp(res.number, num.number, DEFAULT_RND);

		return res;
	}

	/**
	 * Natural logarithm function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num The argument.
	 * @return The natural logarithm of the number.
	 */
	Real ln(const Real& num)
	{
		Real res(num.GetBitPrecision());

		while (mpfr_log(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		//mpfr_log(res.number, num.number, DEFAULT_RND);

		return res;
	}

	/**
	 * Base 10 logarithm function.
	 * @param num The argument.
	 * @return Base 10 logarithm of the number.
	 */
	Real lg(const Real& num)
	{
		Real res = ln(num) / ln(Real(num.GetBitPrecision(), 10));

		return res;
	}

	/**
	 * Logarithm with base function.
	 * @param num1 The base.
	 * @param num2 The argument.
	 * @return Logarithm with base of the number.
	 */
	Real log(const Real& num1, const Real& num2)
	{
		Real res = ln(num2) / ln(num1);

		return res;
	}

	/**
	 * Sine function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The sinus of the number.
	 */
	Real sin(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (angleMeasure != RADIAN)
		{
			Real _num(num.GetBitPrecision());

			if (angleMeasure == DEGREE)
				_num = num.DegreeToRadian();
			else if (angleMeasure == GRAD)
				_num = num.GradToRadian();

			while (mpfr_sin(res.number, _num.number, DEFAULT_RND) < 0)
			{
				if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
					throw MathException(Overflow);

				res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
			}

			return res;
		}

		Real misc = MathHelper::GetMisc<Real>(num);
		Real _pi = pi(num.GetBitPrecision());
		Real pi2 = pi(num.GetBitPrecision()) * 2;

		Real _num = num;
		Real mul = round(_num / pi2);

		_num -= mul * pi2;
		_num = abs(_num);

		if (_num <= misc)
		{
			res = 0;
		}
		else if (abs(_num - _pi) <= misc)
		{
			res = 0;
		}
		else
		{
			while (mpfr_sin(res.number, num.number, DEFAULT_RND) < 0)
			{
				if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
					throw MathException(Overflow);

				res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
			}
		}

		return res;
	}

	/**
	 * Cosine function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The cosine of the number.
	 */
	Real cos(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (angleMeasure != RADIAN)
		{
			Real _num(num.GetBitPrecision());

			if (angleMeasure == DEGREE)
				_num = num.DegreeToRadian();
			else if (angleMeasure == GRAD)
				_num = num.GradToRadian();

			while (mpfr_cos(res.number, _num.number, DEFAULT_RND) < 0)
			{
				if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
					throw MathException(Overflow);

				res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
			}

			return res;
		}

		Real _pi = pi(num.GetBitPrecision());
		Real pi2 = pi(num.GetBitPrecision()) * 2;

		Real mul = round(num / pi2);
		Real _num = num;

		_num -= mul * pi2;
		_num = abs(_num);

		if (_num == 0)
		{
			res = 1;
		}
		else if (_num == _pi)
		{
			res = -1;
		}
		else if (_num == _pi / 2)
		{
			res = 0;
		}
		else if (_num == 3 * _pi / 2)
		{
			res = 0;
		}
		else
		{
			while (mpfr_cos(res.number, num.number, DEFAULT_RND) < 0)
			{
				if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
					throw MathException(Overflow);

				res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
			}
		}

		return res;
	}

	/**
	 * Tangent function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The tangent of the number.
	 */
	Real tg(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (angleMeasure != RADIAN)
		{
			Real _num(num.GetBitPrecision());

			if (angleMeasure == DEGREE)
				_num = num.DegreeToRadian();
			else if (angleMeasure == GRAD)
				_num = num.GradToRadian();

			while (mpfr_tan(res.number, _num.number, DEFAULT_RND) < 0)
			{
				if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
					throw MathException(Overflow);

				res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
			}

			return res;
		}

		while (mpfr_tan(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		return res;
	}

	/**
	 * Cotangent function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The cotangent of the number.
	 */
	Real ctg(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (angleMeasure != RADIAN)
		{
			Real _num(num.GetBitPrecision());

			if (angleMeasure == DEGREE)
				_num = num.DegreeToRadian();
			else if (angleMeasure == GRAD)
				_num = num.GradToRadian();

			while (mpfr_cot(res.number, _num.number, DEFAULT_RND) < 0)
			{
				if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
					throw MathException(Overflow);

				res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
			}

			return res;
		}

		while (mpfr_cot(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		return res;
	}

	/**
	 * Secant function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The secant of the number.
	 */
	Real sec(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (angleMeasure != RADIAN)
		{
			Real _num(num.GetBitPrecision());

			if (angleMeasure == DEGREE)
				_num = num.DegreeToRadian();
			else if (angleMeasure == GRAD)
				_num = num.GradToRadian();

			while (mpfr_sec(res.number, _num.number, DEFAULT_RND) < 0)
			{
				if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
					throw MathException(Overflow);

				res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
			}

			return res;
		}

		while (mpfr_sec(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Cosecant function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The cosecant of the number.
	 */
	Real cosec(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (angleMeasure != RADIAN)
		{
			Real _num(num.GetBitPrecision());

			if (angleMeasure == DEGREE)
				_num = num.DegreeToRadian();
			else if (angleMeasure == GRAD)
				_num = num.GradToRadian();

			while (mpfr_csc(res.number, _num.number, DEFAULT_RND) < 0)
			{
				if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
					throw MathException(Overflow);

				res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
			}

			return res;
		}

		while (mpfr_csc(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Arcsine function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The arcsine of the number.
	 */
	Real arcsin(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (abs(num) > 1)
			throw MathException(Overflow);

		while (mpfr_asin(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		if (angleMeasure == DEGREE)
			res = res.RadianToDegree();
		else if (angleMeasure == GRAD)
			res = res.RadianToGrad();

		return res;
	}

	/**
	 * Arccosine function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The arccosine of the number.
	 */
	Real arccos(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (abs(num) > 1)
			throw MathException(Overflow);

		while (mpfr_acos(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		if (angleMeasure == DEGREE)
			res = res.RadianToDegree();
		else if (angleMeasure == GRAD)
			res = res.RadianToGrad();

		return res;
	}

	/**
	 * Arctangent function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The arctangent of the number.
	 */
	Real arctg(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		while (mpfr_atan(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		if (angleMeasure == DEGREE)
			res = res.RadianToDegree();
		else if (angleMeasure == GRAD)
			res = res.RadianToGrad();

		return res;
	}

	/**
	 * Arccotangent function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The arccotangent of the number.
	 */
	Real arcctg(const Real& num, AngleMeasure angleMeasure)
	{
		Real _pi = pi(num.GetBitPrecision());

		if (angleMeasure == DEGREE)
			_pi = _pi.RadianToDegree();
		else if (angleMeasure == GRAD)
			_pi = _pi.RadianToGrad();

		Real res(_pi / 2 - arctg(num, angleMeasure));

		return res;
	}

	/**
	 * Arcsecant function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The arcsecant of the number.
	 */
	Real arcsec(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(arccos(1 / num, angleMeasure));

		return res;
	}

	/**
	 * Acrcosecant function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The arccosecant of the number.
	 */
	Real arccosec(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(arcsin(1 / num, angleMeasure));

		return res;
	}

	/**
	 * Hyperbolic sine function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The hyperbolic sine of the number.
	 */
	Real sh(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (angleMeasure != RADIAN)
		{
			Real _num(num.GetBitPrecision());

			if (angleMeasure == DEGREE)
				_num = num.DegreeToRadian();
			else if (angleMeasure == GRAD)
				_num = num.GradToRadian();

			while (mpfr_sinh(res.number, _num.number, DEFAULT_RND) < 0)
			{
				if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
					throw MathException(Overflow);

				res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
			}

			//mpfr_sinh(res.number, _num.number, DEFAULT_RND);

			return res;
		}

		while (mpfr_sinh(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		//mpfr_sinh(res.number, num.number, DEFAULT_RND);

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		return res;
	}

	/**
	 * Hyperbolic cosine function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The hyperbolic cosine of the number.
	 */
	Real ch(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (angleMeasure != RADIAN)
		{
			Real _num(num.GetBitPrecision());

			if (angleMeasure == DEGREE)
				_num = num.DegreeToRadian();
			else if (angleMeasure == GRAD)
				_num = num.GradToRadian();

			while (mpfr_cosh(res.number, _num.number, DEFAULT_RND) < 0)
			{
				if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
					throw MathException(Overflow);

				res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
			}

			//mpfr_cosh(res.number, _num.number, DEFAULT_RND);

			return res;
		}

		while (mpfr_cosh(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		//mpfr_cosh(res.number, num.number, DEFAULT_RND);

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		return res;
	}

	/**
	 * Hyperbolic tangent function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The hyperbolic tangent of the number.
	 */
	Real th(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (angleMeasure != RADIAN)
		{
			Real _num(num.GetBitPrecision());

			if (angleMeasure == DEGREE)
				_num = num.DegreeToRadian();
			else if (angleMeasure == GRAD)
				_num = num.GradToRadian();

			while (mpfr_tanh(res.number, _num.number, DEFAULT_RND) < 0)
			{
				if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
					throw MathException(Overflow);

				res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
			}

			//mpfr_tanh(res.number, _num.number, DEFAULT_RND);

			return res;
		}

		while (mpfr_tanh(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		//mpfr_tanh(res.number, num.number, DEFAULT_RND);

		return res;
	}

	/**
	 * Hyperbolic cotangent function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The hyperbolic cotangent of the number.
	 */
	Real cth(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (angleMeasure != RADIAN)
		{
			Real _num(num.GetBitPrecision());

			if (angleMeasure == DEGREE)
				_num = num.DegreeToRadian();
			else if (angleMeasure == GRAD)
				_num = num.GradToRadian();

			while (mpfr_coth(res.number, _num.number, DEFAULT_RND) < 0)
			{
				if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
					throw MathException(Overflow);

				res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
			}

			//mpfr_coth(res.number, _num.number, DEFAULT_RND);

			return res;
		}

		while (mpfr_coth(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		//mpfr_coth(res.number, num.number, DEFAULT_RND);

		return res;
	}

	/**
	 * Hyperbolic secant function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The hyperbolic secant of the number.
	 */
	Real sch(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (angleMeasure != RADIAN)
		{
			Real _num(num.GetBitPrecision());

			if (angleMeasure == DEGREE)
				_num = num.DegreeToRadian();
			else if (angleMeasure == GRAD)
				_num = num.GradToRadian();

			mpfr_sech(res.number, _num.number, DEFAULT_RND);

			return res;
		}

		mpfr_sech(res.number, num.number, DEFAULT_RND);

		return res;
	}

	/**
	 * Hyperbolic cosecant function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The hyperbolic cosecant of the number.
	 */
	Real csch(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		if (angleMeasure != RADIAN)
		{
			Real _num(num.GetBitPrecision());

			if (angleMeasure == DEGREE)
				_num = num.DegreeToRadian();
			else if (angleMeasure == GRAD)
				_num = num.GradToRadian();

			mpfr_csch(res.number, _num.number, DEFAULT_RND);

			return res;
		}

		mpfr_csch(res.number, num.number, DEFAULT_RND);

		return res;
	}

	/**
	 * Hyperbolic arcsine function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The hyperbolic arcsine of the number.
	 */
	Real arsh(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		mpfr_asinh(res.number, num.number, DEFAULT_RND);

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		if (angleMeasure == DEGREE)
			res = res.RadianToDegree();
		else if (angleMeasure == GRAD)
			res = res.RadianToGrad();

		return res;
	}

	/**
	 * Hyperbolic arccosine function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The hyperbolic arccosine of the number.
	 */
	Real arch(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		mpfr_acosh(res.number, num.number, DEFAULT_RND);

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		if (angleMeasure == DEGREE)
			res = res.RadianToDegree();
		else if (angleMeasure == GRAD)
			res = res.RadianToGrad();

		return res;
	}

	/**
	 * Hyperbolic arctangent function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The hyperbolic arctangent of the number.
	 */
	Real arth(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		mpfr_atanh(res.number, num.number, DEFAULT_RND);

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		if (angleMeasure == DEGREE)
			res = res.RadianToDegree();
		else if (angleMeasure == GRAD)
			res = res.RadianToGrad();

		return res;
	}

	/**
	 * Hyperbolic arccotangent function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The hyperbolic arccotangent of the number.
	 */
	Real arcth(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		//res = (ln((num + 1) / (num - 1))) / 2;
		res = arth(1 / num, angleMeasure);

		if (angleMeasure == DEGREE)
			res = res.RadianToDegree();
		else if (angleMeasure == GRAD)
			res = res.RadianToGrad();

		return res;
	}

	/**
	 * Hyperbolic arcsecant function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The hyperbolic arcsecant of the number.
	 */
	Real arsch(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		//res = ln(sqrt((1 / num) - 1) * sqrt((1 / num) + 1) + (1 / num));
		res = arch(1 / num, angleMeasure);

		if (angleMeasure == DEGREE)
			res = res.RadianToDegree();
		else if (angleMeasure == GRAD)
			res = res.RadianToGrad();

		return res;
	}

	/**
	 * Hyperbolic arccosecant function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The hyperbolic arccosecant of the number.
	 */
	Real arcsch(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num.GetBitPrecision());

		//res = ln(sqrt(1 + 1 / sqr(num)) + 1 / num);
		res = arsh(1 / num, angleMeasure);

		if (angleMeasure == DEGREE)
			res = res.RadianToDegree();
		else if (angleMeasure == GRAD)
			res = res.RadianToGrad();

		return res;
	}

	/**
	 * Pow function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 Base.
	 * @param num2 Exponent.
	 * @return Base raised to exponent.
	 */
	Real pow(const Real& num1, const Real& num2)
	{
		Real res(max(num1.GetBitPrecision() + 2, num2.GetBitPrecision() + 2));

		while (mpfr_pow(res.number, num1.number, num2.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		if (res.IsInfinity() || res.IsNaN())
			throw MathException(Overflow);

		res.Round(max(num1.GetBitPrecision(), num2.GetBitPrecision()));

		return res;
	}

	/**
	 * Power function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 Base.
	 * @param num2 Exponent.
	 * @return Base raised to exponent.
	 */
	Real pow(const Real& num1, const int num2)
	{
		Real res(num1.GetBitPrecision());

		while (mpfr_pow_si(res.number, num1.number, num2, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Power function with exponent 2.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num1 Base.
	 * @return Base raised to exponent 2.
	 */
	Real sqr(const Real& num)
	{
		Real res(num.GetBitPrecision());

		while (mpfr_sqr(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Square root function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num The argument.
	 * @return The square root of the number.
	 */
	Real sqrt(const Real& num)
	{
		Real res(num.GetBitPrecision());

		while (mpfr_sqrt(res.number, num.number, DEFAULT_RND) < 0)
		{
			if (res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION >= MPFR_PREC_MAX)
				throw MathException(Overflow);

			res.SetBitPrecision(res.GetBitPrecision() + DEFAULT_INCREASE_PRECISION);
		}

		return res;
	}

	/**
	 * Nth root function.
	 * @param num1 The argument.
	 * @param num2 The degree.
	 * @return The nth root of the number.
	 */
	Real root(const Real& num1, const Real& num2)
	{
		Real res(pow(num1, 1 / num2));

		return res;
	}

	/**
	 * Absolute number function.
	 * @param num The argument.
	 * @return Absolute value.
	 */
	Real abs(const Real& num)
	{
		Real res(num.GetBitPrecision());

		mpfr_abs(res.number, num.number, DEFAULT_RND);

		return res;
	}

	/**
	 * Rounds to to the next lower or equal representable integer.
	 * @param num The argument.
	 * @return The rounded number.
	 */
	Real floor(const Real& num)
	{
		Real res(num.GetBitPrecision());

		mpfr_floor(res.number, num.number);

		return res;
	}

	/**
	 * Fractional part of number.
	 * @param num The argument.
	 * @return The fractional part of the number.
	 */
	Real fract(const Real& num)
	{
		Real res(num.GetBitPrecision());

		mpfr_frac(res.number, num.number, DEFAULT_RND);

		return res;
	}

	/**
	 * Rounds to the next representable integer toward zero.
	 * @param num The argument.
	 * @return The rounded number.
	 */
	Real trunc(const Real& num)
	{
		Real res(num.GetBitPrecision());

		mpfr_trunc(res.number, num.number);

		return res;
	}

	/**
	 * Rounds to the next higher or equal representable integer.
	 * @param num The argument.
	 * @return The rounded number.
	 */
	Real ceil(const Real& num)
	{
		Real res(num.GetBitPrecision());

		mpfr_ceil(res.number, num.number);

		return res;
	}

	/**
	 * Rounds to the nearest representable integer.
	 * @param num The argument.
	 * @return The rounded number.
	 */
	Real round(const Real& num)
	{
		Real res(num.GetBitPrecision());

		mpfr_round(res.number, num.number);

		return res;
	}

	/**
	 * Gets integer of the number.
	 * @param num The argument.
	 * @return The integer.
	 */
	Real integer(const Real& num)
	{
		return trunc(num);
	}

	/**
	 * Gets fraction of the number.
	 * @param num The argument.
	 * @return The fraction.
	 */
	Real fraction(const Real& num)
	{
		return fract(num);
	}

	/**
	 * Factorial function.
	 * @exception MathException Thrown when the mathematics error condition occurs.
	 * @param num The argument.
	 * @return The factorial of the number.
	 */
	Real fact(const Real& num)
	{
		Real res(num.GetBitPrecision());

		if (!num.IsInteger())
			throw MathException(ArgumentIsOver);

		mpfr_fac_ui(res.number, (int)num, DEFAULT_RND);

		return res;
	}

	/**
	 * Rounds to the nearest representable integer.
	 * @param num The argument.
	 * @return The rounded number.
	 */
	Real roundoff(const Real& num)
	{
		Real res(num.GetBitPrecision());

		mpfr_round(res.number, num.number);

		return res;
	}

	/**
	 * Exponent constant.
	 * @param precision The precision.
	 * @return The exponent constant.
	 */
	Real exp(const int precision)
	{
		return exp(Real(precision, 1));
	}

	/**
	 * pi constant.
	 * @param precision The precision.
	 * @return The pi constant.
	 */
	Real pi(const int precision)
	{
		Real res(precision);

		mpfr_const_pi(res.number, DEFAULT_RND);

		return res;
	}

	/**
	 * Converts degree to radian.
	 * @return The result of the conversion.
	 */
	Real Real::DegreeToRadian() const
	{
		Real res = pi(GetBitPrecision()) / 180 * *this;

		return res;
	}

	/**
	 * Converts radian to degree.
	 * @return The result of the conversion.
	 */
	Real Real::RadianToDegree() const
	{
		Real res = 180 / pi(GetBitPrecision()) * *this;

		return res;
	}

	/**
	 * Converts grad to radian.
	 * @return The result of the conversion.
	 */
	Real Real::GradToRadian() const
	{
		Real res = pi(GetBitPrecision()) / 180 * *this * (float)0.9;

		return res;
	}

	/**
	 * Converts radian to grad.
	 * @return The result of the conversion.
	 */
	Real Real::RadianToGrad() const
	{
		Real res = 180 / pi(GetBitPrecision()) * *this * (float)0.9;

		return res;
	}

	/**
	 * Converts degree to grad.
	 * @return The result of the conversion.
	 */
	Real Real::DegreeToGrad() const
	{
		Real res = *this / (float)0.9;

		return res;
	}

	/**
	 * Converts grad to degree.
	 * @return The result of the conversion.
	 */
	Real Real::GradToDegree() const
	{
		Real res = *this * (float)0.9;

		return res;
	}

	/**
	 * Converts rad to an angle measure.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The result of the conversion.
	 */
	Real rad(const Real& num, AngleMeasure angleMeasure)
	{
		Real res(num);

		switch (angleMeasure)
		{
		case DEGREE:
			res = res.RadianToDegree();
			break;
		case GRAD:
			res = res.RadianToGrad();
			break;
		}

		return res;
	}

	/**
	 * Converts degree to an angle measure.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The result of the conversion.
	 */
	Real degree(const Real& num, AngleMeasure angleMeasure)
	{
		Real res = num;

		switch (angleMeasure)
		{
		case RADIAN:
			res = res.DegreeToRadian();
			break;
		case GRAD:
			res = res.DegreeToGrad();
			break;
		}

		return res;
	}

	/**
	 * Converts degree minutes to an angle measure.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The result of the conversion.
	 */
	Real minute(const Real& num, AngleMeasure angleMeasure)
	{
		Real res = num;

		switch (angleMeasure)
		{
		case RADIAN:
			res /= 60;
			res = res.DegreeToRadian();
			break;
		case DEGREE:
			res /=60;
			break;
		case GRAD:
			res /= 60;
			res = res.DegreeToGrad();
			break;
		}

		return res;
	}

	/**
	 * Converts degree seconds to an angle measure.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The result of the conversion.
	 */
	Real second(const Real& num, AngleMeasure angleMeasure)
	{
		Real res = num;

		switch (angleMeasure)
		{
		case RADIAN:
			res /= 3600;
			res = res.DegreeToRadian();
			break;
		case DEGREE:
			res /= 3600;
			break;
		case GRAD:
			res /= 3600;
			res = res.DegreeToGrad();
			break;
		}

		return res;
	}

	/**
	 * Converts grad to an angle measure.
	 * @param num	The argument.
	 * @param angleMeasure The angle measure.
	 * @return The result of the conversion.
	 */
	Real grad(const Real& num, AngleMeasure angleMeasure)
	{
		Real res = num;

		switch (angleMeasure)
		{
		case RADIAN:
			res = res.GradToRadian();
			break;
		case DEGREE:
			res = res.GradToDegree();
			break;
		}

		return res;
	}

	/**
	 * Gets the precision.
	 * @return The precision.
	 */
	int Real::GetPrecision() const
	{
		return MathHelper::ToDecimalPrecision(GetBitPrecision());
	}

	/**
	 * Sets a precision.
	 * @param precision The precision.
	 */
	void Real::SetPrecision(int precision)
	{
		if (stringNumber.empty())
			SetBitPrecision(max((int)mpfr_get_default_prec(), MathHelper::ToBitPrecision(precision + 2)));
		else
		{
			SetBitPrecision(max((int)mpfr_get_default_prec(), MathHelper::ToBitPrecision(precision + 2)));
			//renew the number because of not being precios getting by string
			mpfr_set_str(number, stringNumber.c_str(), DEFAULT_BASE, MPFR_RNDA);
		}
		//SetBitPrecision(MathHelper::ToBitPrecision(precision + addPrecision + 1));

	#ifdef TRACE_OUTPUT
		UpdateNumberStr();
	#endif
	}

	/**
	 * Raises the precision.
	 */
	void Real::RaisePrecision()
	{
		SetPrecision(GetPrecision() + 1);
	}

	/**
	 * Sets lower precision.
	 */
	void Real::LowerPrecision()
	{
		SetPrecision(GetPrecision() - 1);
	}

	/**
	 * Sets lower precision.
	 * @param prec The prec.
	 */
	void Real::LowerPrecision(int prec)
	{
		if (GetBitPrecision() <= MathHelper::ToBitPrecision(prec))
			return;

		SetPrecision(prec);
	}

	/**
	 * Convert this number into a plain string representation.
	 * @return A string representation of this number.
	 */
	string Real::ToString() const
	{
		std::ostringstream s;
		mp_exp_t exp;

		char* c_str = mpfr_get_str(NULL, &exp, DEFAULT_BASE, 0, number, DEFAULT_RND);

		--exp;

		if (c_str == NULL)
			return "";

		if (mpfr_number_p(number))
		{
			if (c_str[0] != '-')
				s << std::string(c_str).insert(1, 1, '.');
			else
				s << std::string(c_str).insert(2, 1, '.');
		}
		else
			s << std::string(c_str);

		mpfr_free_str(c_str);

		if (IsNumber() && !IsZero())
		{
			s << 'e';

			if (exp < 0)
				s << '-';
			else
				s << '+';

			if (std::abs(exp) < 10)
				s << '0';

			s << std::abs(exp);
		}

		string res = s.str();

		return res;
	}

	/**
	 * Convert this number into a string representation.
	 * @param exp The exponent.
	 * @param accuracy The accuracy.
	 * @param [in,out] mantissaSign The mantissa sign.
	 * @param [in,out] mantissa	The mantissa.
	 * @param [in,out] exponentSign The exponent sign.
	 * @param [in,out] exponent	The exponent.
	 */
	void Real::ToString(int exp, int accuracy, bool& mantissaSign, string& mantissa, bool& exponentSign, string& exponent) const
	{
		Real res(abs(*this));
		char* numStr;
		mp_exp_t numExp;
		char buf[20];

		mantissaSign = GetSign();
		exponentSign = false;

		assert(accuracy >= 1);

		if (IsNaN() || IsInfinity())
			return;

		numStr = mpfr_get_str(NULL, &numExp, 10, accuracy + 1, number, DEFAULT_RND);

		if (numExp >= 0 && exp >= numExp)
		{
			mpfr_free_str(numStr);
			numStr = mpfr_get_str(NULL, &numExp, 10, numExp + accuracy, number, DEFAULT_RND);
		}
		else if (exp > ::abs(numExp))
		{
			mpfr_free_str(numStr);
			numStr = mpfr_get_str(NULL, &numExp, 10, accuracy, number, DEFAULT_RND);
		}

		mantissa = numStr;
		mpfr_free_str(numStr);

		if (mantissaSign)
			mantissa.erase(0, 1);

		if (res >= 1)
		{
			if (numExp > exp)
			{
				mantissa.insert(1, 1, '.');

				--numExp;
				_itoa_s(numExp, buf, 10);
				exponent = buf;
			}
			else
			{
				mantissa.insert(numExp, 1, '.');
				exponent = "";
			}
		}
		else
		{
			if (IsZero())
			{
				mantissa = "0.";
				exponent = "";
				return;
			}

			int i = ::abs(numExp);

			if (numExp <= 0)
			{
				while (i < (int)mantissa.size() - 1 && mantissa[i] == '0')
					++i;

				if (i >= exp)
				{
					mantissa.insert(1, 1, '.');

					--numExp;
					if (numExp < 0)
						exponentSign = true;

					if (numExp != 0)
					{
						_itoa_s(::abs(numExp), buf, 10);
						exponent = buf;
					}
					else
						exponent = "";
				}
				else
				{
					mantissa.insert(0, 1, '0');
					mantissa.insert(1, 1, '.');

					if (numExp < 0)
						mantissa.insert(2, ::abs(numExp), '0');

					exponent = "";
				}
			}
			else
			{
				mantissa.insert(1, 1, '.');

				--numExp;
				if (numExp < 0)
					exponentSign = true;

				if (numExp != 0)
				{
					_itoa_s(::abs(numExp), buf, 10);
					exponent = buf;
				}
				else
					exponent = "";
			}
		}

		for (int i = mantissa.size() - 1; i > 0; --i)
		{
			if (mantissa[i] == '.')
				break;
			if (mantissa[i] == '0')
				mantissa.erase(i, 1);
			else
				break;
		}
	}

#ifdef _DEBUG
	/**
	 * Convert this number into a string representation.
	 * @param exp	The exponent.
	 * @param accuracy The accuracy.
	 * @return A string representation of this number.
	 */
	string Real::ToString(int exp, int accuracy) const
	{
		bool mantissaSign;
		string mantissa;
		bool exponentSign;
		string exponent;
		
		ToString(exp, accuracy, mantissaSign, mantissa, exponentSign, exponent);
		
		string res;
		res += mantissaSign ? "-" : "";
		res += mantissa;
		res += "E";
		res += exponentSign ? "-" : "+";
		res += exponent.empty() ? "0" : exponent;
		
		return res;
	}
#endif

	/**
	 * Gets the number.
	 * @return The number.
	 */
	Real Real::GetNumber()
	{
		Real res(*this);

		return res;
	}

	//int Real::GetPrecision() const
	//{
	//	return MathHelper::ToDecimalPrecision(GetBitPrecision());
	//}

	//void Real::SetPrecision(int precision)
	//{
	//	//'precision' in this case means digits count after the point, so we need to add the leading digit
	//	SetBitPrecision(MathHelper::ToBitPrecision(precision + 1));

	//#ifdef TRACE_OUTPUT
	//	UpdateNumberStr();
	//#endif
	//}

	//string Real::ToString() const
	//{
	//	char buf[100];
	//	
	//	gmp_sprintf(buf, "%.Fe", number);
	//	int p = mpf_get_prec(number);
	//	
	//	return string(buf);
	//	
	//	//std::ostringstream s;
	//	//mp_exp_t exp;

	//	//char* c_str = mpf_get_str(NULL, &exp, DEFAULT_BASE, 0, number);

	//	//--exp;

	//	//if (c_str == NULL)
	//	//	return "";

	//	////if (mpf_number_p(number))
	//	////{
	//	////	if (c_str[0] != '-')
	//	////		s << string(c_str).insert(1, 1, '.');
	//	////	else
	//	////		s << string(c_str).insert(2, 1, '.');
	//	////}
	//	////else
	//	//	s << string(c_str);

	//	////mpf_free_str(c_str);
	//	//free_function(c_str);

	//	////if (IsNumber() && !IsZero())
	//	//{
	//	//	s << 'e';

	//	//	if (exp < 0)
	//	//		s << '-';
	//	//	else
	//	//		s << '+';

	//	//	if (std::abs(exp) < 10)
	//	//		s << '0';

	//	//	s << std::abs(exp);
	//	//}

	//	//string res = s.str();

	//	//return res;
	//}

#ifdef TRACE_OUTPUT
	/**
	 * Updates the numberStr field.
	 */
	void Real::UpdateNumberStr()
	{
		numberStr = ToString();
	}
#endif
}
