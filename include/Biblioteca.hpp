#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include <map>
#include <string>

#include "Livro.hpp"

class Biblioteca {
public:
    std::string cadastrarLivro(const std::string& codigoBarras,
                               const std::string& numeroChamada,
                               const std::string& titulo,
                               const std::string& autor, int ano);

private:
    std::map<std::string, Livro> livros;
};

#endif
