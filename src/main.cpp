#include "helpers/interact.cpp"
#include "submenu.cpp"
#include "reservas.cpp"
#include "add_reserva.cpp"
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
        reservas::get_reservas();
        break;
      case 2:
        reservas::add_reserva();
        break;
      case 3:
        reservas::add_viagem();
        break;
      case 4:
        conn::work.commit();
        return 0;
      default:
        perror("Option is not valid.\n");
        exit(1);
    }
  }
  conn::work.commit();
  return 0;
}
