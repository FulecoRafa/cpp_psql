#ifndef VISITANTE
#define VISITANTE

#include <string>
#include <pqxx/pqxx>

#include "connection.cpp"

namespace visitante {
  bool login(std::string email, std::string password) {
    pqxx::result r = conn::work.exec("select * from visitante where "
        "email = '" + email + "' and "
        "senha = '" + password + "'");
    return r.size() == 1;
  }
}

#endif // VISITANTE
