#include "Biblioteca.hpp"

#include <utility>

static bool todosDigitos(const std::string& texto) {
    for (char c : texto) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

std::string Biblioteca::cadastrarLivro(const std::string& codigoBarras,
                                       const std::string& numeroChamada,
                                       const std::string& titulo,
                                       const std::string& autor, int ano) {
    if (codigoBarras.size() != 10 || !todosDigitos(codigoBarras)) {
        return "Codigo de barras invalido";
    }

    if (livros.find(codigoBarras) != livros.end()) {
        return "Cadastro ja existente";
    }

    if (numeroChamada.size() != 5 || !todosDigitos(numeroChamada)) {
        return "Numero de chamada invalido";
    }

    if (ano < 1 || ano > 2026) {
        return "Ano invalido";
    }

    std::map<std::string, Livro>::const_iterator it = livros.begin();
    while (it != livros.end()) {
        const Livro& existente = it->second;
        if (existente.getNumeroChamada() == numeroChamada
            && (existente.getTitulo() != titulo
                || existente.getAutor() != autor
                || existente.getAno() != ano)) {
            return "Dados inconsistentes";
        }
        ++it;
    }

    Livro novo(codigoBarras, numeroChamada, titulo, autor, ano);
    livros.insert(std::make_pair(codigoBarras, novo));
    return "Livro cadastrado com sucesso!";
}

static bool todosIguais(const std::string& texto) {
    for (char c : texto) {
        if (c != texto[0]) {
            return false;
        }
    }
    return true;
}

std::string Biblioteca::cadastrarUsuario(const std::string& cpf,
                                         const std::string& nome) {
    if (cpf.size() != 11 || !todosDigitos(cpf) || todosIguais(cpf)) {
        return "CPF invalido";
    }

    if (usuarios.find(cpf) != usuarios.end()) {
        return "Cadastro ja existente";
    }

    Usuario novo(cpf, nome);
    usuarios.insert(std::make_pair(cpf, novo));
    return "Usuario cadastrado com sucesso!";
}
