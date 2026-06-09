/* ================================================================
   main.c — Caçador de Relíquias 🗡️
   Jogo RPG de terminal com Árvore Rubro-Negra como inventário
   EDA2 – 2026.1 | Grupo 24
   ================================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
  #include <windows.h>
  #define pausar(ms) Sleep(ms)
  #define limpar()   system("cls")
#else
  #include <unistd.h>
  #define pausar(ms) usleep((ms)*1000)
  #define limpar()   system("clear")
#endif
#include "rbtree.h"

/* ── ANSI Colors ── */
#define COR_RESET  "\033[0m"
#define COR_BOLD   "\033[1m"
#define COR_RED    "\033[1;31m"
#define COR_GREEN  "\033[1;32m"
#define COR_YELLOW "\033[1;33m"
#define COR_BLUE   "\033[1;34m"
#define COR_CYAN   "\033[1;36m"
#define COR_WHITE  "\033[1;37m"
#define COR_GRAY   "\033[0;90m"

/* ── Structs do Jogo ── */
typedef struct {
    char nome[64];
    int  hp, maxHp;
    int  ataque, defesa;
    int  nivel, exp, expProximo;
    RBTree *inventario;
} Heroi;

typedef struct {
    char nome[64];
    int  hp, maxHp;
    int  ataque, defesa;
    int  recompensaExp;
    int  dropItemId;   /* -1 = sem drop */
} Inimigo;

/* ── Banco de Itens do Jogo ── */
#define NUM_ITENS 12
static Item catalogoItens[NUM_ITENS] = {
    {1,  "Espada Enferrujada",    "Arma",     8,  "Uma espada velha, mas ainda util"},
    {3,  "Escudo de Madeira",     "Armadura",  5,  "Protege dos golpes mais fracos"},
    {5,  "Pocao de Cura P",      "Pocao",    25,  "Restaura 25 pontos de vida"},
    {7,  "Adaga Afiliada",        "Arma",     12, "Rapida e precisa"},
    {9,  "Armadura de Couro",     "Armadura",  9,  "Leve e resistente"},
    {11, "Pocao de Cura M",      "Pocao",    50,  "Restaura 50 pontos de vida"},
    {13, "Lança de Ferro",        "Arma",     18, "Alcance superior"},
    {15, "Elmo de Bronze",        "Armadura", 12, "Protege a cabeca"},
    {17, "Pocao de Cura G",      "Pocao",    99,  "Restaura quase toda a vida"},
    {19, "Espada Encantada",      "Arma",     25, "Brilha com magia antiga"},
    {21, "Armadura de Dragao",    "Armadura", 20, "Forjada com escamas de dragao"},
    {23, "Reliquia Lendaria",     "Especial", 50, "O tesouro que voce buscava!"},
};

/* ── Banco de Inimigos ── */
#define NUM_INIMIGOS 8
static Inimigo catalogoInimigos[NUM_INIMIGOS] = {
    {"Goblin",         30,  30,  8,  2, 20,  1},
    {"Lobo Cinzento",  40,  40, 10,  3, 30,  5},
    {"Esqueleto",      50,  50, 12,  4, 40,  3},
    {"Orc Guerreiro",  70,  70, 15,  6, 60,  7},
    {"Troll",          90,  90, 18,  8, 80,  9},
    {"Mago Sombrio",   60,  60, 22,  5, 90, 11},
    {"Dragao Negro",  150, 150, 28, 12, 150, 19},
    {"Guardiao Final",200, 200, 32, 15, 200, 23},
};

/* ── Salas ── */
typedef struct {
    const char *nome;
    const char *descricao;
    int inimigoIds[3];   /* indices em catalogoInimigos */
    int numInimigos;
    int itemIds[2];      /* indices em catalogoItens */
    int numItens;
} Sala;

#define NUM_SALAS 5
static Sala salas[NUM_SALAS] = {
    {"Floresta Sombria",
     "Arvores antigas cercam o caminho. Voce ouve passos...",
     {0, 1}, 2, {0, 2}, 2},
    {"Caverna Umida",
     "Gotas d'agua ecoam. Ossos cobrem o chao.",
     {2, 3}, 2, {1, 4}, 2},
    {"Torre em Ruinas",
     "Pedras desmoronadas e magia residual no ar.",
     {4, 5}, 2, {3, 5}, 2},
    {"Fortaleza Goblin",
     "Tochas iluminam corredores lodosos. Gritos ao longe.",
     {3, 4}, 2, {6, 7}, 2},
    {"Covil do Dragao",
     "Calor intenso. Ouro espalhado. O dragao te aguarda.",
     {6, 7}, 2, {8, 9}, 2},
};

