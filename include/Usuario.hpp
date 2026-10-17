#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <list>
#include <string>

class Usuario {
public:
    Usuario(const std::string& cpf, const std::string& nome);

    const std::string& getCpf() const;
    const std::string& getNome() const;
    const std::list<std::string>& getEmprestados() const;

    bool podeEmprestar() const;
    void adicionarEmprestimo(const std::string& codigoBarras);
    void removerEmprestimo(const std::string& codigoBarras);

private:
    std::string cpf;
    std::string nome;
    std::list<std::string> emprestados;
};

#endif
