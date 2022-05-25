#include <iostream>
#include <sstream>
#include <exception>
#include <string>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

class Date {
public:
  Date() {
    year = 1;
    month = 1;
    day = 1;
  }
  Date(const int& new_year, const int& new_month, const int& new_day) {
    year = new_year;
    if (new_month < 1 || new_month > 12) {
      throw invalid_argument("Month value is invalid: " + to_string(new_month));
    } else {
      month = new_month;
    }
    if (new_day < 1 || new_day > 31) {
      throw invalid_argument("Day value is invalid: " + to_string(new_day));
    } else {
      day = new_day;
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

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
    database[date].insert(event);
  }
  bool DeleteEvent(const Date& date, const string& event) {
    if(database[date].count(event) > 0) {
      database[date].erase(event);
      return true;
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
    if (database.count(date) > 0) {
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

int EnsureNextSymbol(istream& stream) {
  int number;
  if (stream.peek() != '-') {
    throw runtime_error("");
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
        throw runtime_error("");
      }
    } else if (stream.peek() == -1) {
      throw runtime_error("");
    } else if (stream.peek() >= '0' && stream.peek() <= '9') {
      stream >> number;
      return number;
    }
  }
}

istream& operator>>(istream& in, Date& date) {
  string input;
  in >> input;
  stringstream stream(input);
  int year, month, day;
  try {
    stream >> year;
    month = EnsureNextSymbol(stream);
    day = EnsureNextSymbol(stream);
    if (stream.peek() != -1) {
      throw runtime_error("");
    }
  } catch (runtime_error& re) {
    throw runtime_error("Wrong date format: " + input);
  }
  date = Date(year, month, day);
  return in;
}

int main() {
  Database db;
    
  string command;
  while (getline(cin, command)) {
    stringstream stream(command);
    string cmd;
    stream >> cmd;
    try {
      if (cmd == "Add") {
        Date date;
        try {
          stream >> date;
        } catch (exception& ex) {
          cout << ex.what() << endl;
          break;
        }
        string event;
        stream >> event;
        db.AddEvent(date, event);
      } else if (cmd == "Del") {
        Date date;
        try {
          stream >> date;
        } catch (exception& ex) {
          cout << ex.what() << endl;
          break;
        }
        stream.ignore(1);
        if (stream.peek() != -1) {
          string event;
          stream >> event;
          if (db.DeleteEvent(date, event)) {
            cout << "Deleted successfully" << endl;
          } else {
            cout << "Event not found" << endl;
          }
        } else {
          cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
        }
      } else if (cmd == "Find") {
        Date date;
        try {
          stream >> date;
        } catch (exception& ex) {
          cout << ex.what() << endl;
          break;
        }
        set<string> events = db.Find(date);
        for (const auto& item : events) {
          cout << item << endl;
        }
      } else if (cmd == "Print") {
        db.Print();
      } else if (cmd == "") {

      } else {
        throw runtime_error("Unknown command: " + cmd);
      } 
    } catch (exception& ex) {
      cout << ex.what() << endl;
      break;
    }
  }

  return 0;
}