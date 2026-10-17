# PLANO — Sistema de Biblioteca

Feito a partir de `DESCRICAO.md` e `AGENTS.md`, conferindo os requisitos de STL
do `ENUNCIADO.md`. Este plano não tem código do sistema: só os arquivos, os
métodos, os containers e a ordem. As perguntas da seção 4 precisam de resposta
antes da etapa 1.

## 1. Arquivos

```text
.
├── include/
│   ├── Livro.hpp        dados de uma cópia física
│   ├── Usuario.hpp      dados de um leitor
│   ├── Biblioteca.hpp   regras e acervo (a classe principal)
│   └── Interface.hpp    menu e impressões (funções, não uma classe do sistema)
├── src/
│   ├── Livro.cpp
│   ├── Usuario.cpp
│   ├── Biblioteca.cpp
│   ├── Interface.cpp
│   └── main.cpp         cria a Biblioteca e chama a interface
├── exemplos/            um arquivo de entrada por etapa, mais um completo
└── PLANO.md             este arquivo
```

- O comando do `README.md` (`g++ ... src/*.cpp -Iinclude ...`) já pega todo
  `.cpp` novo em `src/` → nada muda no README.
- As classes do sistema não usam `cin`/`cout` (AGENTS.md): recebem dados por
  parâmetro e devolvem resultados. Quem lê e imprime é a interface.
- Quando a regra define uma mensagem, a classe devolve a **frase pronta** e a
  interface só faz `cout << frase`. Consultas (listagem, consulta de usuário)
  devolvem **dados** (`vector<Livro>`, ponteiro para `Usuario`) e a interface
  monta a tela.

## 2. As classes

### Livro — uma cópia física (`include/Livro.hpp`, `src/Livro.cpp`)

| Campo | Tipo | Por quê |
| --- | --- | --- |
| codigoBarras | `std::string` | 10 dígitos e único; string preserva o zero à esquerda (regra do DESCRICAO) |
| numeroChamada | `std::string` | 5 dígitos; é identificador, não faz conta — mesma lógica do CPF |
| titulo | `std::string` | aparece na mensagem de empréstimo e na ordenação |
| autor | `std::string` | dado do acervo |
| ano | `int` | comparação direta com o limite (≤ 2026) |
| cpfMutuario | `std::string` | vazio = disponível; com CPF = emprestado |

**O status não é um campo separado: ele deriva do `cpfMutuario`.** Se
existissem os dois (`bool emprestado` + `cpfMutuario`), eles podiam discordar
(livro "disponível" mas com dono). Com um campo só, esse erro não nasce.

Métodos:

- construtor com os 5 dados da entrada;
- getters de todos os campos;
- `bool estaDisponivel() const` → `cpfMutuario.empty()`;
- `void emprestarPara(const std::string& cpf)` e `void devolver()` → mudam só
  o `cpfMutuario`; quem decide **se pode** emprestar é a `Biblioteca`;
- `bool operator<(const Livro& outro) const` (entra na etapa 5) → compara
  `titulo`, é o que o `std::sort` da listagem usa.

### Usuario — o leitor (`include/Usuario.hpp`, `src/Usuario.cpp`)

| Campo | Tipo | Por quê |
| --- | --- | --- |
| cpf | `std::string` | 11 dígitos, chave do map; string preserva o zero |
| nome | `std::string` | completo, pode ter espaços |
| emprestados | `std::list<std::string>` | códigos de barras dos livros que está levando (máx. 3) |

Por que `list` e não `vector`: a operação de sempre é inserir no fim e
remover no meio (devolução), preservando a ordem de empréstimo — e o
ENUNCIADO (seção 2) exige pelo menos um `set` ou um `list`. Com 3 itens um
`vector` também daria conta; se preferir trocar, troque — é você quem vai
defender a escolha na avaliação.

```cpp
emprestados.push_back("2025001523");   // pegou
emprestados.remove("2025001523");     // devolveu
```

Métodos:

- getters, inclusive `const std::list<std::string>& getEmprestados() const`;
- `bool podeEmprestar() const` → `emprestados.size() < 3`;
- `void adicionarEmprestimo(codigo)` / `void removerEmprestimo(codigo)`.

O `Usuario` **não** conhece `Livro`: guarda só códigos. Quem cruza as duas
coisas é a `Biblioteca`.

