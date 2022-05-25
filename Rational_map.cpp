#include <iostream>
#include <map>
#include <set>
#include <vector>
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

bool operator>(const Rational& lhs, const Rational& rhs) {
    if (lhs.Denominator() == rhs.Denominator()) {
        return lhs.Numerator() > rhs.Numerator();
    }
    return lhs.Numerator() * rhs.Denominator() > rhs.Numerator() * lhs.Denominator();
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    if (lhs.Denominator() == rhs.Denominator()) {
        return lhs.Numerator() < rhs.Numerator();
    }
    return lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator();
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}