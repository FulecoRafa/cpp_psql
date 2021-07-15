#ifndef HOTEL
#define HOTEL

#include <string>
#include <pqxx/pqxx>
#include "connection.cpp"

namespace hotel {
  pqxx::result search(std::string& field, std::string& query) {
    return conn::work.exec("select * from hotel where lower(" + field + ") like lower('" + query + "%')");
  }

  std::string print(pqxx::row& obj) {
    return std::string() + "# " + obj["nome"].c_str() +
      "\nCadastro Nacional: " + obj["cadastro_nacional"].c_str() +
      "\nTelefone: " + obj["telefone"].c_str() +
      "\nEndereço: " + obj["logradouro"].c_str() + ", número " + obj["numero"].c_str() +
      "\n          " + obj["codigo_postal"].c_str() + ", " + obj["cidade"].c_str() + ", " + obj["pais"].c_str();
  }
}

#endif // HOTEL
