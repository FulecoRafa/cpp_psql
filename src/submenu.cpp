#ifndef SUBMENU
#define SUBMENU

#include <pqxx/pqxx>

#include "helpers/interact.cpp"
#include "database/database.h"

namespace submenu {
  void busca() {
    std::vector<std::string> options {
      "Destinos",
      "Monumentos",
      "Museus",
      "Obras",
      "Artistas",
      "Épocas",
      "Restaurantes",
      "Hoteis",
      "Menu inicial"
    };
    int selected = interact::opt_one(options);
    switch (selected) {
      case 0: {
          std::string query = interact::prompt("Buscar por cidade: ");
          pqxx::result destinos = destino::search(query);
          pqxx::row d = interact::select_one(destinos);
          std::cout << destino::print(d) << '\n';
          interact::wait();
        }
        break;
      case 1:
        todo();
        break;
      case 2:
        todo();
        break;
      case 3:
        todo();
        break;
      case 4:
        todo();
        break;
      case 5:
        todo();
        break;
      case 6:
        todo();
        break;
      case 7:
        todo();
        break;
      case 8:
        return;
      default:
        perror("Invalid option.\n");
        exit(1);
    }
  }
}

#endif // SUBMENU
