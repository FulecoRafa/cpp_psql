#ifndef HOTEL
#define HOTEL

#include <string>
#include <pqxx/pqxx>
#include "connection.cpp"

#include "../helpers/print.cpp"

namespace hotel {
  pqxx::result search(std::string& field, std::string& query) {
    return conn::work.exec("select * from hotel where lower(" + field + ") like lower('" + query + "%')");
  }

  pqxx::result get_reservas(std::string &visitante) {
    return conn::work.exec("select * from reserva_quarto rq"
        " join quarto q on q.numero = rq.quarto and q.hotel = rq.hotel"
        " join hotel h on q.hotel = h.cadastro_nacional"
        " where visitante = '" + visitante + "'"
        );
  }

  std::string print(pqxx::row& obj) {
    return std::string() + "# " + obj["nome"].c_str() +
      "\nCadastro Nacional: " + obj["cadastro_nacional"].c_str() +
      "\nTelefone: " + obj["telefone"].c_str() +
      "\nEndereço: " + obj["logradouro"].c_str() + ", número " + obj["numero"].c_str() +
      "\n          " + obj["codigo_postal"].c_str() + ", " + obj["cidade"].c_str() + ", " + obj["pais"].c_str();
  }

  std::string print_quarto(pqxx::row obj) {
    std::string total = std::to_string (
        print::moneytof(obj["preco_por_cama"].as<std::string>()) *
        obj["camas"].as<int>()
        );
    return std::string() +
      "Quarto número " + obj["numero"].c_str() +
      "\n" + obj["camas"].c_str() + " camas por $" +
      total.substr(0, total.find('.') + 3) +
      " No hotel:\n" + print(obj);
  }

  std::string print_reserva(pqxx::row obj) {
    return std::string() +
      "Você tem uma reserva marcada"
      "\nde " + print::date(obj["data_de_inicio"].c_str()) +
      " a " + print::date(obj["data_de_inicio"].c_str()) +
      "\nno quarto:\n" + print_quarto(obj);
  }
}

#endif // HOTEL
