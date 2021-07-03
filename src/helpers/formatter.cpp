#ifndef FORMATTER
#define FORMATTER

#include <string>
#include <pqxx/pqxx>
#include <sstream>

namespace format {
  std::string row_to_string(pqxx::row row) {
    std::stringstream ss;
    ss << row[0].c_str();
    for (int i = 1; i < row.size(); i++)
      ss << ", " << row[i].c_str();
    return ss.str();
  }
}

#endif // FORMATTER
