#ifndef OBRA
#define OBRA

#include <string>
#include <pqxx/pqxx>
#include "connection.cpp"
#include "../helpers/print.cpp"

namespace obra {
  pqxx::result search(std::string& field, std::string& query) {
    return conn::work.exec("select * from (select o.*, m.nome as m_nome from obra o"
        " join museu m on o.museu = m.cadastro_nacional) ext_obra"
        " where lower(" + field + ") like lower('" + query + "%')");
  }

  std::string print(pqxx::row& obj) {
    return std::string() +
      "# " + obj["nome"].c_str() +
      "\n" + obj["categoria"].c_str() +
      "\nPode ser visto na exposição '" + obj["exposicao"].c_str() +
      "' no " + obj["m_nome"].c_str() +
      "\nCriado por " + obj["artista"].c_str() +
      " em " + print::date(obj["data_de_criacao"].c_str()) +
      (obj["origem"].is_null()
       ? ""
       : std::string() +
          "\nEssa obra é exemplo do(a) " + obj["origem"].c_str() +
          " " + obj["epoca"].c_str()) +
      "\nDescrição: " + obj["descricao"].c_str();
  }
}

#endif // OBRA
