// Copyright (C) 2023 - Italo Portinho
#include <cstdio>
#include <string>
enum color { RED, BLACK };
class NoArvore {
 public:
    int dado;
    color cor;
    NoArvore* esq;
    NoArvore* dir;
    NoArvore* pai;
};

class ArvoreRedBlack {
 public:
    NoArvore* raiz;
};

//-------------------------------------------------------------------
//  b)      Percurso em pós-ordem (esq, dir, nó)
//-------------------------------------------------------------------
void pos_ordem(NoArvore* no) {
    if (no->esq) {
        pos_ordem(no->esq);
    }
    if (no->dir) {
        pos_ordem(no->dir);
    }
    printf("%d ", no->dado);
    return;
}

//-------------------------------------------------------------------
//  c)      Percurso em-ordem (esq, no, dir)
//-------------------------------------------------------------------
void em_ordem(NoArvore* no) {
    if (no->esq) {
        em_ordem(no->esq);
    }
    printf("%d[", no->dado);
    if (no->cor) {
        printf("black] ");
    } else {
        printf("red] ");
    }

    if (no->dir) {
        em_ordem(no->dir);
    }
    return;
}

//-------------------------------------------------------------------
//  d)      Percurso em pré-ordem (no, esq, dir)
//-------------------------------------------------------------------
void pre_ordem(NoArvore* no) {
    printf("%d ", no->dado);
    if (no->esq) {
        pre_ordem(no->esq);
    }
    if (no->dir) {
        pre_ordem(no->dir);
    }
    return;
}

void RightRotate(ArvoreRedBlack* arvore, NoArvore* no) {
    // Complexidade: O(1)
    // A esquerda do nó x vira a dir do seu filho da esquerda y.
    printf("\n X = %d\n", no->dado);
    printf("\n Y = %d\n", no->esq->dado);
    NoArvore* aux_y = no->esq;
    no->esq = aux_y->dir;

    // O pai de y agora é o pai de x.
    // Este trecho é igual a LeftRotate
    aux_y->pai = no->pai;

    // Definir se y fica a esq ou dir do pai do no x (se houver).
    // Este trecho é igual a LeftRotate
    if (no->pai == 0) {
        arvore->raiz = aux_y;
    } else {
        if (no == no->pai->esq) {
            no->pai->esq = aux_y;
        } else {
            no->pai->dir = aux_y;
        }
    }

    // No x agora é o filho direito de y
    // O pai do nó x agora é y.
    aux_y->dir = no;
    no->pai = aux_y;
    return;
}

void LeftRotate(ArvoreRedBlack* arvore, NoArvore* no) {
    // Complexidade: O(1)
    // A direita do nó x vira a esquerda do seu filho da direita y.
    printf("\n X = %d\n", no->dado);
    printf("\n Y = %d\n", no->dir->dado);
    NoArvore* aux_y = no->dir;
    no->dir = aux_y->esq;

    // O pai de y agora é o pai de x.
    aux_y->pai = no->pai;

    // Definir se y fica a esq ou dir do pai do no x (se houver).
    if (no->pai == 0) {
        arvore->raiz = aux_y;
    } else {
        if (no == no->pai->esq) {
            no->pai->esq = aux_y;
        } else {
            no->pai->dir = aux_y;
        }
    }

    // No x agora é o filho esquerdo de y
    // O pai do nó x agora é y.
    aux_y->esq = no;
    no->pai = aux_y;
    return;
}

