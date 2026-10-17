# Descrição do sistema


## Gerenciamento de Biblioteca

É um sistema gerenciador de biblioteca em C++. Ele serve para controle de acervo de livros, cadastrarem os usuários e livros e disponibilidade.


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
0. Sair: Sai da biblioteca e encerra a operação.


## Regras

- A ordem de verificação para o empréstimo deve ser, verificar se o CPF está cadastrado, de tem limite de empréstimo, se o livro está cadastrado e disponível.

- Não é permitido cadastrar dois livros com o mesmo código de barras.

- O ano do livro deve ser até 2026.

- O número de chamada deve ter 5 números.

- Mais de um livro pode ter o mesmo número de chamada, contanto que seja o mesmo livro, ou seja, que a informações sejam iguais, se for o mesmo livro/mesma obra e volume, muda só o código de barras. 

- O código de barras deve seguir um padrão com 10 números, e cada código de barras é único, cada livro tem o seu.

- Não é permitido cadastrar dois usuários com o mesmo CPF.

- O CPF deve ter 11 números, se o tamanho for diferente de 11 ou se todos os dígitos forem iguais, o CPF é invalido.

- O CPF e o código de barras são strings para preservar os zeros.

- Um usuário pode ter, no máximo, 3 livros emprestados ao mesmo tempo.

- Apos a devolução o livro sai da lista de livros emprestados aquele usuário e volta a ficar disponível na biblioteca.

- Só é possível emprestar um livro se o status dele for "disponível".

- A lista de livros disponíveis deve ser mostrada em ordem alfabética de título. Ordenação alfabética simples, sensível a maiúsculas e sem lidar com casos complexos de acentuação.

- Cada CPF só pode pegar um exemplar de livros iguais por vez, para pegar outro exemplar ou o mesmo livro, o usuário tem que fazer a devolução antes.

- Ao devolver um livro, deve aparecer a mensagem "Livro devolvido com sucesso!"

- As saídas devem seguir um padrão sem acentos.

- Enquanto a operação não for encerrada na opção 0 do menu, deve haver persistência em perguntar se o operador quer fazer mais alguma ação.

- Ao escolher a opção 0 do menu, a operação é encerrada, os dados são perdidos ao fechar. 


## Quando algo dá errado

- **Empréstimo inválido:** Se tentar emprestar um livro que não está cadastrado, o sistema avisa "Livro fora do acerv". Se o livro já estiver com outra pessoa, avisa "Livro indisponível".

- **Limite estourado:** Se o usuário tentar pegar um 4º livro, o sistema bloqueia e avisa "Limite de empréstimos atingido".

- **Cadastro duplicado:** Se tentar cadastrar um CPF ou código de barras de livro que já existe, avisa "Cadastro já existente".

- **Devolução inválida:** Se tentar devolver um livro que não existe ou que não está emprestado, exibe "Devolução invalida".

- **Usuário não cadastrado:** Se tentar fazer um empréstimo ou uma consulta de um CPF que não está cadastrado, exibe "Usuário não encontrado".


## Classes que eu imagino

- `Livro`: Guarda os dados do livro e o seu status de disponibilidade.
- `Usuario`: Guarda os dados do leitor e controla a quantidade de livros que ele pegou.
- `Biblioteca`: É a classe principal. Guarda a lista (ou mapa) de todos os livros e usuários, e faz a verificação das regras antes de aprovar um empréstimo ou devolução.


## Exemplo de uso

> Escolha uma opcao: 1
>
> Codigo de barras: 2025001523
>
> Numero de chamada: 13245
>
> Titulo: O Hobbit
>
> Autor: Tolkien
>
> Ano: 1937
>
> Livro cadastrado com sucesso!
> 
> Escolha uma opcao: 3
>
> Digite o CPF do usuário: 52134542565
>
> Codigo de barras do livro: 2025001523
>
> OK: Emprestimo realizado. O Hobbit agora esta com Maria.