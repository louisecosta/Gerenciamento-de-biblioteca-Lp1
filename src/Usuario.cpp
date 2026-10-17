#include "Usuario.hpp"

Usuario::Usuario(const std::string& cpf, const std::string& nome)
    : cpf(cpf), nome(nome) {
}

const std::string& Usuario::getCpf() const {
    return cpf;
}

const std::string& Usuario::getNome() const {
    return nome;
}

const std::list<std::string>& Usuario::getEmprestados() const {
    return emprestados;
}

bool Usuario::podeEmprestar() const {
    return emprestados.size() < 3;
}

void Usuario::adicionarEmprestimo(const std::string& codigoBarras) {
    emprestados.push_back(codigoBarras);
}

void Usuario::removerEmprestimo(const std::string& codigoBarras) {
    emprestados.remove(codigoBarras);
}