void _rbinsert_fixup(ArvoreRedBlack* arvore, NoArvore* no) {
    // O no inserido (z) é sempre vermelho.
    // Se z nao tiver pai, entao é a raíz e sera colorido no final da função.
    // Se z tiver pai e este for vermelho, é uma violação da regra RB e será
    // corrigido, pois o pai de um nó vermelho sempre deve ser preto.
    // Também, se z tem um pai vermelho, então é garantido que exista
    // o pai do pai de z, seu avô.
    NoArvore* aux_y;
    NoArvore* aux_z = no;

    while (aux_z->pai != 0 && aux_z->pai->cor == RED) {
        // testa se o pai de z é filho da esquerda.
        if (aux_z->pai == aux_z->pai->pai->esq) {
            // y é o tio da direita de z.
            aux_y = aux_z->pai->pai->dir;
            if (aux_y->cor == RED) {
                // CASO 1
                printf("\nCASO 1 (IF)\n");
                aux_z->pai->cor = BLACK;
                aux_y->cor = BLACK;
                aux_z->pai->pai->cor = RED;
                aux_z = aux_z->pai->pai;
            } else {
                // Se o tio do no z for preto entramos nos casos 2 e 3.
                // No caso 2 z é filho da direita e no 3 é filho da esquerda.
                if (aux_z == aux_z->pai->dir) {
                    // CASO 2: z é filho da direita
                    aux_z = aux_z->pai;
                    printf("\n CASO 2: LEFT-ROTATE(IF)\n");
                    LeftRotate(arvore, aux_z);
                } else {
                    // CASO 3: z é filho da esquerda
                    aux_z->pai->cor = BLACK;
                    aux_z->pai->pai->cor = RED;
                    printf("\n CASO 3: RIGHT-ROTATE(IF)\n");
                    RightRotate(arvore, aux_z->pai->pai);
                }
            }
        } else {
            // CASO SIMÉTRICO AO DA CLAUSULA IF
            // TROCAR ESQUERDA POR DIREITA
            // O pai de z é filho da direita.
            // y é o tio da esquerda de z.
            aux_y = aux_z->pai->pai->esq;
            if (aux_y != 0 && aux_y->cor == RED) {
                // CASO 1
                printf("\nCASO 1 (ELSE)\n");
                aux_z->pai->cor = BLACK;
                aux_y->cor = BLACK;
                aux_z->pai->pai->cor = RED;
                aux_z = aux_z->pai->pai;
            } else {
                // CASO 2
                if (aux_z == aux_z->pai->esq) {
                    aux_z = aux_z->pai;
                    printf("\n CASO 2: RIGHT-ROTATE(ELSE)\n");
                    RightRotate(arvore, aux_z);
                } else {
                    // CASO 3: z é filho da direita
                    aux_z->pai->cor = BLACK;
                    aux_z->pai->pai->cor = RED;
                    printf("\n CASO 3: LEFT-ROTATE(ELSE)\n");
                    LeftRotate(arvore, aux_z->pai->pai);
                }
            }
        }
    }
    arvore->raiz->cor = BLACK;
    return;
}

void _rbinsert(ArvoreRedBlack* arvore, NoArvore* no) {
    // Fazer o percurso descendente na árvore,
    // guardando o pai(y), para encontrar a posição de inserção(x).
    // Complexidade: O(lg n)
    // - A mesma de uma busca em uma Árvore Binária de Busca.
    NoArvore* _pai = 0;
    NoArvore* _posicao = arvore->raiz;
    while (_posicao != 0) {
        _pai = _posicao;
        if (no->dado < _posicao->dado) {
            _posicao = _posicao->esq;
        } else {
            _posicao = _posicao->dir;
        }
    }

    // Fazer o teste para saber se o no será filho direito ou esquerdo.
    // Complexidade: O(1)
    if (_pai == 0) {
        arvore->raiz = no;
    } else {
        no->pai = _pai;
        if (no->dado < _pai->dado) {
            _pai->esq = no;
        } else {
            _pai->dir = no;
        }
    }
    // Ponteiros esquerdo e direito do no sao null, e sua cor é RED
    // Chamar RB-INSERT-FIXUP: recolorir e rotacionar a árvore,
    // para mante-la balanceada.
    _rbinsert_fixup(arvore, no);
    return;
}

void Insert(ArvoreRedBlack* arvore, int elemento) {
    NoArvore* new_node = new NoArvore {
        .dado = elemento
        , .cor = RED
        , .esq = 0
        , .dir = 0
        , .pai = 0
    };
    _rbinsert(arvore, new_node);
    return;
}

void Delete(NoArvore* no) {
    return;
}

void Search(int elemento) {
    return;
}