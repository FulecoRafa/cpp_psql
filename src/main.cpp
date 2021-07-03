#include "includes.h"

int main (void) {
  std::string query = interact::prompt("Procurar destino: ");
  pqxx::result destinos = destino::search(query);
  if (destinos.size() <= 0) {
    perror("Sem resultados para busca...\n");
    return 0;
  }
  pqxx::row selected = interact::select_one(destinos);
  // std::string field = interact::prompt("Campo a mudar: ");
  // std::string value = interact::prompt("Novo valor: ");
  destino::del(selected);
  return 0;
}
