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

node* rb_search(node *x, int key);
node* rb_search_pai(node *x, int key);
node* rb_search_min(node *x);
void rb_insert(node **raiz, int key);
void rb_insert_fixup(node **raiz, node *x);
void rb_delete(node **raiz, int key);
void rb_delete_fixup(node **raiz, node *x);
void left_rotate(node **raiz, node *x);
void right_rotate(node **raiz, node *x);
int rb_valid(node *raiz);
int rb_recurso(node *x);



int main(){
    node *raiz = NULL;
    int opcao = 0;
    int  valor;
    node *resultado = NULL;

    while(opcao != 5) {
	printf("\n--- ARVORE RUBRO-NEGRA ---");
    	printf("\n1. Inserir");
    	printf("\n2. Remover");
    	printf("\n3. Buscar");
    	printf("\n4. Validar");
    	printf("\n5. Sair");
    	printf("\nEscolha: "); 

        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Valor para inserir: ");
                scanf("%d", &valor);
                rb_insert(&raiz, valor);
                break;
            case 2:
                printf("Valor para remover: ");
                scanf("%d", &valor);
                rb_delete(&raiz, valor);
                break;
            case 3:
                printf("Valor para buscar: ");
                scanf("%d", &valor);
                resultado = rb_search(raiz, valor);
                if(resultado != NULL){
                    printf("Encontrado! Cor: %c\n", resultado->info->cor);
                } else {
                    printf("Nao encontrado.\n");
                }
                break;
            case 4:
                if(rb_valid(raiz)){
                    printf("Arvore correta!\n");
                }
                break;
            case 5:
                printf("Saindo...\n");
                break;
        }
    }
    return 0;
}

node* rb_search(node *x, int key){
    if(x == NULL || x->info->valor == key){
        return x;
    }
    if(x->info->valor < key){
        return rb_search(x->dir, key);
    }
    return rb_search(x->esq, key);
}

node* rb_search_pai(node *x, int key){
    if(x->info->valor == key){
        return x;
    }
    if(x->info->valor < key){
        if(x->dir == NULL){
            return x;
        }
        return rb_search_pai(x->dir, key);
    } else {
        if(x->esq == NULL){
            return x;
        }
        return rb_search_pai(x->esq, key);
    }
}

void rb_insert(node **raiz, int key){
    node *aux = malloc(sizeof(node));
    aux->info = malloc(sizeof(tipo_dado));
    aux->dir = NULL;
    aux->esq = NULL;
    aux->info->valor = key;
    aux->info->cor = 'V';

    if(*raiz != NULL){
        aux->pai = rb_search_pai(*raiz, key);
        if(aux->pai->info->valor < aux->info->valor){
            aux->pai->dir = aux;
        } else {
            aux->pai->esq = aux;
        }
        rb_insert_fixup(raiz, aux);
    } else {
        *raiz = aux;
        aux->pai = NULL;
        aux->info->cor = 'P';
    }
}

void rb_insert_fixup(node **raiz, node *x){
    while(x != *raiz && x->pai->info->cor == 'V'){
        if(x->pai == x->pai->pai->esq){
            node *y = x->pai->pai->dir;
            if(y != NULL && y->info->cor == 'V'){
                x->pai->info->cor = 'P';
                y->info->cor = 'P';
                x->pai->pai->info->cor = 'V';
                x = x->pai->pai;
            } else {
                if(x == x->pai->dir){
                    x = x->pai;
                    left_rotate(raiz, x);
                }
                x->pai->info->cor = 'P';
                x->pai->pai->info->cor = 'V';
                right_rotate(raiz, x->pai->pai);
            }
        } else {
            node *y = x->pai->pai->esq;
            if(y != NULL && y->info->cor == 'V'){
                x->pai->info->cor = 'P';
                y->info->cor = 'P';
                x->pai->pai->info->cor = 'V';
                x = x->pai->pai;
            } else {
                if(x == x->pai->esq){
                    x = x->pai;
                    right_rotate(raiz, x);
                }
                x->pai->info->cor = 'P';
                x->pai->pai->info->cor = 'V';
                left_rotate(raiz, x->pai->pai);
            }
        }
    }
    (*raiz)->info->cor = 'P';
}

void left_rotate(node **raiz, node *x){
    node *y = x->dir;
    x->dir = y->esq;
    if(y->esq != NULL){
        y->esq->pai = x;
    }
    y->pai = x->pai;
    if(y->pai != NULL){
        if(y->pai->info->valor < y->info->valor){
            y->pai->dir = y;
        } else {
            y->pai->esq = y;
        }
    } else {
        *raiz = y;
    }
    y->esq = x;
    x->pai = y;
}