/* ================================================================
   Funções utilitárias
   ================================================================ */
void linha(char c, int n) {
    for (int i = 0; i < n; i++) putchar(c);
    putchar('\n');
}

void digitar(const char *msg) {
    for (int i = 0; msg[i]; i++) {
        putchar(msg[i]);
        fflush(stdout);
        pausar(18);
    }
    putchar('\n');
}

void pressEnter(void) {
    printf(COR_GRAY "\n[Pressione ENTER para continuar]" COR_RESET);
    fflush(stdout);
    getchar();
}

int lerInt(int min, int max) {
    int v; char buf[32];
    while (1) {
        printf(COR_CYAN "> " COR_RESET);
        if (fgets(buf, sizeof(buf), stdin)) {
            if (sscanf(buf, "%d", &v) == 1 && v >= min && v <= max)
                return v;
        }
        printf(COR_RED "Opcao invalida. Digite entre %d e %d: " COR_RESET, min, max);
    }
}

/* ================================================================
   Funções do Herói
   ================================================================ */
void exibirStatus(Heroi *h) {
    printf(COR_BOLD "\n╔══════════════════════════════╗\n" COR_RESET);
    printf(COR_BOLD "  %s  |  Nível %d\n" COR_RESET, h->nome, h->nivel);
    printf("  HP:  " COR_RED "%d/%d" COR_RESET "\n", h->hp, h->maxHp);
    printf("  ATK: " COR_YELLOW "%d" COR_RESET "  DEF: " COR_BLUE "%d" COR_RESET "\n",
           h->ataque, h->defesa);
    printf("  EXP: %d/%d\n", h->exp, h->expProximo);
    printf(COR_BOLD "╚══════════════════════════════╝\n" COR_RESET);
}

void subirNivel(Heroi *h) {
    h->nivel++;
    h->maxHp    += 20;
    h->hp        = h->maxHp;
    h->ataque   += 3;
    h->defesa   += 2;
    h->expProximo = h->expProximo * 2;
    printf(COR_YELLOW "\n★ SUBIU DE NÍVEL! Agora é nível %d! ★\n" COR_RESET, h->nivel);
    printf("  HP máx: %d | ATK: %d | DEF: %d\n", h->maxHp, h->ataque, h->defesa);
}

void ganharExp(Heroi *h, int exp) {
    h->exp += exp;
    printf(COR_GREEN "  +%d EXP\n" COR_RESET, exp);
    while (h->exp >= h->expProximo) {
        h->exp -= h->expProximo;
        subirNivel(h);
    }
}

/* ================================================================
   Operações de Inventário com exibição educacional
   ================================================================ */
static void imprimirItem(Item *item) {
    const char *cor = strcmp(item->tipo, "Arma")     == 0 ? COR_RED   :
                      strcmp(item->tipo, "Pocao")    == 0 ? COR_GREEN  :
                      strcmp(item->tipo, "Armadura") == 0 ? COR_BLUE   : COR_YELLOW;
    printf("  %s[ID:%2d]%s %-22s (%s, val:%d)\n",
           cor, item->id, COR_RESET, item->nome, item->tipo, item->valor);
}

void exibirArvore(Heroi *h) {
    printf(COR_CYAN "\n╔═══ Estrutura da Árvore Rubro-Negra ═══╗" COR_RESET "\n");
    printf(COR_GRAY "  [V]=Vermelho  [P]=Preto  (chave=ID)\n" COR_RESET);
    linha('-', 45);
    if (rbt_vazia(h->inventario)) {
        printf("  (árvore vazia)\n");
    } else {
        rbt_mostrar(h->inventario, h->inventario->root, "", 0);
    }
    linha('-', 45);
    printf("  Itens no inventário: %d\n",
           rbt_tamanho(h->inventario, h->inventario->root));
    printf(COR_CYAN "╚═══════════════════════════════════════╝" COR_RESET "\n");
}

void coletarItem(Heroi *h, Item item) {
    printf(COR_YELLOW "\n🔑 INSERÇÃO na Árvore Rubro-Negra\n" COR_RESET);
    printf("   Inserindo: %s (ID:%d)\n", item.nome, item.id);
    printf(COR_GRAY "   → Percorre a árvore comparando IDs...\n" COR_RESET);
    printf(COR_GRAY "   → Nó inserido como VERMELHO, aplicando fixup...\n" COR_RESET);
    pausar(600);
    rbt_inserir(h->inventario, item);
    printf(COR_GREEN "   ✔ Item adicionado ao inventário!\n" COR_RESET);
    exibirArvore(h);
}

