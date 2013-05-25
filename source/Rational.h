#ifndef RATIONAL_H
#define RATIONAL_H

#include <string>
#include <mpir.h>
#include "MathHelper.h"
#include "Integer.h"

using namespace std;

namespace BigNumbersParser
{
	/**
	 * Rational number.
	 */
	class Rational
	{
	public:
		Rational();
		Rational(const Rational& source);
		Rational(const int num);
		Rational(const int precision, const double num);
		Rational(const int precision, const int num);
		Rational(const string& num);
		~Rational();
		
	public:
		Rational& operator=(const Rational& source);
		Rational& operator=(const string& source);
		
		Rational operator+();
		Rational operator-();

		friend Rational operator+(const Rational& num1, const Rational& num2);
		friend Rational operator+(const Rational& num1, const int num2);
		friend Rational operator+(const int num1, const Rational& num2);

		friend Rational operator-(const Rational& num1, const Rational& num2);
		friend Rational operator-(const Rational& num1, const int num2);
		friend Rational operator-(const int num1, const Rational& num2);

		friend Rational operator*(const Rational& num1, const Rational& num2);
		friend Rational operator*(const Rational& num1, const int num2);
		friend Rational operator*(const int num1, const Rational& num2);

		friend Rational operator/(const Rational& num1, const Rational& num2);
		friend Rational operator/(const Rational& num1, const int num2);
		friend Rational operator/(const int num1, const Rational& num2);

	public:
		void operator+=(const Rational& num);

	public:
		friend bool operator==(const Rational& num1, const Rational& num2);
		friend bool operator==(const Rational& num1, const int num2);
		friend bool operator==(const int num1, const Rational& num2);

		friend bool operator!=(const Rational& num1, const Rational& num2);
		friend bool operator!=(const Rational& num1, const int num2);
		friend bool operator!=(const int num1, const Rational& num2);

		friend bool operator>(const Rational& num1, const Rational& num2);
		friend bool operator>(const Rational& num1, const int num2);
		friend bool operator>(const int num1, const Rational& num2);

		friend bool operator>=(const Rational& num1, const Rational& num2);
		friend bool operator>=(const Rational& num1, const int num2);
		friend bool operator>=(const int num1, const Rational& num2);

		friend bool operator<(const Rational& num1, const Rational& num2);
		friend bool operator<(const Rational& num1, const int num2);
		friend bool operator<(const int num1, const Rational& num2);

		friend bool operator<=(const Rational& num1, const Rational& num2);
		friend bool operator<=(const Rational& num1, const int num2);
		friend bool operator<=(const int num1, const Rational& num2);

	public:
		Integer GetNumerator();
		Integer GetDenomerator();
	
		string ToString() const;

		int GetPrecision() const
		{
			return 0;
		}

		void SetPrecision(int precision)
		{
		}

		void SetBitPrecision(const int precision)
		{
		}
		
	private:
	#ifdef TRACE_OUTPUT
		void UpdateNumberStr();
	#endif
		
	private:
		mpq_t number; ///< The number 

	#ifdef TRACE_OUTPUT
		string numberStr; ///< The string representation of the number for debug purposes
	#endif
	};
}

#endif
