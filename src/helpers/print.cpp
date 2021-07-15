#ifndef PRINT
#define PRINT

#include <string>

#define pinfo(format, ...) printf("\033[34m" format "\033[0m", ##__VA_ARGS__)
#define perror(format, ...) printf("\033[31m" format "\033[0m", ##__VA_ARGS__)
#define todo() perror("Not yet implemented\n"); exit(1);

namespace print{
  std::string month_num_to_word(int num) {		// codigo para formatacao de datas de forma mais amigavel ao usuario
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

  std::string date(std::string date) {
    std::string day = date.substr(8, 2);
    std::string month = month_num_to_word(date.substr(5, 2));
    std::string year = date.substr(0, 4);
    return std::string() +
      day + " de " + month + " de " + year;
  }

  std::string time(std::string time) {
    std::string hm = time.substr(0, 5);
    int i_hm = std::stoi(hm);
    if (i_hm > 12) {
      return std::to_string(i_hm - 12) + hm.substr(2, 3) + " PM";
    } else {
      return hm + " AM";
    }
  }
}

#endif // PRINT
