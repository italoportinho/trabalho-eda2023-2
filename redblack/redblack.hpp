// Copyright (C) 2023 - Italo Portinho
#include <cstdio>
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

void Insert(ArvoreRedBlack* arvore, int elemento) {
    NoArvore* new_node = new NoArvore {
        .dado = elemento
        , .cor = RED
        , .esq = 0
        , .dir = 0
        , .pai = 0
    };
    _rbinsert(arvore, new_node);
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
}

void _rbinsert_fixup(ArvoreRedBlack* arvore, NoArvore* no) {

}

void Delete(NoArvore* no) {

}

void Search(int elemento) {

}

void RightRotate(ArvoreRedBlack* arvore, NoArvore* no) {
    // Complexidade: O(1)
    // A esquerda do nó x vira a dir do seu filho da esquerda y.
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
}

void LeftRotate(ArvoreRedBlack* arvore, NoArvore* no) {
    // Complexidade: O(1)
    // A direita do nó x vira a esquerda do seu filho da direita y.
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
}
