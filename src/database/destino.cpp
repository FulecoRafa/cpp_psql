#ifndef DESTINO
#define DESTINO

#include <string>
#include "connection.cpp"

namespace destino {
pqxx::result search(std::string& city_name) {
  return conn::work.exec("select * from destino where lower(cidade) like lower('" + city_name + "%')");
}

std::string print(pqxx::row &obj) {
  return std::string() + obj["cidade"].c_str() + "[" + obj["pais"].c_str() + "]";
}
}

#endif // DESTINO
