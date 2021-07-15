#ifndef RESERVAS
#define RESERVAS

#include <cstdio>
#include <vector>
#include <string>

#include "includes.h"

namespace reservas {
  std::string visitante("");
  bool login() {
    std::string email = interact::prompt("Email: ");
    std::string senha = interact::password("Senha: ");
    if (visitante::login(email, senha)) {
      visitante = email;
      return true;
    }
    perror("Email ou senha incorretos\n");
    return false;
  }

  void get_reservas() {
    if (!login()) return;
    std::vector<std::string> options {
      "hotel",
      "restaurante",
      "viagem",
      "menu inicial"
    };
    int tipo = interact::opt_one("Você quer ver que tipo de reserva?", options);
    switch (tipo) {
      case 0:
        todo();
        break;
      case 1:
        todo();
        break;
      case 2:
        todo();
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

#endif // RESERVAS
