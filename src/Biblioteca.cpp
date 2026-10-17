#include "Biblioteca.hpp"

#include <algorithm>
#include <list>
#include <utility>
#include <vector>

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

std::string Biblioteca::emprestar(const std::string& cpf,
                                  const std::string& codigoBarras) {
    std::map<std::string, Usuario>::iterator itUsuario = usuarios.find(cpf);
    if (itUsuario == usuarios.end()) {
        return "Usuario nao encontrado";
    }

    if (!itUsuario->second.podeEmprestar()) {
        return "Limite de empretimos atingido";
    }

    std::map<std::string, Livro>::iterator itLivro = livros.find(codigoBarras);
    if (itLivro == livros.end()) {
        return "Livro fora do acervo";
    }

    if (!itLivro->second.estaDisponivel()) {
        return "Livro indisponivel";
    }

    const std::list<std::string>& emprestados =
        itUsuario->second.getEmprestados();
    std::list<std::string>::const_iterator it = emprestados.begin();
    while (it != emprestados.end()) {
        std::map<std::string, Livro>::const_iterator itEmprestado =
            livros.find(*it);
        if (itEmprestado != livros.end()
            && itEmprestado->second.getNumeroChamada()
                   == itLivro->second.getNumeroChamada()) {
            return "Usuario ja possui este livro";
        }
        ++it;
    }

    itLivro->second.emprestarPara(cpf);
    itUsuario->second.adicionarEmprestimo(codigoBarras);

    return "OK: Emprestimo realizado. " + itLivro->second.getTitulo()
           + " agora esta com " + itUsuario->second.getNome() + ".";
}

std::string Biblioteca::devolver(const std::string& codigoBarras) {
    std::map<std::string, Livro>::iterator itLivro = livros.find(codigoBarras);
    if (itLivro == livros.end()) {
        return "Devolucao invalida";
    }

    if (itLivro->second.estaDisponivel()) {
        return "Devolucao invalida";
    }

    std::map<std::string, Usuario>::iterator itUsuario =
        usuarios.find(itLivro->second.getCpfMutuario());
    itUsuario->second.removerEmprestimo(codigoBarras);

    itLivro->second.devolver();
    return "Livro devolvido com sucesso!";
}

std::vector<Livro> Biblioteca::livrosDisponiveis() const {
    std::vector<Livro> disponiveis;
    std::map<std::string, Livro>::const_iterator it = livros.begin();
    while (it != livros.end()) {
        if (it->second.estaDisponivel()) {
            disponiveis.push_back(it->second);
        }
        ++it;
    }
    std::sort(disponiveis.begin(), disponiveis.end());
    return disponiveis;
}

const Livro* Biblioteca::buscarLivro(const std::string& codigoBarras) const {
    std::map<std::string, Livro>::const_iterator it = livros.find(codigoBarras);
    if (it == livros.end()) {
        return nullptr;
    }
    return &it->second;
}

const Usuario* Biblioteca::buscarUsuario(const std::string& cpf) const {
    std::map<std::string, Usuario>::const_iterator it = usuarios.find(cpf);
    if (it == usuarios.end()) {
        return nullptr;
    }
    return &it->second;
}
