#ifndef MONUMENTO
#define MONUMENTO

#include <string>
#include <pqxx/pqxx>
#include "connection.cpp"
#include "destino.cpp"

namespace monumento {
  std::vector<std::string> fields{ "cidade", "nome" };

  pqxx::result search(std::string& field, std::string& query) {
    return conn::work.exec("select * from monumento where lower(" + field + ") like lower('" + query + "%')");
  }

  void add(pqxx::row& destino, std::string nome, std::string descricao = "") {
    conn::work.exec(std::string() +
      "insert into monumento values ('" +
      nome +
      "', '" +
      destino["cidade"].c_str() +
      "', '" +
      destino["pais"].c_str() +
      "', " +
      (descricao.empty() ? "null" : ("'" + descricao + "'")) +
      ")"
    );
  }

  std::string print(pqxx::row& obj) {
    std::string dest = destino::print(obj);
    return std::string() + obj["nome"].c_str() + " situado em " + dest +
      "\nDescrição: " + obj["descricao"].c_str();
  }
}

#endif // MONUMENTO
