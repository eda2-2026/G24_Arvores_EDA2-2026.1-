/* ================================================================
   rbtree.c  —  Implementação da Árvore Rubro-Negra
   EDA2 – 2026.1 | Grupo 24

   Propriedades mantidas:
     1. Todo nó é VERMELHO ou PRETO
     2. A raiz é PRETA
     3. Toda folha (nil) é PRETA
     4. Filho de nó vermelho é PRETO
     5. Todo caminho raiz→folha tem o mesmo nº de nós pretos
   ================================================================ */
#include "rbtree.h"

/* ──────────────────────────────────────────
   Criação
   ────────────────────────────────────────── */
RBTree *rbt_criar(void) {
    RBTree *t = (RBTree *)malloc(sizeof(RBTree));
    if (!t) { perror("malloc RBTree"); exit(1); }
    t->nil = (Node *)malloc(sizeof(Node));
    if (!t->nil) { perror("malloc nil"); exit(1); }
    t->nil->color  = BLACK;
    t->nil->left   = t->nil;
    t->nil->right  = t->nil;
    t->nil->parent = t->nil;
    t->root = t->nil;
    return t;
}

/* ──────────────────────────────────────────
   Rotações
   ────────────────────────────────────────── */
static void leftRotate(RBTree *t, Node *x) {
    Node *y   = x->right;
    x->right  = y->left;
    if (y->left != t->nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == t->nil)        t->root = y;
    else if (x == x->parent->left)  x->parent->left  = y;
    else                             x->parent->right = y;
    y->left   = x;
    x->parent = y;
}

static void rightRotate(RBTree *t, Node *y) {
    Node *x   = y->left;
    y->left   = x->right;
    if (x->right != t->nil)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == t->nil)        t->root = x;
    else if (y == y->parent->right) y->parent->right = x;
    else                             y->parent->left  = x;
    x->right  = y;
    y->parent = x;
}

/* ──────────────────────────────────────────
   Inserção
   ────────────────────────────────────────── */
static void insertFixup(RBTree *t, Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;   /* tio */
            if (y->color == RED) {                 /* Caso 1 */
                z->parent->color         = BLACK;
                y->color                 = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {       /* Caso 2 */
                    z = z->parent;
                    leftRotate(t, z);
                }
                z->parent->color         = BLACK;  /* Caso 3 */
                z->parent->parent->color = RED;
                rightRotate(t, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;    /* tio (simétrico) */
            if (y->color == RED) {                 /* Caso 1 */
                z->parent->color         = BLACK;
                y->color                 = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {        /* Caso 2 */
                    z = z->parent;
                    rightRotate(t, z);
                }
                z->parent->color         = BLACK;  /* Caso 3 */
                z->parent->parent->color = RED;
                leftRotate(t, z->parent->parent);
            }
        }
    }
    t->root->color = BLACK;
}

void rbt_inserir(RBTree *t, Item item) {
    Node *z = (Node *)malloc(sizeof(Node));
    if (!z) { perror("malloc Node"); exit(1); }
    z->data   = item;
    z->color  = RED;
    z->left   = t->nil;
    z->right  = t->nil;
    z->parent = t->nil;

    Node *y = t->nil;
    Node *x = t->root;
    while (x != t->nil) {
        y = x;
        if (z->data.id < x->data.id) x = x->left;
        else                          x = x->right;
    }
    z->parent = y;
    if (y == t->nil)                  t->root    = z;
    else if (z->data.id < y->data.id) y->left    = z;
    else                               y->right   = z;

    insertFixup(t, z);
}

/* ──────────────────────────────────────────
   Busca
   ────────────────────────────────────────── */
Node *rbt_buscar(RBTree *t, int id) {
    Node *x = t->root;
    while (x != t->nil) {
        if (id == x->data.id) return x;
        x = (id < x->data.id) ? x->left : x->right;
    }
    return NULL;
}

/* ──────────────────────────────────────────
   Remoção
   ────────────────────────────────────────── */
