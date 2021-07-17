#ifndef RESERVAS
#define RESERVAS

#include <cstdio>
#include <vector>
#include <string>
#include <pqxx/pqxx>

#include "database/restaurante.cpp"
#include "includes.h"

namespace reservas {
  std::string visitante("");

  bool login() {
    if (visitante.length() > 0) return true;
    std::string email = interact::prompt("Email: ");
    std::string senha = interact::password("Senha: ");    // Login de usuario
    if (visitante::login(email, senha)) {
      visitante = email;
      return true;
    }
    return false;
  }

  void get_reservas() {

    if (!login()){
      perror("Email ou senha incorretos\n");
      return;
    }
    while (true) {
      std::vector<std::string> options {
        "hotel",
        "restaurante",
        "viagem",
        "menu inicial"
      };

      // rotina para efetuar reservas em diferentes locais
      int tipo = interact::opt_one("Você quer ver que tipo de reserva?", options);
      switch (tipo) {

        case 0: { // hotel
          pqxx::result r_quarto = hotel::get_reservas(visitante);
          if (!check::check_resul(r_quarto)) {
            perror("Você não possui nenhuma reserva em hotéis.");
            break;
          }
          pqxx::row rr = interact::select_one(r_quarto);
          std::cout << '\n' << hotel::print_reserva(rr) << '\n';
        }
          break;

        case 1: { // restaurante
          pqxx::result r_restaurante = restaurante::get_reservas(visitante);
          if (!check::check_resul(r_restaurante)) {
            perror("Você não possui nenhuma reserva em restaurante.");
            break;
          }
          pqxx::row rr = interact::select_one(r_restaurante);
          std::cout << '\n' << restaurante::print_reserva(rr) << '\n';
        }
          break;

        case 2: { // viagem
          pqxx::result viagens = destino::get_viagens(visitante);
          if (!check::check_resul(viagens)) {
            perror("Você não possui nenhuma reserva de viagem.");
            break;
          }
          pqxx::row rr = interact::select_one(viagens);
          std::cout << '\n' << destino::print_viagem(rr) << '\n';
        }
          break;

        case 3:
                return;
        default:
                perror("Invalid option.\n");
                exit(1);
      }
      interact::wait();

    }
  }
}

#endif // RESERVAS
