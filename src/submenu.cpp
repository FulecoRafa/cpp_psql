#ifndef SUBMENU
#define SUBMENU

#include <pqxx/pqxx>

#include "includes.h"

namespace submenu {
  void busca() {
    while (true) {
      std::vector<std::string> options {
        "Destinos",
        "Monumentos",
        "Museus",
        "Exposições",
        "Obras",
        "Restaurantes",
        "Hoteis",
        "Menu inicial"
      };
      int selected = interact::opt_one("O que você gostaria de buscar?", options);
      switch (selected) {

        case 0: { // destinos
          std::string query = interact::prompt("Buscar por cidade: ");
          pqxx::result destinos = destino::search(query);
          if (!check::check_resul(destinos)) {
            perror("Nenhum resultado encontrado para a busca");
            break;
          }
          pqxx::row d = interact::select_one(destinos);
          std::cout << '\n' << destino::print(d) << '\n';
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
          if (!check::check_resul(monumentos)) {
            perror("Nenhum resultado encontrado para a busca");
            break;
          }
          pqxx::row m = interact::select_one(monumentos);
          std::cout << '\n' << monumento::print(m) << '\n';
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
          if (!check::check_resul(museus)) {
            perror("Nenhum resultado encontrado para a busca");
            break;
          }
          pqxx::row m = interact::select_one(museus);
          std::cout << '\n' << museu::print(m) << '\n';
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
              break;
            }
            exposicoes = exposicao::search_by_date(start, finish);
          } else {
            std::string query = interact::prompt("Pesquisa: ");
            exposicoes = exposicao::search(f, query);
          }
          if (!check::check_resul(exposicoes)) {
            perror("Nenhum resultado encontrado para a busca");
            break;
          }
          pqxx::row e = interact::select_one(exposicoes);
          std::cout << '\n' << exposicao::print(e) << '\n';
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
          if (!check::check_resul(obras)) {
            perror("Nenhum resultado encontrado para a busca");
            break;
          }
          pqxx::row o = interact::select_one(obras);
          std::cout << '\n' << obra::print(o) << '\n';
        }
          break;

        case 5: { // restaurante
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
          std::cout << '\n' << restaurante::print(r) << '\n';
        }
          break;

        case 6: { // hoteis
          std::vector<std::string> fields {
            "cadastro_nacional",
            "nome",
            "cidade",
            "pais"
          };
          std::string f = interact::opt_one_string("Pesquisar por: ", fields);
          std::string query = interact::prompt("Pesquisa: ");
          pqxx::result hoteis = hotel::search(f, query);
          if (!check::check_resul(hoteis)) {
            perror("Nenhum resultado encontrado para a busca");
            break;
          }
          pqxx::row m = interact::select_one(hoteis);
          std::cout << '\n' << hotel::print(m) << '\n';
        }
          break;

        case 7:
                return;
        default:
                perror("Invalid option.\n");
                exit(1);
      }
      interact::wait();
    }
  }
}

#endif // SUBMENU
