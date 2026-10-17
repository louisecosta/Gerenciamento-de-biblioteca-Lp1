#include "Livro.hpp"

Livro::Livro(const std::string& codigoBarras, const std::string& numeroChamada,
             const std::string& titulo, const std::string& autor, int ano)
    : codigoBarras(codigoBarras), numeroChamada(numeroChamada),
      titulo(titulo), autor(autor), ano(ano), cpfMutuario("") {
}

const std::string& Livro::getCodigoBarras() const {
    return codigoBarras;
}

const std::string& Livro::getNumeroChamada() const {
    return numeroChamada;
}

const std::string& Livro::getTitulo() const {
    return titulo;
}

const std::string& Livro::getAutor() const {
    return autor;
}

int Livro::getAno() const {
    return ano;
}

const std::string& Livro::getCpfMutuario() const {
    return cpfMutuario;
}

bool Livro::estaDisponivel() const {
    return cpfMutuario.empty();
}

void Livro::emprestarPara(const std::string& cpf) {
    cpfMutuario = cpf;
}

void Livro::devolver() {
    cpfMutuario = "";
}

bool Livro::operator<(const Livro& outro) const {
    return titulo < outro.titulo;
}
