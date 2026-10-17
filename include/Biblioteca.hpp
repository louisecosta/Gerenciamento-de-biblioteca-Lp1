#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include <map>
#include <string>

#include "Livro.hpp"
#include "Usuario.hpp"

class Biblioteca {
public:
    std::string cadastrarLivro(const std::string& codigoBarras,
                               const std::string& numeroChamada,
                               const std::string& titulo,
                               const std::string& autor, int ano);

    std::string cadastrarUsuario(const std::string& cpf,
                                 const std::string& nome);

private:
    std::map<std::string, Livro> livros;
    std::map<std::string, Usuario> usuarios;
};

#endif
