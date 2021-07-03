#ifndef CONN
#define CONN

#include <cstdio>
#include <pqxx/pqxx>

namespace conn {
  pqxx::connection conn{ "postgresql://postgres:docker@localhost/postgres" };
  pqxx::work work(conn);
}
#endif
