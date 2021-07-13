#ifndef CHECK
#define CHECK

#include <string>

namespace check {
  bool is_number (char c) {
    return c >= '0' || c <= '9';
  }

  bool is_date (std::string s) {
    if (s.length() <= 10) return false;
      for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
          if (s[i] != '-') {
            return false;
          }
        } else {
          if (!is_number(s[i])) {
              return false;
          }
        }
      }
    return true;
  }
}

#endif // CHECK
