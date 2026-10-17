#include "Interface.hpp"

#include <iostream>
#include <limits>
#include <string>

static bool perguntarMaisAcao() {
    std::string resposta;
    while (true) {
        std::cout << "Fazer mais alguma acao? (s/n)" << std::endl;
        if (!(std::cin >> resposta)) {
            return false;
        }
        if (resposta == "s") {
            return true;
        }
        if (resposta == "n") {
            return false;
        }
    }
}

static void opcaoCadastrarLivro(Biblioteca& biblioteca) {
    std::string codigoBarras;
    std::string numeroChamada;
    std::string titulo;
    std::string autor;
    int ano = 0;

    std::cout << "Codigo de barras: ";
    std::cin >> codigoBarras;

    std::cout << "Numero de chamada: ";
    std::cin >> numeroChamada;

    std::cout << "Titulo: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, titulo);

    std::cout << "Autor: ";
    std::getline(std::cin, autor);

    std::cout << "Ano: ";
    if (!(std::cin >> ano)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ano invalido" << std::endl;
        return;
    }

    std::cout << biblioteca.cadastrarLivro(codigoBarras, numeroChamada,
                                           titulo, autor, ano)
              << std::endl;
}

void executar(Biblioteca& biblioteca) {
    while (true) {
        std::cout << "1 - Cadastrar livro" << std::endl;
        std::cout << "0 - Sair" << std::endl;
        std::cout << "Escolha uma opcao: ";

        int opcao = 0;
        if (!(std::cin >> opcao)) {
            if (std::cin.eof()) {
                return;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Opcao invalida" << std::endl;
            continue;
        }

        if (opcao == 0) {
            return;
        }

        if (opcao == 1) {
            opcaoCadastrarLivro(biblioteca);
            if (!perguntarMaisAcao()) {
                return;
            }
        } else {
            std::cout << "Opcao invalida" << std::endl;
        }
    }
}
