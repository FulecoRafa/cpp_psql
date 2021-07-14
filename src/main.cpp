#include "helpers/interact.cpp"
#include "includes.h"
#include "submenu.cpp"
#include <cstdio>

int main (void) {
  std::vector<std::string> options{
    "Buscar",
    "Minhas reservas",
    "Fazer nova reserva",
    "Fazer nova viagem",
    "Sair"
  };
  while (true) {
    int selected = interact::opt_one("O que gostaria de fazer?", options);
    switch (selected) {
      case 0:
        submenu::busca();
        break;
      case 1:
        todo()
        break;
      case 2:
        todo()
        break;
      case 3:
        todo()
        break;
      case 4:
        return 0;
      default:
        perror("Option is not valid.\n");
        exit(1);
    }
  }
  return 0;
}
