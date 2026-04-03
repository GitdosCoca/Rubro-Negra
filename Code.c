#include <stdio.h>
#include <stdlib.h>

typedef struct tipo_dado {
    int valor;
    //cor (V) vermelho e (P) preto
    char cor;
} tipo_dado;

typedef struct node {
    tipo_dado *info;
    struct node *esq;
    struct node *dir;
    struct node *pai;
} node;

// declaraçao do ponteiro da arvore
typedef node *tree;

node* rb_search(node *x, int key);
node* rb_search_pai(node *x, int key);
node* rb_search_min(node *x);
void rb_insert(node **tree, int key);
void rb_insert_fixup(node **tree, node *x);
void rb_delete(node **tree, int key);
void rb_delete_fixup(node **tree, node *x);
void left_rotate(node **tree, node *x);
void right_rotate(node **tree, node *x);
int rb_valid(node *tree);
int rb_recurso(node *x);

int main() {

    return 0;
}

node* rb_search(node *x, int key) {
    if (x == NULL || x->info->valor == key) {
        return x;
    }

    if (x->info->valor < key) {
        return rb_search(x->dir, key);
    } else {
        return rb_search(x->esq, key);
    }
}

node* rb_search_pai(node *x, int key) {
    if (x->info->valor == key) {
        printf("\n este item já existe e foi sobrescrito\n");
        return x;
    }

    if (x->info->valor < key) {
        if (x->dir == NULL) {
            return x;
        }
        return rb_search_pai(x->dir, key);
    } else {
        if (x->esq == NULL) {
            return x;
        }
        return rb_search_pai(x->esq, key);
    }
}

void rb_insert(node **tree, int key) {
    node *aux = malloc(sizeof(node));
    aux->info = malloc(sizeof(tipo_dado));

    aux->dir = NULL;
    aux->esq = NULL;
    aux->info->valor = key;
    aux->info->cor = 'V';

    if (*tree != NULL) {
        aux->pai = rb_search_pai(*tree, key);
        if (aux->pai->info->valor < aux->info->valor) {
            aux->pai->dir = aux;
        } else {
            aux->pai->esq = aux;
        }
        rb_insert_fixup(tree, aux);
    } else {
        *tree = aux;
        aux->pai = NULL;
        aux->info->cor = 'P';
    }
}

void rb_insert_fixup(node **tree, node *x) {
    while (x != *tree && x->pai->info->cor == 'V') {
        if (x->pai == x->pai->pai->esq) {
            node *y = x->pai->pai->dir;
            if (y != NULL && y->info->cor == 'V') {
                x->pai->info->cor = 'P';
                y->info->cor = 'P';
                x->pai->pai->info->cor = 'V';
                x = x->pai->pai;
            } else {
                if (x == x->pai->dir) {
                    x = x->pai;
                    left_rotate(tree, x);
                }
                x->pai->info->cor = 'P';
                x->pai->pai->info->cor = 'V';
                right_rotate(tree, x->pai->pai);
            }
        } else {
            node *y = x->pai->pai->esq;
            if (y != NULL && y->info->cor == 'V') {
                x->pai->info->cor = 'P';
                y->info->cor = 'P';
                x->pai->pai->info->cor = 'V';
                x = x->pai->pai;
            } else {
                if (x == x->pai->esq) {
                    x = x->pai;
                    right_rotate(tree, x);
                }
                x->pai->info->cor = 'P';
                x->pai->pai->info->cor = 'V';
                left_rotate(tree, x->pai->pai);
            }
        }
    }
    (*tree)->info->cor = 'P';
}

void left_rotate(node **tree, node *x) {
    node *y = x->dir;
    x->dir = y->esq;

    if (y->esq != NULL) {
        y->esq->pai = x;
    }

    y->pai = x->pai;

    if (y->pai != NULL) {
        if (y->pai->info->valor < y->info->valor) {
            y->pai->dir = y;
        } else {
            y->pai->esq = y;
        }
    } else {
        *tree = y;
    }

    y->esq = x;
    x->pai = y;
}