static void transplant(RBTree *t, Node *u, Node *v) {
    if (u->parent == t->nil)       t->root        = v;
    else if (u == u->parent->left)  u->parent->left  = v;
    else                            u->parent->right = v;
    v->parent = u->parent;
}

static Node *minimum(RBTree *t, Node *x) {
    while (x->left != t->nil) x = x->left;
    return x;
}

static void deleteFixup(RBTree *t, Node *x) {
    while (x != t->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {                             /* Caso 1 */
                w->color         = BLACK;
                x->parent->color = RED;
                leftRotate(t, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) { /* Caso 2 */
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {                /* Caso 3 */
                    w->left->color = BLACK;
                    w->color       = RED;
                    rightRotate(t, w);
                    w = x->parent->right;
                }
                w->color          = x->parent->color;          /* Caso 4 */
                x->parent->color  = BLACK;
                w->right->color   = BLACK;
                leftRotate(t, x->parent);
                x = t->root;
            }
        } else {                                               /* Simétrico */
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color         = BLACK;
                x->parent->color = RED;
                rightRotate(t, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color        = RED;
                    leftRotate(t, w);
                    w = x->parent->left;
                }
                w->color         = x->parent->color;
                x->parent->color = BLACK;
                w->left->color   = BLACK;
                rightRotate(t, x->parent);
                x = t->root;
            }
        }
    }
    x->color = BLACK;
}

void rbt_remover(RBTree *t, int id) {
    Node *z = rbt_buscar(t, id);
    if (!z) return;

    Node *y = z;
    Node *x;
    int   yColor = y->color;

    if (z->left == t->nil) {
        x = z->right;
        transplant(t, z, z->right);
    } else if (z->right == t->nil) {
        x = z->left;
        transplant(t, z, z->left);
    } else {
        y      = minimum(t, z->right);
        yColor = y->color;
        x      = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(t, y, y->right);
            y->right         = z->right;
            y->right->parent = y;
        }
        transplant(t, z, y);
        y->left         = z->left;
        y->left->parent = y;
        y->color        = z->color;
    }
    free(z);
    if (yColor == BLACK) deleteFixup(t, x);
}

/* ──────────────────────────────────────────
   Traversal & Visualização
   ────────────────────────────────────────── */
void rbt_inOrder(RBTree *t, Node *x, void (*fn)(Item *)) {
    if (x != t->nil) {
        rbt_inOrder(t, x->left, fn);
        fn(&x->data);
        rbt_inOrder(t, x->right, fn);
    }
}

/* Exibe a árvore estilo "pretty-print" com cores ANSI */
void rbt_mostrar(RBTree *t, Node *x, char *prefix, int isLeft) {
    if (x == t->nil) return;

    char newPrefix[256];

    /* Filho direito primeiro (top of screen = right subtree) */
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix,
             isLeft ? "|   " : "    ");
    rbt_mostrar(t, x->right, newPrefix, 0);

    /* Nó atual */
    const char *cor   = (x->color == RED)
                        ? "\033[1;31m[V]\033[0m"   /* vermelho */
                        : "\033[1;90m[P]\033[0m";  /* preto */
    printf("%s%s── %s ID:%-3d %-22s (val:%d)\n",
           prefix,
           isLeft ? "\\── " : "/── ",
           cor, x->data.id, x->data.nome, x->data.valor);

    /* Filho esquerdo */
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix,
             isLeft ? "    " : "|   ");
    rbt_mostrar(t, x->left, newPrefix, 1);
}

/* ──────────────────────────────────────────
   Utilitários
   ────────────────────────────────────────── */
int rbt_vazia(RBTree *t) {
    return t->root == t->nil;
}

int rbt_tamanho(RBTree *t, Node *x) {
    if (x == t->nil) return 0;
    return 1 + rbt_tamanho(t, x->left) + rbt_tamanho(t, x->right);
}

static void destruirRec(RBTree *t, Node *x) {
    if (x != t->nil) {
        destruirRec(t, x->left);
        destruirRec(t, x->right);
        free(x);
    }
}

void rbt_destruir(RBTree *t) {
    destruirRec(t, t->root);
    free(t->nil);
    free(t);
}
