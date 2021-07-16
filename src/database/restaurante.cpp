#ifndef RESTAURANTE
#define RESTAURANTE

#include <string>
#include <pqxx/pqxx>
#include "connection.cpp"
#include "../helpers/print.cpp"

namespace restaurante {
  pqxx::result search(std::string& field, std::string& query) {
    return conn::work.exec("select * from (select"
        " r.cadastro_nacional, r.nome, r.horario_abertura,"
        " r.horario_fechamento, r.culinaria1,"
        " r.culinaria2, r.culinaria3, m.nome as m_nome"
        " from restaurante r"
        " join museu m on r.museu = m.cadastro_nacional) ext_rest"
        " where lower(" + field + ") like lower('" + query + "%')");
  }

  pqxx::result search_by_culinaria(std::string culinaria) {
    return conn::work.exec("select * from (select r.*, m.nome as m_nome"
        " from restaurante r"
        " join museu m on r.museu = m.cadastro_nacional) ext_rest"
        " where lower(culinaria1) like lower('" + culinaria + "%') or"
        " lower(culinaria2) like lower('" + culinaria + "%') or"
        " lower(culinaria3) like lower('" + culinaria + "%')"
        );
  }

  pqxx::result get_reservas(std::string visitante) {
    return conn::work.exec("select rr.*, r.*, m.nome as m_nome from reserva_restaurante rr"
        " join restaurante r on r.cadastro_nacional = rr.restaurante"
        " join museu m on r.museu = m.cadastro_nacional"
        " where visitante = '" + visitante + "'"
        );
  }

  pqxx::result add_reserva(std::string visitante, std::string date,
                           std::string time, pqxx::row restaurante) {
    return conn::work.exec("insert into reserva_restaurante values("
        "'" + visitante + "', "
        "'" + date + "T" + time + ":00', "
        "'" +  restaurante["cadastro_nacional"].as<std::string>() +
        "')");
  }

  std::string print(pqxx::row& obj) {
    std::vector<std::string> culinarias;
      if (!obj["culinaria1"].is_null())culinarias.push_back(obj["culinaria1"].c_str());
      if (!obj["culinaria2"].is_null())culinarias.push_back(obj["culinaria2"].c_str());
      if (!obj["culinaria3"].is_null())culinarias.push_back(obj["culinaria3"].c_str());
    std::string res =  std::string() +
      "# " + obj["nome"].c_str() +
      "\nEncontra-se no '" + obj["m_nome"].c_str() +
      "'\nHorário de funcionamento, das " + print::time(obj["horario_abertura"].c_str()) +
      " às " + print::time(obj["horario_fechamento"].c_str());
      if (culinarias.size() > 0) {
        res += "\nCulinárias: " + culinarias[0];
        for (int i = 1; i < culinarias.size(); i++) {
          res += ", " + culinarias[i];
        }
      }
    return res;
  }

  std::string print_reserva(pqxx::row& obj) {
    return std::string() +
      "Você possui uma reserva"
      "\n no dia " + print::date(obj["data_horario"].c_str()) +
      " às " + print::time(std::string(obj["data_horario"].c_str()).substr(11)) +
      "\nNo resturante:\n" +
      print(obj);
  }
}

#endif // RESTAURANTE