void right_rotate(node **raiz, node *x){
    node *y = x->esq;
    x->esq = y->dir;
    if(y->dir != NULL){
        y->dir->pai = x;
    }
    y->pai = x->pai;
    if(y->pai != NULL){
        if(y->pai->info->valor < y->info->valor){
            y->pai->dir = y;
        } else {
            y->pai->esq = y;
        }
    } else {
        *raiz = y;
    }
    y->dir = x;
    x->pai = y;
}

void rb_delete(node **raiz, int key){
    node *z = rb_search(*raiz, key);
    if(z == NULL){
        return;
    }

    node *y = z;
    node *x;
    char cor_original_y = y->info->cor;

    if(z->esq == NULL){
        x = z->dir;
        if(z->pai == NULL){
            *raiz = x;
        } else if(z == z->pai->esq){
            z->pai->esq = x;
        } else {
            z->pai->dir = x;
        }
        if(x != NULL){
            x->pai = z->pai;
        }
    } else if(z->dir == NULL){
        x = z->esq;
        if(z->pai == NULL){
            *raiz = x;
        } else if(z == z->pai->esq){
            z->pai->esq = x;
        } else {
            z->pai->dir = x;
        }
        if(x != NULL){
            x->pai = z->pai;
        }
    } else {
        y = rb_search_min(z->dir);
        cor_original_y = y->info->cor;
        x = y->dir;

        if(y->pai == z){
            if(x != NULL) x->pai = y;
        } else {
            if(y->dir != NULL) y->dir->pai = y->pai;
            y->pai->esq = y->dir;
            
            y->dir = z->dir;
            y->dir->pai = y;
        }

        if(z->pai == NULL){
            *raiz = y;
        } else if(z == z->pai->esq){
            z->pai->esq = y;
        } else {
            z->pai->dir = y;
        }
        y->pai = z->pai;
        y->esq = z->esq;
        y->esq->pai = y;
        y->info->cor = z->info->cor;
    }

    free(z->info);
    free(z);

    if(cor_original_y == 'P' && x != NULL){
        rb_delete_fixup(raiz, x);
    }
}

void rb_delete_fixup(node **raiz, node *x){
    while(x != *raiz && x->info->cor == 'P'){
        if(x == x->pai->esq){
            node *z = x->pai->dir;
            if(z != NULL && z->info->cor == 'V'){
                z->info->cor = 'P';
                x->pai->info->cor = 'V';
                left_rotate(raiz, x->pai);
                z = x->pai->dir;
            }
            if(z->esq->info->cor == 'P' && z->dir->info->cor == 'P'){
                z->info->cor = 'V';
                x = x->pai;
            } else {
                if(z->dir->info->cor == 'P'){
                    z->esq->info->cor = 'P';
                    z->info->cor = 'V';
                    right_rotate(raiz, z);
                    z = x->pai->dir;
                }
                z->info->cor = x->pai->info->cor;
                x->pai->info->cor = 'P';
                z->dir->info->cor = 'P';
                left_rotate(raiz, x->pai);
                x = *raiz;
            }
        } else {
            node *z = x->pai->esq;
            if(z->info->cor == 'V'){
                z->info->cor = 'P';
                x->pai->info->cor = 'V';
                right_rotate(raiz, x->pai);
                z = x->pai->esq;
            }
            if(z->dir->info->cor == 'P' && z->esq->info->cor == 'P'){
                z->info->cor = 'V';
                x = x->pai;
            } else {
                if(z->esq->info->cor == 'P'){
                    z->info->cor = 'V';
                    z->dir->info->cor = 'P';
                    left_rotate(raiz, z);
                    z = x->pai->esq;
                }
                z->info->cor = x->pai->info->cor;
                x->pai->info->cor = 'P';
                z->esq->info->cor = 'P';
                right_rotate(raiz, x->pai);
                x = *raiz;
            }
        }
    }
    x->info->cor = 'P';
}

node* rb_search_min(node *x){
    if(x->esq == NULL){
        return x;
    }
    return rb_search_min(x->esq);
}

int rb_valid(node *raiz){
    if(raiz == NULL){
        return 1;
    }
    if(raiz->info->cor == 'V'){
        printf("\nErro: A raiz e vermelha!\n");
        return 0;
    }
    if(rb_recurso(raiz) == -1){
        printf("\nErro: Violacao de propriedades Rubro-Negra!\n");
        return 0;
    }
    return 1;
}

int rb_recurso(node *x){
    if(x == NULL){
        return 1;
    }
    if(x->info->cor == 'V'){
        if((x->esq != NULL && x->esq->info->cor == 'V') || (x->dir != NULL && x->dir->info->cor == 'V')){
            return -1;
        }
    }
    int h_esq = rb_recurso(x->esq);
    int h_dir = rb_recurso(x->dir);
    if(h_esq == -1 || h_dir == -1 || h_esq != h_dir){
        return -1;
    }
    if(x->info->cor == 'P'){
        return h_esq + 1;
    } else {
        return h_esq;
    }
}
