#ifndef DESTINO
#define DESTINO

#include <string>
#include "connection.cpp"

namespace destino {
pqxx::result search(std::string& city_name) {
  return conn::work.exec("select * from destino where lower(cidade) like lower('" + city_name + "%')");
}

void add(std::string& cidade, std::string& pais) {
  conn::work.exec("insert into destino values ('" + cidade + "', '" + pais + "')");
}

void update(pqxx::row& entry, std::string& field, std::string& value) {
  try {
    conn::work.exec("update destino set " + field + " = '" + value + "' where cidade = '" + entry["cidade"].c_str() + "' and pais = '" + entry["pais"].c_str() + "'");
    conn::work.commit();
  } catch (const std::exception& e) {
    perror("There was an error: %s\n", e.what());
  }
}

void del(pqxx::row& entry) {
  conn::work.exec(std::string("") + "delete from destino where cidade = '" + entry["cidade"].c_str() + "' and pais = '" + entry["pais"].c_str() + "'");
  conn::work.commit();
}
}

#endif // DESTINO
