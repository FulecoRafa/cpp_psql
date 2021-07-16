#ifndef DESTINO
#define DESTINO

#include <string>
#include "connection.cpp"

#include "../helpers/print.cpp"

namespace destino {
  pqxx::result search(std::string& city_name) {
    return conn::work.exec("select * from destino where lower(cidade) like lower('" + city_name + "%')");
  }

  pqxx::result get_viagens(std::string visitante) {
    return conn::work.exec(
        "select * from viagem where visitante = '" + visitante + "'"
    );
  }

  pqxx::result add_viagem(std::string visitante, std::string data,
                          std::string horario, std::string transporte,
                          pqxx::row &destino) {
    return conn::work.exec(
        "insert into viagem values ("
        "'" + visitante + "', "
        "'" + data + "T" + horario + ":00', "
        "'" + destino["cidade"].as<std::string>() + "', "
        "'" + destino["pais"].as<std::string>() + "', "
        "'" + transporte + "')"
      );
  }

  std::string print(pqxx::row &obj) {
    return std::string() + obj["cidade"].c_str() + "[" + obj["pais"].c_str() + "]";
  }

  std::string print_viagem(pqxx::row & obj) {
    return std::string() +
      "Você tem uma viagem " +
      print::date(obj["data_horario"].as<std::string>()) +
      " às " + print::time(obj["data_horario"].as<std::string>().substr(11)) +
      "\nde " + obj["meio_de_transporte"].c_str() + " para " + print(obj);
      ;
  }
}

#endif // DESTINO
