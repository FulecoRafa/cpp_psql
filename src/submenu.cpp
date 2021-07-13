#ifndef SUBMENU
#define SUBMENU

#include <pqxx/pqxx>

#include "includes.h"

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
      "Exposições",
      "Obras",
      "Artistas",
      "Movimentos artísticos",
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
        std::cout << '\n' << destino::print(d) << '\n';
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
        std::cout << '\n' << monumento::print(m) << '\n';
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
        std::cout << '\n' << museu::print(m) << '\n';
        interact::wait(multi_result(museus));
      }
        break;
      case 3: {
        std::vector<std::string> fields {
          "museu",
          "nome",
          "data"
        };
        std::string f = interact::opt_one_string("Pesquisar por: ", fields);
        pqxx::result exposicoes;
        if (f == "data") {
          std::string start = interact::prompt("Data de mínima da exposição. Utilize o formato (AAAA-MM-DD): ");
          std::string finish = interact::prompt("Data de máxima da exposição. Utilize o formato (AAAA-MM-DD): ");
          if (!(check::is_date(start) && check::is_date(finish))) {
            perror("Data em formato inválido...");
            interact::wait(false);
            return;
          }
          exposicoes = exposicao::search_by_date(start, finish);
        } else {
          std::string query = interact::prompt("Pesquisa: ");
          exposicoes = exposicao::search(f, query);
        }
        if (!check_resul(exposicoes)) {
          perror("Nenhum resultado encontrado para a busca");
          interact::wait(false);
          return;
        }
        pqxx::row e = interact::select_one(exposicoes);
        std::cout << '\n' << exposicao::print(e) << '\n';
        interact::wait(multi_result(exposicoes));
      }
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
        todo();
        break;
      case 9:
        return;
      default:
        perror("Invalid option.\n");
        exit(1);
    }
  }
}

#endif // SUBMENU