int usarPocao(Heroi *h) {
    if (rbt_vazia(h->inventario)) {
        printf(COR_RED "Inventário vazio!\n" COR_RESET);
        return 0;
    }
    printf("\n── Escolha uma Poção pelo ID ──\n");
    rbt_inOrder(h->inventario, h->inventario->root, imprimirItem);
    printf("ID (0 = cancelar): ");
    int id = lerInt(0, 99);
    if (id == 0) return 0;

    printf(COR_YELLOW "\n🔍 BUSCA na Árvore Rubro-Negra\n" COR_RESET);
    printf("   Buscando ID:%d...\n", id);
    Node *no = rbt_buscar(h->inventario, id);

    if (!no) {
        printf(COR_RED "   ✘ ID não encontrado na árvore!\n" COR_RESET);
        return 0;
    }
    if (strcmp(no->data.tipo, "Pocao") != 0) {
        printf(COR_RED "   ✘ %s não é uma poção!\n" COR_RESET, no->data.nome);
        return 0;
    }

    int cura = no->data.valor;
    h->hp = (h->hp + cura > h->maxHp) ? h->maxHp : h->hp + cura;
    printf(COR_GREEN "   ✔ Usou %s → +" COR_RESET COR_GREEN "%d HP!\n" COR_RESET,
           no->data.nome, cura);

    printf(COR_YELLOW "\n🗑  REMOÇÃO na Árvore Rubro-Negra\n" COR_RESET);
    printf("   Removendo ID:%d após uso...\n", id);
    printf(COR_GRAY "   → Aplicando transplant + deleteFixup...\n" COR_RESET);
    pausar(500);
    rbt_remover(h->inventario, id);
    printf(COR_GREEN "   ✔ Item removido e árvore rebalanceada!\n" COR_RESET);
    exibirArvore(h);
    return 1;
}

void listarInventario(Heroi *h) {
    printf(COR_CYAN "\n── Inventário (percurso In-Order) ──\n" COR_RESET);
    printf(COR_GRAY "   Percorre Esq → Raiz → Dir, produzindo IDs em ordem crescente\n\n" COR_RESET);
    if (rbt_vazia(h->inventario)) printf("  (vazio)\n");
    else rbt_inOrder(h->inventario, h->inventario->root, imprimirItem);
}

/* ================================================================
   Sistema de Batalha
   ================================================================ */
int batalhar(Heroi *h, Inimigo *ini) {
    printf(COR_RED "\n⚔  BATALHA: %s vs %s\n" COR_RESET, h->nome, ini->nome);
    linha('=', 40);

    while (h->hp > 0 && ini->hp > 0) {
        /* Ataque do herói */
        int dano = h->ataque - ini->defesa;
        if (dano < 1) dano = 1;
        ini->hp -= dano;
        printf(COR_GREEN "  Você atacou %s: -%d HP (%d/%d)\n" COR_RESET,
               ini->nome, dano, ini->hp < 0 ? 0 : ini->hp, ini->maxHp);

        if (ini->hp <= 0) break;

        /* Ataque do inimigo */
        int danoIni = ini->ataque - h->defesa;
        if (danoIni < 1) danoIni = 1;
        h->hp -= danoIni;
        printf(COR_RED "  %s atacou você: -%d HP (%d/%d)\n" COR_RESET,
               ini->nome, danoIni, h->hp < 0 ? 0 : h->hp, h->maxHp);

        /* Opção de usar poção durante batalha */
        if (h->hp > 0 && h->hp < h->maxHp / 2) {
            printf(COR_YELLOW "  [P] Usar poção  [C] Continuar lutando: " COR_RESET);
            char buf[8]; fgets(buf, sizeof(buf), stdin);
            if (buf[0] == 'p' || buf[0] == 'P') usarPocao(h);
        }
        pausar(300);
    }

    if (h->hp <= 0) {
        printf(COR_RED "\n☠  Você foi derrotado por %s...\n" COR_RESET, ini->nome);
        return 0;
    }
    printf(COR_GREEN "\n✔ %s derrotado!\n" COR_RESET, ini->nome);
    ganharExp(h, ini->recompensaExp);

    /* Drop de item */
    if (ini->dropItemId >= 0) {
        Item drop = catalogoItens[ini->dropItemId];
        printf(COR_YELLOW "  💎 %s dropou: %s!\n" COR_RESET, ini->nome, drop.nome);
        printf("  Coletar? (s/n): ");
        char buf[8]; fgets(buf, sizeof(buf), stdin);
        if (buf[0] == 's' || buf[0] == 'S') {
            /* Verifica se já existe no inventário */
            if (rbt_buscar(h->inventario, drop.id)) {
                printf(COR_GRAY "  Você já possui este item.\n" COR_RESET);
            } else {
                coletarItem(h, drop);
            }
        }
    }
    return 1;
}

