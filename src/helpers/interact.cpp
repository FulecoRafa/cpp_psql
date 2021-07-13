#ifndef SELECTOR
#define SELECTOR

#include <cstdio>
#include <ostream>
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

  int opt_one(std::string prompt, const std::vector<std::string>& list) {   
    int index = 0;
    system("/bin/stty raw");
    while (true) {
      system("clear");
      std::cout << prompt << "\r\n";
      for (int i = 0; i < list.size(); i++) {
        if (index == i)
          pinfo("> %s\r\n", list[i].c_str());
        else
          printf("  %s\r\n", list[i].c_str());
      }
      char option = getchar();
      if (option == 'w') index = (index - 1 < 0 ? list.size() : index) - 1;
      else if (option == 's') index = (index + 1) % list.size();
      else if (option == ' ') break;
    }
    printf("\r");
    system("/bin/stty cooked");
    return index;
  }

  std::string opt_one_string(std::string prompt, const std::vector<std::string>& list) {
    return list[opt_one(prompt, list)];
  }

  pqxx::row select_one(const pqxx::result& list) {
    if (list.size() == 1) {
      return list[0];
    }
    int index = 0;
    system("/bin/stty raw");
    while (true) {
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

  void wait(bool is_space) {    // retorna o programa quando o usuario pressiona ENTER
    std::cin.clear();
    if (is_space) {
      std::fflush(stdin);
    } else {
      while(std::cin.get() != '\n');
    }
    std::cout << "\nPress ENTER to continue ";
    while(std::cin.get() != '\n');
  }
}

#endif // SELECTOR
