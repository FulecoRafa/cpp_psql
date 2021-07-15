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
    std::getline(std::cin, answer, '\n');
    return answer;
  }

  std::string password(std::string msg) {
    std::string answer;
    std::cout << msg << "\033[30;40;5m";
    std::getline(std::cin, answer, '\n');
    std::cout << "\033[0m\n";
    system("clear");
    return answer;
  }

  int opt_one(std::string prompt, const std::vector<std::string>& list) {   // cria um menu interativo com opcoes para o usuario selecionar 
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
      if (option == 'w') index = (index - 1 < 0 ? list.size() : index) - 1;   // navegacao do menu com W e S
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
    int s = list.size();
    int index = 0;
    system("/bin/stty raw");
    while (true) {
      system("clear");
      for (int i = 0; i < s; i++) {
        if (index == i)
          pinfo("> %s\r\n", format::row_to_string(list[i]).c_str());
        else
          printf("  %s\r\n", format::row_to_string(list[i]).c_str());
      }
      char option = getchar();
      if (option == 'w') index = (index - 1 < 0 ? s : index) - 1;     // mais navegacao de menus
      else if (option == 's') index = (index + 1) % s;
      else if (option == ' ') break;
    }
    printf("\r");
    system("/bin/stty cooked");
    return list[index];
  }

<<<<<<< HEAD

=======
  void wait() {
    std::fflush(stdin);
>>>>>>> master
    std::cout << "\nPress ENTER to continue ";
    while(std::cin.get() != '\n');
  }
}

#endif // SELECTOR
