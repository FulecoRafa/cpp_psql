#ifndef ADD_RESERVA
#define ADD_RESERVA

#include <cstdio>
#include <vector>
#include <string>
#include <pqxx/pqxx>

#include "database/restaurante.cpp"
#include "helpers/interact.cpp"
#include "reservas.cpp"
#include "includes.h"

namespace reservas {
  void add_reserva () {
    if (!login()){
      perror("Email ou senha incorretos\n");
      return;
    }
    while (true) {
      std::vector<std::string> options {
        "hotel",
        "restaurante",
        "menu inicial"
      };
      int tipo = interact::opt_one("Você quer ver que tipo de reserva?", options);
      switch (tipo) {

        case 0: { // hotel
          std::vector<std::string> fields {
            "cadastro_nacional",
            "nome",
            "cidade",
            "pais"
          };
          std::string f = interact::opt_one_string("Pesquisar hotel por: ", fields);
          std::string query = interact::prompt("Pesquisa: ");
          pqxx::result hoteis = hotel::search(f, query);
          if (!check::check_resul(hoteis)) {
            perror("Nenhum resultado encontrado para a busca");
            break;
          }
          std::string m = interact::select_one(hoteis)["cadastro_nacional"].as<std::string>();
          pqxx::result quartos = hotel::get_quartos(m);
          if (!check::check_resul(quartos)) {
            perror("Nenhum resultado encontrado para a busca");
            break;
          }
          pqxx::row q = interact::select_one(quartos);
          std::cout << "\n" << hotel::print_quarto(q) << '\n';
          if (interact::confirm("É este quarto que gostaria de reservar?")) {
              std::string start = interact::prompt("Quando gostaria de entrar? Utilize o formato (AAAA-MM-DD): ");
              std::string finish = interact::prompt("Qual a data de saída? Utilize o formato (AAAA-MM-DD): ");
              if (!(check::is_date(start) || check::is_date(finish))) {
                perror("Data em formato inválido...");
                break;
              }
              hotel::add_reserva(visitante, start, finish, q);
              std::cout << "Reserva cadastrada com sucesso!\n";
          }
        }
          break;

        case 1: { // restaurante
          std::vector<std::string> fields {
            "nome",
            "museu",
            "culinaria"
          };
          std::string f = interact::opt_one_string("Pesquisar por: ", fields);
          if (f == "museu") f = "m_nome";
          std::string query = interact::prompt("Pesquisa: ");
          pqxx::result restaurantes;
          if (f == "culinaria") {
            restaurantes = restaurante::search_by_culinaria(query);
          } else {
            restaurantes = restaurante::search(f, query);
          }
          if (!check::check_resul(restaurantes)) {
            perror("Nenhum resultado encontrado para a busca");
            break;
          }
          pqxx::row r = interact::select_one(restaurantes);
          std::cout << "\n" << restaurante::print(r) << '\n';
          if (interact::confirm("É este restaurante que gostaria de reservar?")) {
              std::string date = interact::prompt("Quando gostaria de entrar? Utilize o formato (AAAA-MM-DD): ");
              std::string hour = interact::prompt("Qual o horário da reserva? Utilize o formato (hh:mm): ");
              if (!(check::is_date(date) || check::is_time(hour))) {
                perror("Data/horário em formato inválido...");
                break;
              }
              restaurante::add_reserva(visitante, date, hour, r);
              std::cout << "Reserva cadastrada com sucesso!\n";
          }
        }
          break;

        case 2:
          return;
        default:
          perror("Invalid option.\n");
          exit(1);
      }
      interact::wait();
    }
  }
}

#endif // ADD_RESERVA
