202500560090 Letícia Videira Gois

# TED — Trabalho II de Estrutura de Dados I (2026)

**Aluna:** Letícia Videira Gois  
**Número de matrícula:** 202500560090  
**Disciplina:** Estrutura de Dados I — 2026  
**Professor:** Evandro Baccarin

---

# Sobre o projeto

O projeto implementa o Trabalho II da disciplina de Estrutura de Dados I da UEL.

O programa `ted` processa arquivos `.geo` e `.qry`, armazenando e manipulando formas geométricas em uma Árvore Binária de Busca (ABB).

Além da manipulação das figuras, o sistema implementa algoritmos clássicos de ordenação adaptados para produzir animações em SVG durante o processo de ordenação, conforme especificado pelo trabalho.

Ao final da execução são produzidos arquivos SVG e TXT contendo o estado final das estruturas e os resultados das consultas.

---

# Estruturas de dados utilizadas

- Árvore Binária de Busca (ABB);
- Vetores dinâmicos para apoio às ordenações;
- Armazenamento genérico utilizando `void *`;
- Modularização completa em `.h` e `.c`;
- Testes unitários utilizando Unity Framework.

---

# Algoritmos de ordenação implementados

O projeto implementa os seguintes algoritmos:

- Selection Sort (`ss`);
- Bubble Sort (`bs`);
- Insertion Sort (`is`);
- Shell Sort (`shs`);
- Quick Sort (`qs`);
- Merge Sort (`ms`).

Os algoritmos foram adaptados para gerar snapshots da execução em arquivos SVG, permitindo a criação de animações.

---

# Critérios de ordenação

As formas podem ser ordenadas pelos seguintes critérios:

| Código | Critério |
|---------|----------|
| `d` | Ordem padrão (y, x e área) |
| `a` | Área |
| `w` | Largura |
| `h` | Altura |
| `c` | Cor de preenchimento (ou cor da borda para linhas) |

---

# Como compilar

Dentro da pasta `src/` execute:

```bash
make
```

Compilar todos os testes unitários:

```bash
make tests
```

Executar todos os testes unitários:

```bash
make run-tests
```

Remover arquivos objeto, executáveis e arquivos temporários:

```bash
make clean
```

---

# Como executar

## Apenas arquivo `.geo`

```bash
./ted -e "diretório de entrada" -f "arquivo.geo" -o "diretório de saída"
```

## Arquivos `.geo` e `.qry`

```bash
./ted -e "diretório de entrada" -f "arquivo.geo" -q "arquivo.qry" -o "diretório de saída"
```

A ordem dos parâmetros pode ser alterada.

---

# Parâmetros do programa

| Parâmetro | Obrigatório | Descrição |
|------------|-------------|-----------|
| `-e path` | Não | Diretório-base de entrada |
| `-f arq.geo` | Sim | Arquivo `.geo` |
| `-q arq.qry` | Não | Arquivo de consultas |
| `-o path` | Sim | Diretório-base de saída |

---

# Arquivos de entrada

O programa utiliza dois arquivos principais:

- `.geo` → descrição das formas geométricas;
- `.qry` → consultas, modificações e ordenações sobre as formas.

---

# Comandos do arquivo `.geo`

| Comando | Parâmetros | Descrição |
|---------|------------|-----------|
| `c` | `i x y r corb corp` | Cria círculo |
| `r` | `i x y w h corb corp` | Cria retângulo |
| `l` | `i x1 y1 x2 y2 cor` | Cria linha |
| `t` | `i x y corb corp a texto` | Cria texto |
| `ts` | `fFamily fWeight fSize` | Define o estilo dos textos |

---

# Comandos do arquivo `.qry`

| Comando | Parâmetros | Descrição |
|---------|------------|-----------|
| `sel` | `x y w h` | Seleciona as formas inteiramente contidas na região |
| `find` | `k alg crit x y dw` | Ordena e posiciona os k menores elementos selecionados |
| `findrm` | `k alg crit x y dw` | Igual ao `find`, removendo os elementos excedentes |
| `cm` | `x y w h dx dy` | Clona as formas da região, desloca e seleciona os clones |
| `mc` | `corb corp` | Altera as cores das formas selecionadas |

---

# Organização das formas

As formas são armazenadas em uma Árvore Binária de Busca utilizando como ordem padrão:

1. Coordenada **y**;
2. Coordenada **x**;
3. Área da forma.

---

# Animação da ordenação

Durante a execução dos comandos `find` e `findrm`, o programa produz uma sequência de arquivos SVG representando cada etapa do algoritmo de ordenação.

Os snapshots recebem nomes sequenciais, por exemplo:

```text
arquivo-consulta000001.svg
arquivo-consulta000002.svg
arquivo-consulta000003.svg
...
```

Esses arquivos podem ser utilizados posteriormente para gerar animações.

---

# Arquivos de saída

## Apenas `.geo`

```text
arquivo.svg
```

---

## `.geo` + `.qry`

```text
arquivo.svg
arquivo-consulta.svg
arquivo-consulta.txt
arquivo-consulta000001.svg
arquivo-consulta000002.svg
...
```

---

# Saídas SVG

Os arquivos SVG representam:

- círculos;
- retângulos;
- linhas;
- textos;
- regiões de seleção;
- marcações dos elementos encontrados;
- estado final da árvore;
- snapshots intermediários da ordenação.

---

# Saídas TXT

Os arquivos TXT registram:

- comandos executados;
- formas selecionadas;
- resultados das consultas;
- atributos relevantes utilizados na ordenação;
- operações de clonagem;
- alterações de cores;
- remoções realizadas pelo `findrm`.

Formato:

```text
[*] comando executado
resultado da operação
```

---

# Testes unitários

O projeto utiliza o framework Unity.

Cada módulo possui seu respectivo arquivo de testes:

```text
t_modulo.c
```

Exemplos:

```text
t_ABB.c
t_comparadores.c
t_ordenacao.c
t_forma.c
t_svg.c
```

---

# Como executar os testes

Compilar todos os testes:

```bash
make tests
```

Executar todos os testes:

```bash
make run-tests
```

---

# O que os testes verificam

Os testes cobrem:

- inserção e remoção na ABB;
- buscas;
- critérios de comparação;
- algoritmos de ordenação;
- tratamento de `NULL`;
- gerenciamento de memória;
- funcionamento dos módulos;
- abertura e fechamento de arquivos;
- geração das saídas.

---

# Uso do Valgrind

O projeto foi desenvolvido considerando análise de memória com Valgrind.

Exemplo:

```bash
valgrind \
  --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  ./ted -e ./testes -f teste.geo -q consulta.qry -o ./saida
```

---

# Compilação resumida

```bash
make
make tests
make run-tests
make clean
```
