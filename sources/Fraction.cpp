//
// Created by shani on 20/04/2023.
//

/// Class that represents a fraction, defined by two 'int' type values - num and den.
/// The class overloads all relevant operators to perform arithmetic with fractions.
/// The operators work with double types too, for both operands.

#include <algorithm>  // __gcd
#include <limits>
#include "Fraction.hpp"
using namespace std;

double EPS = std::numeric_limits<double>::epsilon();

int max_int = std::numeric_limits<int>::max();
int min_int = std::numeric_limits<int>::min();

int lcm(int a, int b) {
    return (a * b) / __gcd(a, b);
}

void overflow_check(double num){
    if(num > max_int){
        throw overflow_error("Overflow detected - number too big");
    }
    if (num < min_int){
        throw overflow_error("Overflow detected - number too small");
    }
}


Fraction operator+ (const Fraction frac1, const Fraction frac2)
{
    /// create new simple frac with common denominator
    double new_den = lcm(frac1._den, frac2._den);
    overflow_check(new_den);

    double num1 = new_den/frac1._den * frac1._num;
    double num2 = new_den/frac2._den * frac2._num;

    double new_num = num1 + num2;
    overflow_check(new_num);

    return Fraction{new_num, new_den};
}

Fraction operator- (const Fraction frac1, const Fraction frac2){
    /// create new simple frac with common denominator
    double new_den = lcm(frac1._den, frac2._den);
    overflow_check(new_den);

    double num1 = new_den/frac1._den * frac1._num;
    double num2 = new_den/frac2._den * frac2._num;


    double new_num = num1 - num2;
    overflow_check(new_num);

    return {new_num ,new_den};
}


Fraction operator* (const Fraction frac1, const Fraction frac2){
    double new_den = (long long) frac1._den * (long long) frac2._den;
    overflow_check(new_den);

    double new_num = (long long) frac1._num * (long long) frac2._num;
    overflow_check(new_num);

    return Fraction{new_num, new_den};
}


Fraction operator/ (const Fraction frac1, const Fraction frac2)
{
    if(frac2._num == 0){  // frac2 = 0
        throw std::runtime_error("Can not divide by zero!");
    }

    double new_den = (long long) frac1._den * (long long) frac2._num;
    overflow_check(new_den);

    double new_num = (long long) frac1._num * (long long) frac2._den;
    overflow_check(new_num);

    return {new_num, new_den};
}


const Fraction Fraction::operator++ (int)  // f++
{
    // first use the frac -> then increase
    Fraction copy(this->_num, this->_den);  // deep copy
    *this = *this + 1;
    return copy;
}

Fraction& Fraction::operator++ ()  // ++f
{
    // first increase the frac -> then use
    *this = *this + 1;
    return *this;
}

const Fraction Fraction::operator-- (int)  // f--
{
    // first use the frac -> then increase
    Fraction copy(this->_num, this->_den);  // deep copy
    *this = *this - 1;
    return copy;
}

Fraction& Fraction::operator-- () // --f
{
    // first increase the frac -> then use
    *this = *this - 1;
    return *this;
}

bool operator!= (Fraction frac1, Fraction frac2)
{
    bool eq_num = frac1._num != frac2._num;
    bool eq_den = frac1._den != frac2._den;

    return eq_num || eq_den;
}

bool operator== (Fraction frac1, Fraction frac2)
{
    bool eq_num = frac1._num == frac2._num;
    bool eq_den = frac1._den == frac2._den;

    return eq_num && eq_den;
}

bool operator> (Fraction frac1, Fraction frac2)
{
    Fraction f = frac1 - frac2;
    bool result = f._num > 0 && f._den > 0;

    return result;
}

bool operator>= (Fraction frac1, Fraction frac2)
{
    Fraction f = frac1 - frac2;
    bool result = f._num >= 0;  // no need to check positively for 'den' the minus sign is always on 'num'

    return  result;
}

bool operator< (Fraction frac1, Fraction frac2)
{
    Fraction f = frac1 - frac2;
    bool result = f._num < 0;  // no need to check positively for 'den' the minus sign is always on 'num'

    return  result;
}

bool operator<= (Fraction frac1, Fraction frac2)
{
    Fraction f = frac1 - frac2;
    bool result = f._num <= 0;

    return  result;
}

ostream& operator<< (ostream& os, Fraction& frac)
{
    os << frac._num << '/' << frac._den;
    return os;
}

istream& operator>> (istream& is, Fraction& frac)
{
    double num, den = 0;  // initialize
    is >> num >> den;

    // if num or den is not integers
    if(static_cast<long>(num) != num || static_cast<long>(den) != den){
        throw runtime_error("floating-point input");
    }

    // cant divide by zero
    if(den == 0){
        throw runtime_error("Cannot divide by zero!");
    }

    frac = Fraction(num, den);

    return is;
}


void Fraction::toSimpleFrac(double num, double den){
    /// find numerator and denominator of the simple frac
    num = num * (1 + EPS);  // to prevent information loss

    // 3 digits at most
    num = num * 1000;
    den = den * 1000;
    // the integers part of num and den are wanted

    /// create the reduced form
    pair<long, long> result = reducedForm(num, den);  // the integers part of num and den are the arguments

    this->_num = result.first;
    this->_den = result.second;
}

pair<long, long> Fraction::reducedForm(long long num, long long den){
    /// change _num, _den accordingly to simple fraction _num/_den
    long long gcd = __gcd(num, den);  // the greatest common divisor
    num = num/gcd;
    den = den/gcd;

    // the minus is wanted at numerator
    if(den < 0 && num > 0){
        num *= -1;
        den *= -1;
    }

    return make_pair(num, den);
}


