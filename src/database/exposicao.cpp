#ifndef EXPOSICAO
#define EXPOSICAO

#include <string>
#include <pqxx/pqxx>
#include <iostream>
#include "connection.cpp"
#include "../helpers/print.cpp"


// busca por exposicoes e fornecimento de informacoes relevantes sobre estas
namespace exposicao {
  pqxx::result search(std::string& field, std::string& query) {
    return conn::work.exec(std::string() +
        "select * from (select e.nome, e.data_de_inicio, e.data_de_termino, e.descricao, m.nome as museu"
        " from exposicao e join museu m on e.museu = m.cadastro_nacional"
        ") exposits"
        " where lower(" + field + ") like lower('" + query + "%')");
  }

  pqxx::result search_by_date(std::string& start, std::string& finish) {
    return conn::work.exec(std::string() +
        "select e.nome, e.data_de_inicio, e.data_de_termino, e.descricao, m.nome as museu"
        " from exposicao e join museu m on e.museu = m.cadastro_nacional"
        " where e.data_de_inicio >= '" + start + "' and e.data_de_termino < '" + finish + "'"
        " or e.data_de_termino is null");
  }

  std::string print(pqxx::row& obj) {
    std::string ret = std::string() + "# Exposição '" + obj["nome"].c_str() +
      "'\nAberta no museu '" + obj["museu"].c_str() +
      "'\nComeça/começou   em " + print::date(obj["data_de_inicio"].c_str()) +
      (obj["data_de_termino"].is_null()
       ? "\nNão tem data de término prevista"
       : "\nTermina/terminou em " + print::date(obj["data_de_termino"].c_str())) +
      "\nDescrição: " + obj["descricao"].c_str();
    return ret;
  }
}

#endif // EXPOSICAO
