#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <sstream>
#include <set>
#include <iomanip>

using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
public:
  Date() {
    year = 1;
    month = 1;
    day = 1;
  }
  Date(const int& new_year, const int& new_month, const int& new_day) {
    year = new_year;
    try {
      if (new_month >= 1 && new_month <= 12) {
        month = new_month;
        try {
          if (new_day >= 1 && new_day <= 31) {
            day = new_day;
          } else {
            throw domain_error(to_string(new_day));
          }
        } catch (domain_error& exc) {
          cout << "Day value is invalid: " << exc.what() << endl;
        }
      } else {
        throw length_error(to_string(new_month));
      }
    } catch (length_error& ex) {
      cout << "Month value is invalid: " << ex.what() << endl;
    }
  }
  int GetYear() const {
    return year;
  }
  int GetMonth() const {
    return month;
  }
  int GetDay() const {
    return day;
  }
private:
  int year;
  int month;
  int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() == rhs.GetYear()) {
    if (lhs.GetMonth() == rhs.GetMonth()) {
      return lhs.GetDay() < rhs.GetDay();
    }
    return lhs.GetMonth() < rhs.GetMonth();
  }
  return lhs.GetYear() < rhs.GetYear();
}

bool operator==(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay()) {
    return true;
  }
  return false;
}

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
    database[date].insert(event);
  }
  bool DeleteEvent(const Date& date, const string& event) {
    for (auto& item : database) {
      if (item.first == date) {
        for (auto& ev : item.second) {
          if (ev == event) {
            item.second.erase(ev);
            if (database[date].size() == 0) {
              database.erase(date);
            }
            return true;
          }
        }
      }
    }
    return false;
  }
  int  DeleteDate(const Date& date) {
    int number = 0;
    if (database.count(date) > 0) {
      number = database[date].size();
      database.erase(date);
    }
    return number;
  }

  set<string> Find(const Date& date) const {
    set<string> events;
    if (database.count(date)) {
      for (const auto& item : database.at(date)) {
        events.insert(item);
      }
    }
    return events;
  }
  
  void Print() const {
    for (const auto& item : database) {
      for (const auto& e : item.second) {      
        cout << setw(4) << setfill('0') << item.first.GetYear() << '-'
             << setw(2) << setfill('0') << item.first.GetMonth() << '-'
             << setw(2) << setfill('0') << item.first.GetDay();
        cout << ' ' << e << endl;
      }
    }
  }
private:
  map<Date, set<string>> database;
};

int EnsureNextSymbols(stringstream& stream) {
  int number;
  if (stream.peek() != '-') {
    throw invalid_argument("");
  } else {
    stream.ignore(1);
    if (stream.peek() == '-') {
      stream.ignore(1);
      if (stream.peek() >= '0' && stream.peek() <= '9') {
        stream >> number;
        number = -number;
        //throw domain_error(to_string(number));
      }
    } else if (stream.peek() == '+') {
      stream.ignore(1);
      if (stream.peek() >= '0' && stream.peek() <= '9') {
        stream >> number;
        return number;
      } else {
        throw invalid_argument("");
      }
    } else if (stream.peek() >= '0' && stream.peek() <= '9') {
      stream >> number;
      return number;
    }
  }
}

Date ParseDate(const string& date_str) {
  stringstream stream(date_str);
  Date date;
  int year, month, day;
  stream >> year;
  month = EnsureNextSymbols(stream);
  day = EnsureNextSymbols(stream);
  if (stream.peek() != -1) {
    throw invalid_argument("");
  }
  date = Date(year, month, day);
  return date;
}

int main() {
  Database db;
  Date d;
  string e, d_s;
    
  string command;
  while (getline(cin, command)) {
    // Считайте команды с потока ввода и обработайте каждую
    stringstream ss(command);
    string cmd;
    ss >> cmd;
    try {
      if (cmd == "Add") {
        try {
          ss >> d_s >> e;
          d = ParseDate(d_s);
          db.AddEvent(d, e);
        } catch (invalid_argument&) {
          cout << "Wrong date format: " << d_s << endl;
          return 0;
        }
      } else if (cmd == "Del") {
        try {
          ss >> d_s;
          d = ParseDate(d_s);
        } catch (invalid_argument&) {
          cout << "Wrong date format: " << d_s << endl;
          return 0;
        }
        ss.ignore(1);
        if (ss.peek() != -1) {
          //ss.ignore(1);
          ss >> e;
          if (db.DeleteEvent(d, e)) {
            cout << "Deleted successfully" << endl;
          } else {
            cout << "Event not found" << endl;
          }
        } else {
          cout << "Deleted " << db.DeleteDate(d) << " events" << endl;          
        }
      } else if (cmd == "Find") {
        try {
          ss >> d_s;
          d = ParseDate(d_s);
        } catch (invalid_argument&) {
          cout << "Wrong date format: " << d_s << endl;
          return 0;
        }
        set<string> eve = db.Find(d);
        for (auto& item : eve) {
          cout << item;
          int i = 1;
          if (i < eve.size()) {
            cout << ' ';
          }
          cout << endl;
        }
      } else if (cmd == "Print") {
        db.Print();
      } else if (cmd == "") {

      } else {
        throw out_of_range("");
      }
    } catch (out_of_range&) {
      cout << "Unknown command: " << cmd << endl;
      return 0;
    }
  }

  return 0;
}

/*
1) Add Дата Событие
  - неверная комманда
  - неверный формат ввода даты
  - месяц < 1 или > 12
  - если месяц корректен, день < 1 или > 31
2) Del Дата Событие
3) Del Дата
4) Find Дата
5) Print
*/