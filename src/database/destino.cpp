#ifndef DESTINO
#define DESTINO

#include <string>
#include "connection.cpp"

namespace destino {
void all() {
  pqxx::result destinos = conn::work.exec("select * from destino");
  for (pqxx::row row : destinos) {
    printf("%s/%s\n", row["cidade"].c_str(), row["pais"].c_str());
  }
}

void add(std::string cidade, std::string pais) {
  conn::work.exec("insert into destino values ('" + cidade + "', '" + pais + "')");
}
}

#endif // DESTINO
