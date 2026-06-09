´`# 🗡️ Caçador de Relíquias — Árvore Rubro-Negra

RPG de terminal interativo desenvolvido para demonstrar a **Árvore Rubro-Negra (Red-Black Tree)** na disciplina de **Estruturas de Dados e Algoritmos 2 (EDA2) – 2026.1**.

---

## Alunos

<div align="center">
<table>
  <tr>
    <td align="center"><a href="https://github.com/alvesingrid"><img style="border-radius: 50%;" src="https://github.com/alvesingrid.png" width="120" alt=""/><br/><sub><b>Ingrid Alves</b></sub></a></td>
    <td align="center"><a href="https://github.com/Ericcs10"><img style="border-radius: 50%;" src="https://github.com/Ericcs10.png" width="120" alt=""/><br/><sub><b>Eric Camargo</b></sub></a></td>
  </tr>
</table>
</div>

| Matrícula  | Nome                     |
|:-----------|:-------------------------|
| 202045348  | **Ingrid Alves Rocha**   |
| 202016168  | **Eric Camargo da Silva**|

---

## 🎮 Sobre o Projeto

**Caçador de Relíquias** é um RPG de dungeon em modo texto onde o jogador explora 5 salas, derrota inimigos e coleta itens para recuperar uma relíquia lendária roubada por um dragão.

O diferencial acadêmico: **o inventário do jogador é uma Árvore Rubro-Negra**. Cada ação do jogo demonstra visualmente uma operação real na estrutura:

| Ação no Jogo         | Operação na Árvore RB |
|----------------------|-----------------------|
| Coletar item         | **INSERT** + fixup    |
| Usar poção           | **SEARCH** → **DELETE** + fixup |
| Listar inventário    | **IN-ORDER** traversal |
| Visualizar árvore    | **printTree** com cores |

---

## 🌲 A Árvore Rubro-Negra

Uma **BST auto-balanceada** que garante altura máxima $2\log_2(n+1)$.

### Propriedades mantidas

1. Todo nó é **VERMELHO** ou **PRETO**
2. A **raiz** é sempre **PRETA**
3. Toda **folha** (nó sentinela `nil`) é **PRETA**
4. Filho de nó **VERMELHO** é obrigatoriamente **PRETO**
5. Todo caminho raiz → folha contém o mesmo número de nós **PRETOS** (black-height)

### Complexidade

| Operação | Pior caso |
|----------|-----------|
| Busca    | $O(\log n)$ |
| Inserção | $O(\log n)$ |
| Remoção  | $O(\log n)$ |

### Por que RB Tree no jogo?

O inventário cresce e diminui dinamicamente (coleta e uso de itens). Uma BST comum degradaria para $O(n)$; a Rubro-Negra garante eficiência mesmo no pior caso, graças às **rotações** e **recoloração** no `insertFixup` e `deleteFixup`.

---

## 📁 Estrutura do Projeto

```
G24_Arvores_EDA2-2026.1-/
├── src/
│   ├── rbtree.h    # Tipos e declarações da RB Tree
│   ├── rbtree.c    # Implementação completa (rotações, fixups)
│   └── main.c      # Jogo RPG + integração com a árvore
├── docs/
│   └── screenshots/
├── Makefile
└── README.md
```

---

## ▶️ Como Executar

### Pré-requisitos
- GCC instalado (`gcc --version`)
- Terminal com suporte a cores ANSI (Linux/macOS/WSL)

### Compilar e executar

```bash
# Clonar o repositório
git clone https://github.com/SEU_USUARIO/G24_Arvores_EDA2-2026.1-.git
cd G24_Arvores_EDA2-2026.1-

# Compilar
make

# Executar
./cacador

# Ou tudo de uma vez
make run
```

### Comandos do jogo

| Tecla | Ação |
|-------|------|
| Número | Escolher opção do menu |
| `s/n`  | Confirmar/cancelar ação |
| `P`    | Usar poção durante batalha |
| ENTER  | Continuar |

---

## 🏗️ Implementação Técnica

### Nó sentinela (`nil`)
Usamos um único nó `nil` preto como folha universal, eliminando verificações de `NULL` e simplificando as rotações.

### Rotações
- `leftRotate(t, x)` — pivô à esquerda
- `rightRotate(t, y)` — pivô à direita

### `insertFixup`
Corrige 3 casos após inserção de nó VERMELHO:
- **Caso 1**: Tio vermelho → recolorir, subir
- **Caso 2**: Tio preto, z é filho direito → rotação à esquerda
- **Caso 3**: Tio preto, z é filho esquerdo → rotação à direita + recolorir

### `deleteFixup`
Corrige 4 casos de "nó duplamente preto" após remoção, aplicando rotações e recoloração simétricas.

---

## 📊 Visualização da Árvore

O jogo exibe a árvore no terminal após cada operação:

```
/── [P] ID:9  Armadura de Couro   (val:9)
    /── [V] ID:7  Adaga Afiliada      (val:12)
        /── [P] ID:5  Pocao de Cura P     (val:25)
\── [P] ID:13 Lança de Ferro       (val:18)
    \── [V] ID:15 Elmo de Bronze       (val:12)
```
`[V]` = Nó Vermelho | `[P]` = Nó Preto

---

<font size="3"><p align="center">Projeto EDA2 — 2026.1 | Grupo 24<br/>
<a href="https://github.com/alvesingrid">Ingrid Alves</a> e <a href="https://github.com/Ericcs10">Eric Camargo</a></p></font>