/* ================================================================
   Telas
   ================================================================ */
void telaTitulo(void) {
    limpar();
    printf(COR_RED);
    printf("  ██████╗██████╗  █████╗ ██████╗ ██████╗  ██████╗ \n");
    printf(" ██╔════╝██╔══██╗██╔══██╗██╔══██╗╚════██╗██╔═████╗\n");
    printf(" ██║     ██████╔╝███████║██║  ██║ █████╔╝██║██╔██║\n");
    printf(" ██║     ██╔══██╗██╔══██║██║  ██║ ╚═══██╗████╔╝██║\n");
    printf(" ╚██████╗██║  ██║██║  ██║██████╔╝██████╔╝╚██████╔╝\n");
    printf("  ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝ ╚═════╝  ╚═════╝\n");
    printf(COR_RESET);
    printf(COR_YELLOW "      Caçador de Relíquias — RPG Terminal\n" COR_RESET);
    printf(COR_GRAY   "      Inventário gerenciado por Árvore Rubro-Negra\n\n" COR_RESET);
    printf(COR_CYAN   "      EDA2 – 2026.1 | Grupo 24\n" COR_RESET);
    printf(COR_GRAY   "      Ingrid Alves Rocha | Eric Camargo da Silva\n\n" COR_RESET);
    linha('-', 52);
}

void telaAjuda(void) {
    printf(COR_CYAN "\n── Como o Inventário Funciona ──\n" COR_RESET);
    printf("  A Árvore Rubro-Negra é uma BST auto-balanceada.\n");
    printf("  • INSERÇÃO: nó novo entra vermelho → fixup garante\n");
    printf("    propriedades (altura ≤ 2·log₂(n+1))\n");
    printf("  • BUSCA: O(log n) — percorre comparando IDs\n");
    printf("  • REMOÇÃO: transplant + deleteFixup recolore/rotaciona\n");
    printf("  • IN-ORDER: lista itens em ordem crescente de ID\n\n");
}

/* ================================================================
   Menu principal de uma sala
   ================================================================ */
void jogarSala(Heroi *h, Sala *sala, int *derrotado) {
    int inimigosDerrotados[3] = {0, 0, 0};
    int itensPegos[2] = {0, 0};
    int opcao;

    while (1) {
        limpar();
        printf(COR_YELLOW "\n═══ %s ═══\n" COR_RESET, sala->nome);
        digitar(sala->descricao);
        exibirStatus(h);

        printf("\n" COR_BOLD "O que fazer?\n" COR_RESET);

        int opt = 1;
        int inimivivo = 0;
        for (int i = 0; i < sala->numInimigos; i++) {
            if (!inimigosDerrotados[i]) {
                Inimigo *ini = &catalogoInimigos[sala->inimigoIds[i]];
                printf("  [%d] Lutar contra %s (HP:%d ATK:%d DEF:%d)\n",
                       opt++, ini->nome, ini->hp, ini->ataque, ini->defesa);
                inimivivo = 1;
            }
        }
        if (!inimivivo) {
            for (int i = 0; i < sala->numItens; i++) {
                if (!itensPegos[i]) {
                    Item *item = &catalogoItens[sala->itemIds[i]];
                    printf("  [%d] Pegar %s\n", opt++, item->nome);
                }
            }
        }
        printf("  [%d] Ver inventário\n",   opt++);
        printf("  [%d] Ver árvore RB\n",    opt++);
        printf("  [%d] Ajuda\n",            opt++);
        printf("  [%d] Próxima sala\n",     opt);

        int maxOpt = opt;
        opcao = lerInt(1, maxOpt);

        /* Processar opção dinamicamente */
        int cursor = 1;
        int escolhido = 0;

        /* Inimigos */
        for (int i = 0; i < sala->numInimigos && !escolhido; i++) {
            if (!inimigosDerrotados[i]) {
                if (opcao == cursor) {
                    /* Clonar inimigo para resetar HP por sala */
                    Inimigo ini = catalogoInimigos[sala->inimigoIds[i]];
                    int vivo = batalhar(h, &ini);
                    if (!vivo) { *derrotado = 1; return; }
                    inimigosDerrotados[i] = 1;
                    escolhido = 1;
                    pressEnter();
                }
                cursor++;
            }
        }
        /* Itens (só quando sala limpa) */
        if (!inimivivo) {
            for (int i = 0; i < sala->numItens && !escolhido; i++) {
                if (!itensPegos[i]) {
                    if (opcao == cursor) {
                        Item item = catalogoItens[sala->itemIds[i]];
                        if (rbt_buscar(h->inventario, item.id))
                            printf(COR_GRAY "Você já tem esse item.\n" COR_RESET);
                        else
                            coletarItem(h, item);
                        itensPegos[i] = 1;
                        escolhido = 1;
                        pressEnter();
                    }
                    cursor++;
                }
            }
        }

        if (!escolhido) {
            if (opcao == cursor)      { listarInventario(h); pressEnter(); }
            else if (opcao == cursor+1) { exibirArvore(h);    pressEnter(); }
            else if (opcao == cursor+2) { telaAjuda();        pressEnter(); }
            else { /* próxima sala */
                /* Verifica se limpou a sala */
                int todosDefeitos = 1;
                for (int i = 0; i < sala->numInimigos; i++)
                    if (!inimigosDerrotados[i]) { todosDefeitos = 0; break; }
                if (!todosDefeitos) {
                    printf(COR_RED "Derrote todos os inimigos antes de avançar!\n" COR_RESET);
                    pressEnter();
                } else {
                    return;
                }
            }
        }
    }
}

