#ifndef LIVRO_HPP
#define LIVRO_HPP

#include <string>

class Livro {
public:
    Livro(const std::string& codigoBarras, const std::string& numeroChamada,
          const std::string& titulo, const std::string& autor, int ano);

    const std::string& getCodigoBarras() const;
    const std::string& getNumeroChamada() const;
    const std::string& getTitulo() const;
    const std::string& getAutor() const;
    int getAno() const;
    const std::string& getCpfMutuario() const;

    bool estaDisponivel() const;
    void emprestarPara(const std::string& cpf);
    void devolver();

private:
    std::string codigoBarras;
    std::string numeroChamada;
    std::string titulo;
    std::string autor;
    int ano;
    std::string cpfMutuario;
};

#endif
