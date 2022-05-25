#include <iostream>
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

bool operator==(const Rational& lhs, const Rational& rhs) {
    if (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator()) {
        return true;
    } else {
        return false;
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
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    {
        istringstream input("2/4/6/8");
        Rational r1;
        input >> r1;
        bool correct = r1 == Rational(1, 2);
        if (!correct) {
            cout << "Multiple-slashed number sequence value read incorrectly: " << r1 << endl;
            return 7;
        }
    }

    cout << "OK" << endl;
    return 0;
}