/* ================================================================
   Main
   ================================================================ */
int main(void) {
    srand((unsigned)time(NULL));

    telaTitulo();
    printf(COR_BOLD "\nBem-vindo, aventureiro!\n" COR_RESET);
    printf("Uma relíquia lendária foi roubada por um dragão.\n");
    printf("Explore 5 salas, derrote inimigos e recupere o tesouro!\n\n");

    /* Criar herói */
    Heroi heroi;
    printf("Digite seu nome: ");
    fgets(heroi.nome, sizeof(heroi.nome), stdin);
    heroi.nome[strcspn(heroi.nome, "\n")] = '\0';

    heroi.hp = heroi.maxHp = 100;
    heroi.ataque   = 15;
    heroi.defesa   = 5;
    heroi.nivel    = 1;
    heroi.exp      = 0;
    heroi.expProximo = 100;
    heroi.inventario = rbt_criar();

    /* Item inicial */
    printf(COR_YELLOW "\nVocê começa com uma Espada Enferrujada.\n" COR_RESET);
    coletarItem(&heroi, catalogoItens[0]); /* ID=1 */
    pressEnter();

    /* Loop de salas */
    int derrotado = 0;
    for (int i = 0; i < NUM_SALAS; i++) {
        limpar();
        printf(COR_CYAN "\n▶ SALA %d de %d: %s\n" COR_RESET,
               i+1, NUM_SALAS, salas[i].nome);
        pausar(800);
        jogarSala(&heroi, &salas[i], &derrotado);
        if (derrotado) break;
        printf(COR_GREEN "\n✔ Sala %d concluída! Avançando...\n" COR_RESET, i+1);
        pausar(1200);
    }

    /* Tela final */
    limpar();
    if (derrotado) {
        printf(COR_RED "\n");
        printf("  ╔═══════════════════════════╗\n");
        printf("  ║   GAME OVER — Tente novamente!  ║\n");
        printf("  ╚═══════════════════════════╝\n" COR_RESET);
    } else {
        printf(COR_YELLOW "\n");
        printf("  ╔══════════════════════════════════╗\n");
        printf("  ║   🏆 VITÓRIA! Relíquia Recuperada! ║\n");
        printf("  ╚══════════════════════════════════╝\n" COR_RESET);
        printf("\n%s vence como Nível %d!\n", heroi.nome, heroi.nivel);
        printf("\nInventário final (in-order pela Árvore RB):\n");
        rbt_inOrder(heroi.inventario, heroi.inventario->root, imprimirItem);
        printf("\nEstrutura final da Árvore Rubro-Negra:\n");
        exibirArvore(&heroi);
    }

    rbt_destruir(heroi.inventario);
    printf(COR_GRAY "\nObrigado por jogar! — EDA2 G24\n" COR_RESET);
    return 0;
}
