#include <iostream>
#include <exception>
#include <sstream>
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
        if (denom == 0) {
            throw invalid_argument("Invalid argument");
        } else if (numer == 0) {
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

int Nok(const int& ld, const int& rd) {
    int nok, a = ld, b = rd;
    while (a > 0 && b > 0) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }
    nok = ld * rd / (a + b);
    return nok;
}

int Numer(const int& n, const int& nok, const int& d) {
    return (n * nok / d);
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    if (lhs.Denominator() == rhs.Denominator()) {
        return Rational(lhs.Numerator() + rhs.Numerator(), lhs.Denominator());
    } else {
        int nok, lnumer, rnumer;
        nok = Nok(lhs.Denominator(), rhs.Denominator());
        lnumer = Numer(lhs.Numerator(), nok, lhs.Denominator());
        rnumer = Numer(rhs.Numerator(), nok, rhs.Denominator());
        return Rational(lnumer + rnumer, nok);
    }
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    if (lhs.Denominator() == rhs.Denominator()) {
        return Rational(lhs.Numerator() - rhs.Numerator(), lhs.Denominator());
    } else {
        int nok, lnumer, rnumer;
        nok = Nok(lhs.Denominator(), rhs.Denominator());
        lnumer = Numer(lhs.Numerator(), nok, lhs.Denominator());
        rnumer = Numer(rhs.Numerator(), nok, rhs.Denominator());
        return Rational(lnumer - rnumer, nok);
    }
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    if (rhs.Numerator() == 0) {
        throw domain_error("Division by zero");
    } else {
        return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
    }
}

istream& operator>>(istream& stream, Rational& rational) {
    int p, q;
    char i;
    if(stream >> p && stream >> i && stream >> q && i == '/') {
        rational = { p, q};
    }
    return stream;
}

ostream& operator<<(ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << '/' << rational.Denominator();
    return stream;
}

int main() {
    Rational r1, r2;
    char o;
    try {
        cin >> r1 >> o >> r2;
        if (o == '+') {
            cout << r1 + r2 << endl;
        } else if (o == '-') {
            cout << r1 - r2 << endl;
        } else if (o == '*') {
            cout << r1 * r2 << endl;
        } else if (o == '/') {
            try {
                cout << r1 / r2 << endl;   
            } catch (domain_error& e) {
                cout << e.what() << endl;
            }
        }
    } catch (invalid_argument& e) {
        cout << e.what() << endl;
    }
    return 0;
}