# Descrição do sistema


## Gerenciamento de Biblioteca

É um sistema gerenciador de biblioteca. Ele serve para controle de acervo de livros, cadastrarem os usuários e livros e disponibilidade.

## O que o sistema guarda

- **Livros:** Registra dados como título, autor, ano de publicação, número de chamada (que identifica a obra), código de barras (que identifica a cópia física única) e o status (disponível ou emprestado).
- **Usuários:** Nome completo, CPF e a lista de livros que a pessoa tem emprestada no momento.

## O que dá para fazer

1. Cadastrar livro: pede código de barras, número de chamada, título, autor e ano de publicação.
2. Cadastrar usuário: pede CPF e nome.
3. Registrar empréstimo: pede o CPF do usuário e o código de barras do livro.
4. Registrar devolução: pede o código de barras do livro.
5. Listar livros disponíveis: mostra todos os livros que não estão emprestados, ordenados por título.
6. Consultar usuário: pede o CPF e mostra os dados da pessoa e quais livros ela tem em empréstimo.


## Regras

- Não é permitido cadastrar dois livros com o mesmo código de barras.
- Mais de um livro pode ter o mesmo número de chamada (se for o mesmo livro/mesma obra), mudando só o código de barras. 
- Não é permitido cadastrar dois usuários com o mesmo CPF.
- Um usuário pode ter, no máximo, 3 livros emprestados ao mesmo tempo.
- Só é possível emprestar um livro se o status dele for "disponível".
- A lista de livros disponíveis deve ser mostrada em ordem alfabética de título.

## Quando algo dá errado

- **Empréstimo inválido:** Se tentar emprestar um livro que não está cadastrado, o sistema avisa "Livro não encontrado". Se o livro já estiver com outra pessoa, avisa "Livro indisponível".
- **Limite estourado:** Se o usuário tentar pegar um 4º livro, o sistema bloqueia e avisa "Limite de empréstimos atingido".
- **Cadastro duplicado:** Se tentar cadastrar um CPF ou código de barras de livro que já existe, avisa "Cadastro já existente".
- **Devolução inválida:** Se tentar devolver um livro que não existe ou que não está emprestado, exibe erro.

## Classes que eu imagino

- `Livro`: Guarda os dados do livro e o seu status de disponibilidade.
- `Usuario`: Guarda os dados do leitor e controla a quantidade de livros que ele pegou.
- `Biblioteca`: É a classe principal. Guarda a lista (ou mapa) de todos os livros e usuários, e faz a verificação das regras antes de aprovar um empréstimo ou devolução.

## Exemplo de uso

> Escolha uma opcao: 1
> Digite o codigo de barras, numero de chamada, titulo, autor e ano: 001, 869, O Hobbit, Tolkien, 1937
> OK: Livro cadastrado com sucesso.
> 
> Escolha uma opcao: 3
> Digite o CPF do usuario e o codigo de barras do livro: 123456789, 001
> OK: Emprestimo realizado. O Hobbit agora esta com Maria.