### Biblioteca — as regras (`include/Biblioteca.hpp`, `src/Biblioteca.cpp`)

| Campo | Tipo | Por quê |
| --- | --- | --- |
| livros | `std::map<std::string, Livro>` | chave = código de barras |
| usuarios | `std::map<std::string, Usuario>` | chave = CPF |

| Método | O que faz | Devolve |
| --- | --- | --- |
| `cadastrarLivro(codigo, numChamada, titulo, autor, ano)` | valida formato, duplicidade e coerência; insere | `std::string` com a frase |
| `cadastrarUsuario(cpf, nome)` | valida CPF e duplicidade | frase |
| `emprestar(cpf, codigo)` | aplica a ordem de verificação da regra | frase de sucesso ou de erro |
| `devolver(codigo)` | tira o livro do usuário e libera a cópia | frase |
| `livrosDisponiveis()` | filtra os disponíveis e ordena por título | `std::vector<Livro>` |
| `buscarLivro(codigo)` / `buscarUsuario(cpf)` | pesquisa rápida | `const Livro*` / `const Usuario*` (`nullptr` se não achar) |

O ponteiro aponta para o objeto que já está dentro do map: ninguém faz
`new`, e quem "libera" é o próprio map quando a `Biblioteca` sai de escopo.

```cpp
const Livro* l = bib.buscarLivro("2025001523");
if (l == nullptr) { /* fora do acervo */ }
```

Achar um livro pelo número de chamada (regras da coerência e da obra
repetida) = varredura simples no map — o acervo é pequeno; índice secundário
só valeria a pena se o sistema crescer muito.

Ordem de verificação do `emprestar`, exatamente como no `DESCRICAO.md`:

1. CPF cadastrado → senão "Usuario nao encontrado";
2. `podeEmprestar()` → senão "Limite de empretimos atingido";
3. livro cadastrado → senão "Livro fora do acervo";
4. `estaDisponivel()` → senão "Livro indisponivel";
5. obra repetida para o mesmo CPF → posição e mensagem a confirmar (Q3/Q2);
6. registra nos dois e devolve
   `"OK: Emprestimo realizado. {titulo} agora esta com {nome}."`.

### Interface (`include/Interface.hpp`, `src/Interface.cpp`, `src/main.cpp`)

Funções livres, sem estado:

- `void executar(Biblioteca& bib)` → o loop do menu: imprime, lê a opção,
  despacha, repete até a opção 0;
- uma função por opção (`opcaoCadastrarLivro(bib)`, ...) para o menu não virar
  um bloco gigante;
- `main.cpp`: cria a `Biblioteca` e chama `executar`.

Detalhe que derruba menu (ENUNCIADO 5.7): a leitura precisa sobreviver a
texto onde esperava número e a fim de arquivo — os testes rodam com
`./sistema < exemplos/x.txt` e, quando a entrada acaba, o programa tem que
**sair**, senão vira um laço infinito imprimindo sem parar.

## 3. Onde entra cada pedaço da STL

| Onde | Container/algoritmo | Por quê |
| --- | --- | --- |
| `Biblioteca::livros` | `std::map<std::string, Livro>` | busca por código de barras em O(log n) e chave única: o próprio map recusa código repetido (a regra "Cadastro ja existente" vira um `insert` que falha) |
| `Biblioteca::usuarios` | `std::map<std::string, Usuario>` | idem, com o CPF como chave |
| `Usuario::emprestados` | `std::list<std::string>` | a lista de empréstimos: inserir no fim, remover na devolução, ordem preservada; atende ao "set ou list" do enunciado |
| `Biblioteca::livrosDisponiveis` | `std::vector<Livro>` + `std::sort` | sort quer um intervalo aleatório; vector é o mais simples; a comparação vem do `operator<` do `Livro` |

```cpp
// ENUNCIADO, seção 2: sort com operator< da sua classe, sem lambda
bool Livro::operator<(const Livro& outro) const {
    return titulo < outro.titulo;
}
std::sort(disponiveis.begin(), disponiveis.end());   // usa o operator<
```

Isso cobre os três requisitos de STL do `ENUNCIADO.md`: um `map` ✓, um
`set` ou `list` ✓, `sort` com `operator<` em classe sua ✓.

## 4. Perguntas antes da etapa 1

