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
    std::vector<std::string> options {    // recebe uma string com a opcao de busca a ser feita
      "Destinos",
      "Monumentos",
      "Museus",
      "Exposições",
      "Obras",
      "Restaurantes",
      "Hoteis",
      "Menu inicial"
    };
    int selected = interact::opt_one("O que você gostaria de buscar?", options);  // recebe o retorno de interact.cpp com a opcao de execucao a ser realizada
    switch (selected) {

      case 0: { // destinos
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

      case 1: { // monumentos
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
        
      case 2: { // museus
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
      case 3: { // exposicoes
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

      case 4: { // obras
        std::vector<std::string> fields {
          "nome",
          "museu",
          "artista",
          "movimento artístico/origem"
        };
        std::string f = interact::opt_one_string("Pesquisar por: ", fields);
        std::string query = interact::prompt("Pesquisa: ");
        pqxx::result obras = obra::search(f, query);
        if (!check_resul(obras)) {
          perror("Nenhum resultado encontrado para a busca");
          interact::wait(false);
          return;
        }
        pqxx::row o = interact::select_one(obras);
        std::cout << '\n' << obra::print(o) << '\n';
        interact::wait(multi_result(obras));
      }
        break;

      case 5: { // restaurante

      }
        todo();
        break;

      case 6: { // hoteis

      }
        todo();
        break;
      case 7:
        return;
      default:
        perror("Invalid option.\n");
        exit(1);
    }
  }
}

#endif // SUBMENU
