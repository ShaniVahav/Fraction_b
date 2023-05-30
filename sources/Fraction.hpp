//
// Created by shani on 20/04/2023.
//

#ifndef FRACTION_A_FRACTION_H
#define FRACTION_A_FRACTION_H

#include <iostream>
using namespace std;
namespace ariel{}

class Fraction {
public:
    Fraction(double num = 0.0, double den = 1.0)
    {
        if(den == 0){
            throw invalid_argument("Cannot divide by zero!");
        }

        this->toSimpleFrac(num, den);  // num and den are updated in this function
    }

    friend Fraction operator+ (Fraction frac1, Fraction frac2);
    friend Fraction operator- (Fraction frac1, Fraction frac2);
    friend Fraction operator* (Fraction frac1, Fraction frac2);
    friend Fraction operator/ (Fraction frac1, Fraction frac2);
    const Fraction operator++ (int);
    Fraction& operator++ ();
    const Fraction operator-- (int);
    Fraction& operator-- ();
    friend bool operator!= (Fraction frac1, Fraction frac2);
    friend bool operator== (Fraction frac1, Fraction frac2);
    friend bool operator> (Fraction frac1, Fraction frac2);
    friend bool operator>= (Fraction frac1, Fraction frac2);
    friend bool operator< (Fraction frac1, Fraction frac2);
    friend bool operator<= (Fraction frac1, Fraction frac2);
    friend ostream& operator<< (ostream& output, Fraction& frac);
    friend istream& operator>> (istream& input, Fraction& frac);

    void toSimpleFrac(double num, double den); // convert to num/den fraction
    pair<long, long> reducedForm(long long num, long long den);  // gcd

    int getNumerator() const{return this->_num;}
    int getDenominator() const{return this->_den;}

private:
    int _num{};  // numerator
    int _den{};  // denominator
};


#endif //FRACTION_A_FRACTION_H
