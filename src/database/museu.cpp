#ifndef MUSEUS
#define MUSEUS

#include <string>
#include <pqxx/pqxx>
#include "connection.cpp"

namespace museu {
  pqxx::result search(std::string& field, std::string& query) {
    return conn::work.exec("select * from museu where lower(" + field + ") like lower('" + query + "%')");
  }

  std::string print(pqxx::row& obj) {
    pqxx::result linguas =
      conn::work.exec(std::string() + "select idioma from idioma_museu where museu = '" + obj["cadastro_nacional"].c_str()
          + "'");
    std::string ret = std::string() + "# " + obj["nome"].c_str() +
      "\nCadastro Nacional: " + obj["cadastro_nacional"].c_str() +
      "\nTelefone: " + obj["telefone"].c_str() +
      "\nPossui assessibilidade para deficientes visuais: " +
        (obj["ajuda_deficiente_visao"].as<bool>() ? "✔" : "✘") +
      "\nPossui assessibilidade para deficientes auditivos: " +
        (obj["ajuda_deficiente_auditivo"].as<bool>() ? "✔" : "✘") +
      "\nEndereço: " + obj["logradouro"].c_str() + ", número " + obj["numero"].c_str() +
      "\n          " + obj["codigo_postal"].c_str() + ", " + obj["cidade"].c_str() + ", " + obj["pais"].c_str() +
      "\nLinguas faladas: ";
    for (auto entry : linguas) {
      ret += std::string() + entry["idioma"].c_str() + ", ";
    }
    return ret;
  }
}

#endif // MUSEUS