void right_rotate(node **tree, node *x) {
    node *y = x->esq;
    x->esq = y->dir;

    if (y->dir != NULL) {
        y->dir->pai = x;
    }

    y->pai = x->pai;

    if (y->pai != NULL) {
        if (y->pai->info->valor < y->info->valor) {
            y->pai->dir = y;
        } else {
            y->pai->esq = y;
        }
    } else {
        *tree = y;
    }

    y->dir = x;
    x->pai = y;
}

void rb_delete(node **tree, int key) {
    node *x = rb_search(*tree, key);
    if (x == NULL) {
        return;
    }

    node *y = x;
    char cor = y->info->cor;
    node *z;

    if (x->esq == NULL) {
        z = x->dir;
        if (x->pai != NULL) {
            if (x->pai->dir == x) x->pai->dir = z;
            else x->pai->esq = z;
        } else *tree = z;
        if (z != NULL) z->pai = x->pai;
    } else if (x->dir == NULL) {
        z = x->esq;
        if (x->pai != NULL) {
            if (x->pai->esq == x) x->pai->esq = z;
            else x->pai->dir = z;
        } else *tree = z;
        if (z != NULL) z->pai = x->pai;
    } else {
        y = rb_search_min(x->dir);
        cor = y->info->cor;
        z = y->dir;
    }

    free(x->info);
    free(x);

    if (cor == 'P' && z != NULL) {
        rb_delete_fixup(tree, z);
    }
}

void rb_delete_fixup(node **tree, node *x) {
    while (x != *tree && x->info->cor == 'P') {
        if (x == x->pai->esq) {
            node *z = x->pai->dir;
            if (z->info->cor == 'V') {
                z->info->cor = 'P';
                x->pai->info->cor = 'V';
                left_rotate(tree, x->pai);
                z = x->pai->dir;
            }

            if (z->esq->info->cor == 'P' && z->dir->info->cor == 'P') {
                z->info->cor = 'V';
                x = x->pai;
            } else {
                if (z->dir->info->cor == 'P') {
                    z->esq->info->cor = 'P';
                    z->info->cor = 'V';
                    right_rotate(tree, z);
                    z = x->pai->dir;
                }
                z->info->cor = x->pai->info->cor;
                x->pai->info->cor = 'P';
                z->dir->info->cor = 'P';
                left_rotate(tree, x->pai);
                x = *tree;
            }
        } else {
            node *z = x->pai->esq;
            if (z->info->cor == 'V') {
                z->info->cor = 'P';
                x->pai->info->cor = 'V';
                right_rotate(tree, x->pai);
                z = x->pai->esq;
            }

            if (z->dir->info->cor == 'P' && z->esq->info->cor == 'P') {
                z->info->cor = 'V';
                x = x->pai;
            } else {
                if (z->esq->info->cor == 'P') {
                    z->info->cor = 'V';
                    z->dir->info->cor = 'P';
                    left_rotate(tree, z);
                    z = x->pai->esq;
                }
                z->info->cor = x->pai->info->cor;
                x->pai->info->cor = 'P';
                z->esq->info->cor = 'P';
                right_rotate(tree, x->pai);
                x = *tree;
            }
        }
    }
    x->info->cor = 'P';
}

node* rb_search_min(node *x) {
    if (x->esq == NULL) {
        return x;
    }
    return rb_search_min(x->esq);
}

int rb_valid(node *tree) {
    if (tree == NULL) {
        return 1;
    }
    if (tree->info->cor == 'V') {
        printf("\nErro: A raiz e vermelha!\n");
        return 0;
    }
    if (rb_recurso(tree) == -1) {
        printf("\nErro: Violacao de propriedades Rubro-Negra!\n");
        return 0;
    }
    return 1;
}

int rb_recurso(node *x) {
    if (x == NULL) {
        return 1;
    }

    if (x->info->cor == 'V') {
        if ((x->esq != NULL && x->esq->info->cor == 'V') || (x->dir != NULL && x->dir->info->cor == 'V')) {
            return -1;
        }
    }

    int altura_esq = rb_recurso(x->esq);
    int altura_dir = rb_recurso(x->dir);

    if (altura_esq == -1 || altura_dir == -1) {
        return -1;
    }

    if (altura_esq != altura_dir) {
        return -1;
    }

    if (x->info->cor == 'P') {
        return altura_esq + 1;
    } else {
        return altura_esq;
    }
}
