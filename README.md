# Controle de Estoque (Vestuário) - Algoritmos de Ordenação

Sistema prático de gerenciamento e controle de estoque para uma loja de roupas, desenvolvido para demonstrar e comparar a eficiência de diferentes algoritmos de ordenação na disciplina de **Estruturas de Dados e Algoritmos 2 (EDA2)**.

## Alunos

<div align = "center">
<table>
  <tr>
    <td align="center"><a href="https://github.com/alvesingrid"><img style="border-radius: 50%;" src="https://github.com/alvesingrid.png" width="190;" alt=""/><br /><sub><b>Ingrid Alves</b></sub></a><br /><a href="Link git" title="Rocketseat"></a></td>
    <td align="center"><a href="https://github.com/Ericcs10"><img style="border-radius: 50%;" src="https://github.com/Ericcs10.png" width="190px;" alt=""/><br /><sub><b>Eric Camargo </b></sub></a><br />
  </tr>
</table>
</div>

## Autores

| Matrícula | Nome |
| :--- | :--- |
| 202045348 | **Ingrid Alves Rocha** |
| 202016168 | **Eric Camargo da Silva** |

## Sobre a Modelagem

O acervo gerencia itens modelados com identificadores voltados para filtragens do dia a dia de um e-commerce ou estoque físico:
* `código` (inteiro único)
* `descrição` e `tamanho` (strings)
* `preço` (float)
* `quantidade` (inteiro)

---

## Conexão Teórico-Prática dos Algoritmos

Cada método foi implementado visando resolver um problema específico de organização de listagem:

### 1. Insertion Sort (Filtro por Preço)
* **Aplicação Prática**: Ideal para ordenar subconjuntos ou organizar itens de um carrinho do menor para o maior preço.
* **Teoria**: Algoritmo simples, natural e **estável**. Muito utilizado no cotidiano (como na organização de cartas de baralho). Possui complexidade $O(n^2)$, apresentando o menor número de trocas e comparações quando o vetor já se encontra parcial ou totalmente ordenado.

### 2. Bubble Sort (Auditoria de Disponibilidade)
* **Aplicação Prática**: Empregado para ordenar o estoque com base na quantidade disponível, permitindo ao gestor identificar rapidamente produtos esgotados ou com baixo volume.
* **Teoria**: Realiza ordenações através de sucessivas comparações e trocas entre elementos adjacentes. O maior elemento vai "borbulhando" até alcançar sua posição final no vetor.

### 3. Shell Sort (Catálogo Geral por Código)
* **Aplicação Prática**: Utilizado para a ordenação veloz de todo o catálogo através dos códigos numéricos de identificação das peças.
* **Teoria**: Criado por Donald Shell em 1959, é o algoritmo de ordenação mais eficiente dentre os que possuem complexidade quadrática. Consiste em um refinamento direto do Insertion Sort, atuando sobre múltiplos segmentos do vetor simultaneamente.

---

## Benchmark de Desempenho

O sistema conta com um modo de **benchmark** (opção 5 do menu) que executa os três algoritmos sobre o estado atual do estoque e exibe, lado a lado, o número de **comparações** e **trocas** realizadas por cada um — sem alterar os dados exibidos.

Esse recurso permite observar na prática o que a teoria prevê sobre complexidade de algoritmos. Exemplo de saída com o estoque inicial (6 itens em ordem aleatória):

| Algoritmo      | Comparações | Trocas |
|----------------|-------------|--------|
| Insertion Sort | 9           | 5      |
| Bubble Sort    | 15          | 5      |
| Shell Sort     | 8           | 3      |

> O Shell Sort tende a realizar menos operações por trabalhar com intervalos (*gaps*) decrescentes, aproximando-se de $O(n \log n)$ na prática, enquanto Bubble Sort sempre percorre todas as comparações possíveis.

---

## Como Executar

1. Clone o repositório para a sua máquina:
```bash
   git clone https://github.com/indalvess/eda2-estoque-ordenacao.git
```

2. Acesse o diretório raiz do projeto:
```bash
   cd eda2-estoque-ordenacao
```

3. Compile os arquivos de código-fonte usando o `gcc`:
```bash
   gcc -o estoque src/ordenacao.c src/main.c
```

4. Execute a aplicação:
```bash
   ./estoque
```

## Screenshots
<p align="center">
  <img src="Documentos/screenshots/Print%201.png" alt="Print 1 do projeto" width="600"/>
</p>

<p align="center">
  <img src="Documentos/screenshots/Print%202.png" alt="Print 2 do projeto" width="600"/>
</p>

<p align="center">
  <img src="Documentos/screenshots/Print%203.png" alt="Print 3 do projeto" width="600"/>
</p>

## Apresentação 

<div align="center">
<a href="https://youtu.be/PoJ3FK-J3wM?si=VLjQ5nK-w6U8Dh7-"><img src="https://i.imgur.com/nNBEJk2.png" width="50%"></a>
</div>

<font size="3"><p style="text-align: center">Autor: <a href="https://github.com/alvesingrid">Ingrid Alves</a> e <a href="https://github.com/Ericcs10">Eric Camargo</a>.</p></font>