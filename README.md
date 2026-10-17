# Gerenciamento de biblioteca

Atividade da Unidade 2 de Linguagem de Programação I.

Um sistema simples em C++ que gerencia o acervo de uma biblioteca, controlando o cadastro de livros, de usuários e o fluxo de empréstimos e devoluções.

## Arquivos

```text
.
├── AGENTS.md       regras que a IA lê antes de cada pedido
├── DESCRICAO.md    a descrição do sistema, escrita por você
├── ENUNCIADO.md    a atividade
├── PLANO.md        o plano feito com a IA (criado na etapa 3)
├── README.md       este arquivo
├── exemplos/       arquivos de entrada para testar
├── include/        um .hpp por classe
└── src/            um .cpp por classe, mais a interface
```

## Compilar e executar

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema
```


## Onde uso a STL

Escreva esta seção sem IA. Para cada container ou algoritmo da STL que o
sistema usa: em que classe ele está, o que guarda, e por que você escolheu
ele e não outro.

| Onde | O quê | Por quê |
| ---  | ---   | ---     |
| Classe `Biblioteca` | `map` para `livros` e `usuarios` | Escolhi o map porque ele impede cadastros duplicados e acha os dados mais rápido na hora de fazer o empréstimo, sem precisar fazer um laço for|
| ---  | ---   | ---     |
| Classe `Usuario` | `list` para os `emprestados` | Escolhi a list porque, quando a pessoa devolve o livro, eu posso usar o `.remove()` para tirar o código do meio da lista facilmente, sem precisar reorganizar os outros elementos |
| ---  | ---   | ---     |
| Classe `Biblioteca` | `vector` e `sort` na listagem | Usei o `std::sort` nele para organizar a lista em ordem alfabética. Isso só foi possível porque criei um `operator<` na classe `Livro` ensinando o programa a comparar os títulos |

## Como usei a IA

Escreva com as suas palavras:

- Modelo usado: OpenCode v1.19.3, Big Pickle

- Um pedido que deu certo, e por que você acha que deu certo: A parte de  fazer o plano passo a passo PLANO.md antes de me dar qualquer código. Sinto que deu certo porque dividiu um sistema grande em 6 etapas menores, o que permitindo testar e fazer um commit de cada vez sem me perder nos erros.

- Um pedido que deu errado, o que veio errado e como você mudou o pedido: Quando fiz o DESCRICAO.md pela primeira vez, eu não tinha deixado algumas coisas claras, como  a ordem exata de verificação do empréstimo nem as mensagens de erro, e a IA apontou várias ambiguidades. Tive que mandar um novo pedido respondendo as perguntas dela e arrumar as regras exatas para ela não programar coisas erradas.

- Uma coisa que a IA sugeriu e você recusou, e por quê: Na hora de planejar o loop do menu, a IA me deu duas sugestões que poderiam complicar a regra de saída. Eu recusei e pedi para ela seguir pelo caminho mais simples, perguntando apenas "(s/n)" depois de cada ação, onde o "n" encerra o programa. Para evitar complicar e fazer besteira.
