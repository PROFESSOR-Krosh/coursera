#include <iostream>
using namespace std;

class Rational {
public:
    Rational() {
        numer = 0;
        denom = 1;
    }

    Rational(int numerator, int denominator) {
        numer = numerator;
        denom = denominator;
        if (numer == 0) {
            denom = 1;
        } else {
            int sign = 1;
            if (numer < 0 && denom > 0) {
                numer *= -1;
                sign = -1;
            } else if (numer > 0 && denom < 0) {
                denom *= -1;
                sign = -1;
            } else if (numer < 0 && denom < 0) {
                numer *= -1;
                denom *= -1;
            }
            int a = numer, b = denom;
            while (a > 0 && b > 0) {
                if (a > b) {
                    a = a % b;
                } else {
                    b = b % a;
                }
            }
            numer = numer / (a + b);
            if (sign == -1) {
                numer *= -1;
            }
            denom = denom / (a + b);
        }
    }

    int Numerator() const {
        return numer;
    }

    int Denominator() const {
        return denom;
    }

private:
    int numer;
    int denom;
};

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, -6);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != 2/3" << endl;
            cout << r.Numerator() << '/' << r.Denominator() << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            cout << r.Numerator() << ' ' << r.Denominator() << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}