#ifndef REAL_H
#define REAL_H

#include <string>
#include <mpfr.h>
#include "MathHelper.h"
#include "ParserException.h"

using namespace std;

namespace BigNumbersParser
{
	/**
	 * Real number.
	 */
	class Real
	{
	public:
		Real();
		explicit Real(int precision);
		explicit Real(int precision, const char* num);
		explicit Real(int precision, int num);
		explicit Real(int precision, float num);
		Real(const string& num);
		Real(const Real& source);
		~Real();

	public:
		typedef Real value_type;
		
		Real& operator=(const Real& num);
		Real& operator=(const int num);
		Real& operator=(const double num);
		Real& operator=(const char* source);
		Real& operator=(const string& num);

		Real operator+();
		Real operator-();

		Real operator++();
		Real operator--();

		friend Real operator+(const Real& num1, const Real& num2);
		friend Real operator+(const Real& num1, const int num2);
		friend Real operator+(const int num1, const Real& num2);
		friend Real operator+(const Real& num1, const float num2);
		friend Real operator+(const float num1, const Real& num2);

		friend Real operator-(const Real& num1, const Real& num2);
		friend Real operator-(const Real& num1, const int num2);
		friend Real operator-(const int num1, const Real& num2);
		friend Real operator-(const Real& num1, const float num2);
		friend Real operator-(const float num1, const Real& num2);

		friend Real operator*(const Real& num1, const Real& num2);
		friend Real operator*(const Real& num1, const int num2);
		friend Real operator*(const int num1, const Real& num2);
		friend Real operator*(const Real& num1, const float num2);
		friend Real operator*(const float num1, const Real& num2);

		friend Real operator/(const Real& num1, const Real& num2);
		friend Real operator/(const Real& num1, const int num2);
		friend Real operator/(const int num1, const Real& num2);
		friend Real operator/(const Real& num1, const float num2);
		friend Real operator/(const float num1, const Real& num2);

		void operator+=(const Real& num);
		void operator+=(const int num);
		void operator+=(const float num);

		void operator-=(const Real& num);
		void operator-=(const int num);
		void operator-=(const float num);

		void operator*=(const Real& num);
		void operator*=(const int num);
		void operator*=(const float num);

		void operator/=(const Real& num);
		void operator/=(const int num);
		void operator/=(const float num);

	public:
		operator int() const;

	public:
		friend bool operator==(const Real& num1, const Real& num2);
		friend bool operator==(const Real& num1, const int num2);
		friend bool operator==(const int num1, const Real& num2);
		friend bool operator==(const Real& num1, const float num2);
		friend bool operator==(const float num1, const Real& num2);
		friend bool operator==(const Real& num1, const double num2);
		friend bool operator==(const double num1, const Real& num2);
		friend bool operator==(const Real& num1, const char* num2);
		friend bool operator==(const char* num1, const Real& num2);

		friend bool operator!=(const Real& num1, const Real& num2);
		friend bool operator!=(const Real& num1, const int num2);
		friend bool operator!=(const int num1, const Real& num2);
		friend bool operator!=(const Real& num1, const float num2);
		friend bool operator!=(const float num1, const Real& num2);

		friend bool operator>(const Real& num1, const Real& num2);
		friend bool operator>(const Real& num1, const int num2);
		friend bool operator>(const int num1, const Real& num2);
		friend bool operator>(const Real& num1, const float num2);
		friend bool operator>(const float num1, const Real& num2);

		friend bool operator>=(const Real& num1, const Real& num2);
		friend bool operator>=(const Real& num1, const int num2);
		friend bool operator>=(const int num1, const Real& num2);
		friend bool operator>=(const Real& num1, const float num2);
		friend bool operator>=(const float num1, const Real& num2);

		friend bool operator<(const Real& num1, const Real& num2);
		friend bool operator<(const Real& num1, const int num2);
		friend bool operator<(const int num1, const Real& num2);
		friend bool operator<(const Real& num1, const float num2);
		friend bool operator<(const float num1, const Real& num2);

		friend bool operator<=(const Real& num1, const Real& num2);
		friend bool operator<=(const Real& num1, const int num2);
		friend bool operator<=(const int num1, const Real& num2);
		friend bool operator<=(const Real& num1, const float num2);
		friend bool operator<=(const float num1, const Real& num2);

	public:
		friend Real exp(const Real& num);

		friend Real ln(const Real& num);
		friend Real lg(const Real& num);
		friend Real log(const Real& num1, const Real& num2);

		friend Real sin(const Real& num, AngleMeasure angleMeasure);

		friend Real cos(const Real& num, AngleMeasure angleMeasure);

		friend Real tg(const Real& num, AngleMeasure angleMeasure);

		friend Real ctg(const Real& num, AngleMeasure angleMeasure);

		friend Real sec(const Real& num, AngleMeasure angleMeasure);

		friend Real cosec(const Real& num, AngleMeasure angleMeasure);

		friend Real arcsin(const Real& num, AngleMeasure angleMeasure);

		friend Real arccos(const Real& num, AngleMeasure angleMeasure);

