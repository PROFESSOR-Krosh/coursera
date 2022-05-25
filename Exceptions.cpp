#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <exception>

using namespace std;

struct Date {
	int year;
	int month;
	int day;
};

void EnsureNextSymbolAndSkip(stringstream& stream) {
	if (stream.peek() != '/') {
		// Исключение; Ошибка передается в main
		stringstream ss;
		ss << "expected / , but has: " << char(stream.peek());
		throw runtime_error(ss.str());
	}
	stream.ignore(1);
}

Date ParseDate(const string& s) {
	stringstream stream(s);
	Date date;
	stream >> date.year;
	EnsureNextSymbolAndSkip(stream);
	stream >> date.month;
	EnsureNextSymbolAndSkip(stream);
	stream >> date.day;
	return date;
}

/* Обработка ошибки
try {
	...
} catch (exception&) {
	...
}*/

int main() {
	string date_str = "2017a01/25";
	try {
		// опасный код
		Date date = ParseDate(date_str);
		cout << setw(2) << setfill('0') << date.day << '.'
			 << setw(2) << setfill('0') << date.month << '.'
		 	 << date.year << endl;		
	} catch (exception& ex) {
		// обработка ошибки
		cout << "exception happens: " << ex.what();
		// ex.what() - возвращает текст ошибки
	}
	return 0;
}