#ifndef SUBMENU
#define SUBMENU

#include <pqxx/pqxx>

#include "helpers/interact.cpp"
#include "helpers/print.cpp"
#include "database/database.h"

namespace submenu {
  bool check_resul(pqxx::result &r) {
    return r.size() > 0;
  }

  bool multi_result(pqxx::result &r) {
    return r.size() > 1;
  }

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
          if (!check_resul(destinos)) {
            perror("Nenhum resultado encontrado para a busca");
            interact::wait(false);
            return;
          }
          pqxx::row d = interact::select_one(destinos);
          std::cout << destino::print(d) << '\n';
          interact::wait(multi_result(destinos));
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
          if (!check_resul(monumentos)) {
            perror("Nenhum resultado encontrado para a busca");
            interact::wait(false);
            return;
          }
          pqxx::row m = interact::select_one(monumentos);
          std::cout << monumento::print(m) << '\n';
          interact::wait(multi_result(monumentos));
        }
        break;
      case 2: {
          std::vector<std::string> fields {
            "cadastro_nacional",
            "nome",
            "cidade",
            "pais"
          };
          std::string f = interact::opt_one_string("Pesquisar por: ", fields);
          std::string query = interact::prompt("Pesquisa: ");
          pqxx::result museus = museu::search(f, query);
          if (!check_resul(museus)) {
            perror("Nenhum resultado encontrado para a busca");
            interact::wait(false);
            return;
          }
          pqxx::row m = interact::select_one(museus);
          std::cout << museu::print(m) << '\n';
          interact::wait(multi_result(museus));
        }
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