### 4.1 Mudam o funcionamento — preciso da sua resposta (vale registrar no
`DESCRICAO.md` e commitar, como manda o ENUNCIADO 5.1)

**Q1 — Textos das mensagens.** A regra diz "saídas sem acentos", mas várias
mensagens do `DESCRICAO.md` estão com acento, e uma parece typo. Proponho
gravar assim:

| Está escrito hoje | Proponho |
| --- | --- |
| "Usuário não encontrado" | "Usuario nao encontrado" |
| "Limite de empréstimos atingido" | "Limite de empretimos atingido" |
| "Cadastro já existente" | "Cadastro ja existente" |
| "Devolução invalida" | "Devolucao invalida" |
| "Livro indisponível" | "Livro indisponivel" |
| "Livro fora do acervo" | "Livro fora do acervo" (provável typo) |


**Q2 — Mensagens que ainda não existem.** Situações previstas pelas regras,
sem frase definida. Minhas propostas:

| Situação | Mensagem proposta |
| --- | --- |
| Cadastrar usuário com sucesso | "Usuario cadastrado com sucesso!" |
| Código de barras com ≠ 10 dígitos (ou não-numérico) | "Codigo de barras invalido" |
| Número de chamada com ≠ 5 dígitos | "Numero de chamada invalido" |
| Ano acima de 2026 | "Ano invalido" |
| CPF com ≠ 11 dígitos ou todos iguais | "CPF invalido" |
| Número de chamada repetido, mas com dados diferentes | "Dados inconsistentes" |
| Usuário já está com outro exemplar da mesma obra | "Usuario ja possui este livro" |

**Q3 — Onde entra a obra repetida.** A regra "cada CPF só pode pegar um
exemplar de livros iguais por vez" não diz onde entra na ordem de verificação
do empréstimo. Só dá para verificar depois que o livro existe (preciso do
número de chamada dele). Proponho: **depois de "disponível"**, como última
checagem. Confirma?

**Q4 — Menu: "fazer mais alguma ação".** A frase "deve haver persistência em
perguntar se o operador quer fazer mais alguma ação" pode ser:

- **(a)** depois de cada ação, perguntar "Fazer mais alguma acao? (s/n)" —
  mas aí o que acontece com "n", já que só a opção 0 encerra?
- **(b)** o menu simplesmente se repete até a opção 0 — "perguntar" é
  mostrar o menu de novo.

Minha leitura é a **(b)**, porque é a única que fecha com "a operação só
encerra na opção 0". Qual é a sua? 

**Q5 — "Mesmas informações" do número de chamada.** A regra fala em "mesmo
livro/mesma obra e **volume**", mas não existe campo volume. Proponho comparar
**título + autor + ano** (com o número de chamada já igual). Pode ser?

**Q6 — Ano e ordem das validações.** Só existe limite superior (2026):
proponho aceitar `1 ≤ ano ≤ 2026`. E no cadastro de livro proponho a ordem —
formato do código → código duplicado → número de chamada → ano → coerência do
número de chamada (no de usuário: formato do CPF → duplicidade).

### 4.2 Detalhe — escolho o mais simples, você pode mudar

- **Listagem (opção 5):** uma linha por livro:
  `titulo - autor - codigo de barras`. Vazia: `Nenhum livro disponivel`.
- **Consulta (opção 6):** CPF, nome, `Livros emprestados:` e cada um como
  `titulo (codigo)`. Sem livros: `Nenhum livro emprestado`.
- **Número de chamada como `string`** (preserva zero à esquerda, mesmo
  motivo do CPF).
- **Entrada inválida no menu** (texto onde esperava número):
  `Opcao invalida` e volta ao menu.

## 5. Etapas

Cada etapa termina compilando com o comando do `README.md`, sem avisos com
`-Wall -Wextra`, e com um arquivo novo em `exemplos/` para rodar. Ao fim de
cada uma: compile, rode, confira (`git status`, `git diff`) e faça um commit
(ENUNCIADO 5.10).

### Etapa 1 — Livro + menu com cadastro de livro (opção 1)

- **Cria:** `include/Livro.hpp`, `src/Livro.cpp`, `include/Interface.hpp`,
  `src/Interface.cpp`, `src/main.cpp`, `exemplos/cadastro_livro.txt`.
