/* ================================================================
   rbtree.h  —  Árvore Rubro-Negra (Red-Black Tree)
   EDA2 – 2026.1 | Grupo 24
   Aplicação: Inventário do Caçador de Relíquias
   ================================================================ */
#ifndef RBTREE_H
#define RBTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── Cores dos nós ── */
#define RED   0
#define BLACK 1

#define MAX_STR 64

/* ── Dado armazenado em cada nó ── */
typedef struct {
    int  id;
    char nome[MAX_STR];
    char tipo[MAX_STR];   /* "Arma" | "Pocao" | "Armadura" | "Especial" */
    int  valor;           /* dano / cura / defesa */
    char desc[MAX_STR];
} Item;

/* ── Nó da árvore ── */
typedef struct Node {
    Item         data;
    int          color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

/* ── Árvore ── */
typedef struct {
    Node *root;
    Node *nil;   /* sentinela: folha preta universal */
} RBTree;

/* ── Operações ── */
RBTree *rbt_criar(void);
void    rbt_inserir(RBTree *t, Item item);
Node   *rbt_buscar(RBTree *t, int id);
void    rbt_remover(RBTree *t, int id);
void    rbt_inOrder(RBTree *t, Node *x, void (*fn)(Item *));
void    rbt_mostrar(RBTree *t, Node *x, char *prefix, int isLeft);
int     rbt_vazia(RBTree *t);
int     rbt_tamanho(RBTree *t, Node *x);
void    rbt_destruir(RBTree *t);

#endif /* RBTREE_H */
