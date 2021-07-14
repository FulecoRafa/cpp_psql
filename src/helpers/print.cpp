#ifndef PRINT
#define PRINT

#include <string>

#define pinfo(format, ...) printf("\033[34m" format "\033[0m", ##__VA_ARGS__)
#define perror(format, ...) printf("\033[31m" format "\033[0m", ##__VA_ARGS__)
#define todo() perror("Not yet implemented"); exit(1);

namespace print{
  std::string month_num_to_word(int num) {
    std::string months[] = {
      "Janeiro",
      "Fevereiro",
      "Março",
      "Abril",
      "Maio",
      "Junho",
      "Julho",
      "Agosto",
      "Setembro",
      "Outubro",
      "Novembro",
      "Dezembro"
    };
    return months[num-1];
  }
  std::string month_num_to_word(std::string num) {
    return month_num_to_word(std::stoi(num));
  }

  std::string print_date(std::string date) {
    std::string day = date.substr(8, 2);
    std::string month = month_num_to_word(date.substr(5, 2));
    std::string year = date.substr(0, 4);
    return std::string() +
      day + " de " + month + " de " + year;
  }
}

#endif // PRINT
