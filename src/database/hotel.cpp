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

  pqxx::result get_quartos(std::string &hotel) {
    return conn::work.exec("select *, (q.preco_por_cama * q.camas) as total"
        " from quarto q"
        " join hotel h on q.hotel = h.cadastro_nacional"
        " where hotel = '" + hotel + "'"
        );
  }

  pqxx::result get_reservas(std::string &visitante) {
    return conn::work.exec("select *, (q.preco_por_cama * q.camas) as total"
        " from reserva_quarto rq"
        " join quarto q on q.numero = rq.quarto and q.hotel = rq.hotel"
>>>>>>> master
        " join hotel h on q.hotel = h.cadastro_nacional"
        " where visitante = '" + visitante + "'"
        );
  }


  // retorna as informacoes a respeito do hotel, quarto, e reserva feita
  pqxx::result add_reserva(
      std::string visitante,
      std::string start,
      std::string end,
      pqxx::row quarto
      ) {
    pqxx::result res = conn::work.exec("insert into reserva_quarto values ("
        "'" + visitante + "', "
        "'" + start + "', "
        "'" + end + "', "
        "'" + quarto["numero"].as<std::string>() + "', "
        "'" + quarto["hotel"].as<std::string>() + "', "
        "'" + quarto["total"].as<std::string>() + "')"
        );
    return res;
  }

>>>>>>> master
  std::string print(pqxx::row& obj) {
    return std::string() + "# " + obj["nome"].c_str() +
      "\nCadastro Nacional: " + obj["cadastro_nacional"].c_str() +
      "\nTelefone: " + obj["telefone"].c_str() +
      "\nEndereço: " + obj["logradouro"].c_str() + ", número " + obj["numero"].c_str() +
      "\n          " + obj["codigo_postal"].c_str() + ", " + obj["cidade"].c_str() + ", " + obj["pais"].c_str();
  }

  std::string print_quarto(pqxx::row obj) {
    return std::string() +
      "Quarto número " + obj["numero"].c_str() +
      "\n" + obj["camas"].c_str() + " camas por " +
      obj["total"].as<std::string>() +
      " No hotel:\n" + print(obj);
  }

  std::string print_reserva(pqxx::row obj) {
    return std::string() +
      "Você tem uma reserva marcada"
      "\nde " + print::date(obj["data_de_inicio"].c_str()) +
      " a " + print::date(obj["data_de_termino"].c_str()) +
      "\nno quarto:\n" + print_quarto(obj);
  }
}

#endif // HOTEL
