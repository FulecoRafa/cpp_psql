#ifndef SELECTOR
#define SELECTOR

#include <pqxx/pqxx>
#include <iostream>
#include <string>

#include "print.cpp"
#include "formatter.cpp"

namespace interact {
  std::string prompt(std::string msg) {
    std::string answer;
    std::cout << msg;
    std::cin >> answer;
    return answer;
  }

  pqxx::row select_one(const pqxx::result& list) {
    int index = 0;
    system("/bin/stty raw");
    while (true) {
      // printf("\r\n");
      system("clear");
      for (int i = 0; i < list.size(); i++) {
        if (index == i)
          pinfo("> %s\r\n", format::row_to_string(list[i]).c_str());
        else
          printf("  %s\r\n", format::row_to_string(list[i]).c_str());
      }
      char option = getchar();
      if (option == 'w') index = (index + 1) % list.size();
      else if (option == 's') index = (index - 1) % list.size();
      else if (option == ' ') break;
    }
    printf("\r");
    system("/bin/stty cooked");
    return list[index];
  }
}

#endif // SELECTOR