		friend Real arctg(const Real& num, AngleMeasure angleMeasure);

		friend Real arcctg(const Real& num, AngleMeasure angleMeasure);

		friend Real arcsec(const Real& num, AngleMeasure angleMeasure);

		friend Real arccosec(const Real& num, AngleMeasure angleMeasure);

		friend Real sh(const Real& num, AngleMeasure angleMeasure);

		friend Real ch(const Real& num, AngleMeasure angleMeasure);

		friend Real th(const Real& num, AngleMeasure angleMeasure);

		friend Real cth(const Real& num, AngleMeasure angleMeasure);

		friend Real sch(const Real& num, AngleMeasure angleMeasure);

		friend Real csch(const Real& num, AngleMeasure angleMeasure);

		friend Real arsh(const Real& num, AngleMeasure angleMeasure);

		friend Real arch(const Real& num, AngleMeasure angleMeasure);

		friend Real arth(const Real& num, AngleMeasure angleMeasure);

		friend Real arcth(const Real& num, AngleMeasure angleMeasure);

		friend Real arsch(const Real& num, AngleMeasure angleMeasure);

		friend Real arcsch(const Real& num, AngleMeasure angleMeasure);

		friend Real pow(const Real& num1, const Real& num2);

		friend Real pow(const Real& num1, const int num2);

		//friend Real pow(const Real& num1, const int num2, ParserExpression* pExpression);

		friend Real sqr(const Real& num);

		friend Real sqrt(const Real& num);

		friend Real root(const Real& num1, const Real& num2);

		friend Real abs(const Real& num);

		friend Real floor(const Real& num);

		friend Real trunc(const Real& num);

		friend Real fract(const Real& num);

		friend Real ceil(const Real& num);

		friend Real round(const Real& num);

		friend Real integer(const Real& num);

		friend Real fraction(const Real& num);

		friend Real fact(const Real& num);

		friend Real roundoff(const Real& num);

	public:
		friend Real exp(const int precision);
		friend Real pi(const int precision);

	public:
		Real DegreeToRadian() const;
		Real RadianToDegree() const;

		Real GradToRadian() const;
		Real RadianToGrad() const;

		Real DegreeToGrad() const;
		Real GradToDegree() const;

		friend Real rad(const Real& num, AngleMeasure angleMeasure);
		friend Real degree(const Real& num, AngleMeasure angleMeasure);
		friend Real minute(const Real& num, AngleMeasure angleMeasure);
		friend Real second(const Real& num, AngleMeasure angleMeasure);
		friend Real grad(const Real& num, AngleMeasure angleMeasure);

	public:
		bool IsNumber() const
		{
			return mpfr_number_p(number) != 0;
		}

		bool IsZero() const
		{
			return mpfr_zero_p(number) != 0;
		}

		bool IsInfinity() const
		{
			return mpfr_inf_p(number) != 0;
		}

		bool IsInteger() const
		{
			return mpfr_integer_p(number) != 0;
		}

		bool IsNaN() const
		{
			return mpfr_nan_p(number) != 0;
		}

		void SetNaN()
		{
			mpfr_set_nan(number);
		}
		
		bool GetSign() const
		{
			return mpfr_signbit(number);
		}

		int GetExp() const
		{
			mp_exp_t exp;
			mpfr_get_str(NULL, &exp, DEFAULT_BASE, 0, number, DEFAULT_RND);

			return exp - 1;
		}

		void SetExp(int exp)
		{
			//int curExp = GetExp();

			//if (curExp > exp)
			//	*this /= (float)pow(10., curExp - exp);
			//else if (curExp < exp)
			//	*this *= (float)pow(10., exp - curExp);

#ifdef TRACE_OUTPUT
			UpdateNumberStr();
#endif
		}

		int GetBitPrecision() const
		{
			return mpfr_get_prec(number);
		}

		void SetBitPrecision(const int precision)
		{
			//mpfr_prec_round(number, max((int)mpfr_get_default_prec(), precision), DEFAULT_RND);
			mpfr_prec_round(number, precision, DEFAULT_RND);

#ifdef TRACE_OUTPUT
			UpdateNumberStr();
#endif
		}

		int GetPrecision() const;
		void SetPrecision(int precision);

		void RaisePrecision();
		void LowerPrecision();
		void LowerPrecision(int prec);

		Real& Round(int prec)
		{
			mpfr_prec_round(number, prec, GMP_RNDN);

	#ifdef TRACE_OUTPUT
			UpdateNumberStr();
	#endif

			return *this;
		}

	public:
		string ToString() const;
		void ToString(int exp, int accuracy, bool& mantissaSign, string& mantissa, bool& exponentSign, string& exponent) const;
		
#ifdef _DEBUG
		string ToString(int exp, int accuracy) const;
#endif

		Real GetNumber();

	private:
		mpfr_t number;	///< The number
		//int addPrecision;
		string stringNumber;

#ifdef TRACE_OUTPUT
	void UpdateNumberStr();

	string numberStr; ///< The string representation of the number for debug purposes.
#endif
	};
}

#endif