- **Funciona:** `Livro` com campos, getters e `estaDisponivel()`;
  `Biblioteca` com o `map` de livros e `cadastrarLivro()` (validações na
  ordem da Q6); interface com o menu das opções 1 e 0.
- **Teste:** `./sistema < exemplos/cadastro_livro.txt` — livro válido com
  título contendo espaço; código com 9 dígitos; repetir o mesmo código; ano
  2027; número de chamada com 4 dígitos; e a entrada acabando (tem que sair,
  sem laço infinito).
- **Cuidado (o clássico):** `titulo` e `autor` têm espaço → ler com
  `getline`; depois de um campo lido com `>>` o `\n` sobra no buffer e engole
  a linha seguinte — é o `cin.ignore()`.
- **Pronto quando:** todos os casos batem com as mensagens combinadas e
  `-Wall -Wextra` está limpo.

### Etapa 2 — Usuario + cadastro (opção 2)

- **Cria:** `include/Usuario.hpp`, `src/Usuario.cpp`,
  `exemplos/cadastro_usuario.txt`. **Altera:** `Biblioteca` (map de usuários +
  `cadastrarUsuario`), `Interface` (opção 2).
- **Funciona:** CPF com 11 dígitos e não-todos-iguais, e único; nome com
  espaços.
- **Teste:** CPF válido; CPF de 10 dígitos; `11111111111`; CPF repetido.
- **Cuidado:** CPF lido com `>>` e nome com `getline` → mesmo `cin.ignore()`
  da etapa 1.

### Etapa 3 — Empréstimo (opção 3)

- **Altera:** `Biblioteca` (`buscarLivro`, `buscarUsuario`, `emprestar`),
  `Interface` (opção 3). **Cria:** `exemplos/emprestimo.txt`.
- **Funciona:** a ordem de verificação (seção 2) com as mensagens
  combinadas; sucesso =
  `"OK: Emprestimo realizado. O Hobbit agora esta com Maria."`.
- **Teste:** CPF inexistente; usuário já com 3 livros; livro fora do
  acervo; livro já emprestado; obra repetida (cadastra 2 exemplares do mesmo
  número de chamada e tenta pegar os dois); e o caminho feliz do exemplo do
  `DESCRICAO.md`.

### Etapa 4 — Devolução (opção 4)

- **Altera:** `Biblioteca::devolver`, `Interface` (opção 4). **Cria:**
  `exemplos/devolucao.txt`.
- **Funciona:** remove o código da `list` do usuário, esvazia o
  `cpfMutuario`; `"Livro devolvido com sucesso!"` ou `"Devolucao invalida"`.
- **Teste:** devolver livro emprestado → sucesso e o livro volta para a
  listagem; devolver livro inexistente → erro; devolver livro já devolvido →
  erro; devolver 1 dos 3 e pegar outro (a vaga abriu); devolver um exemplar
  e então poder pegar o segundo exemplar da mesma obra.

### Etapa 5 — Listagem ordenada (opção 5) + `operator<`

- **Altera:** `Livro` (`operator<`), `Biblioteca` (`livrosDisponiveis()` →
  filtra + `std::sort`), `Interface` (opção 5). **Cria:**
  `exemplos/listagem.txt`.
- **Teste:** 3 livros com 1 emprestado → lista só os 2 disponíveis, em ordem
  alfabética simples e sensível a maiúsculas (`Zebra` vem antes de `ala`,
  porque `Z` < `a` no código da letra); lista vazia → mensagem da Q2/4.2.

### Etapa 6 — Consulta (opção 6) + acabamento

- **Altera:** `Interface` (opção 6, guarda de entrada inválida e o ajuste
  final sobre "fazer mais ação" conforme Q4). **Cria:**
  `exemplos/consulta.txt`, `exemplos/cenario_completo.txt`.
- **Teste:** usuário com livros; sem livros; CPF inexistente; texto digitado
  no menu; depois roda **todos** os exemplos — os antigos precisam continuar
  passando.
- **Pronto quando:** tudo compila sem aviso, todos os exemplos batem e
  nenhuma saída tem acento.

Depois das 6 etapas (só você, ENUNCIADO 4.2): preencher "Onde uso a STL" e
"Como usei a IA" no `README.md` sem IA, um commit por etapa, e conferir
`git status`/`git diff` depois de cada etapa.