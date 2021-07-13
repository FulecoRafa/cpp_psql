#ifndef MONUMENTO
#define MONUMENTO

#include <string>
#include <pqxx/pqxx>
#include "connection.cpp"
#include "destino.cpp"

namespace monumento {
  pqxx::result search(std::string& field, std::string& query) {
    return conn::work.exec("select * from monumento where lower(" + field + ") like lower('" + query + "%')");
  }

  std::string print(pqxx::row& obj) {
    std::string dest = destino::print(obj);
    return std::string() + obj["nome"].c_str() + " situado em " + dest +
      "\nDescrição: " + obj["descricao"].c_str();
  }
}

#endif // MONUMENTO
