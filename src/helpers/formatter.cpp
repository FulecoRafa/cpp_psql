#ifndef FORMATTER
#define FORMATTER

#include <string>
#include <pqxx/pqxx>
#include <sstream>

namespace format {    
  std::string row_to_string(pqxx::row row) {    // normaliza o tamanho das strings recebidas para 60 caracteres introduzindo "..." ate este limite e truncando o excesso
    std::stringstream ss;
    ss << row[0].c_str();
    for (int i = 1; i < row.size(); i++) {
      if (ss.str().size() > 60) {
        ss << "...";
        break;
      }
      ss << ", " << row[i].c_str();
    }
    return ss.str();
  }
}

#endif // FORMATTER
