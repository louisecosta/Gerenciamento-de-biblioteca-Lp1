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
