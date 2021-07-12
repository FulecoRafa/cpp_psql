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
    int selected = interact::opt_one("O que você gostaria de buscar?", options);
    switch (selected) {
      case 0: {
          std::string query = interact::prompt("Buscar por cidade: ");
          pqxx::result destinos = destino::search(query);
          pqxx::row d = interact::select_one(destinos);
          std::cout << destino::print(d) << '\n';
        }
        break;
      case 1: {
          std::vector<std::string> fields {
            "nome",
            "cidade",
            "pais"
          };
          std::string f = interact::opt_one_string("Pesquisar por: ", fields);
          std::string query = interact::prompt("Pesquisa: ");
          pqxx::result monumentos = monumento::search(f, query);
          pqxx::row m = interact::select_one(monumentos);
          std::cout << monumento::print(m) << '\n';
        }
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
    interact::wait();
  }
}

#endif // SUBMENU
