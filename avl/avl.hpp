// Copyright (C) 2023 - Italo Portinho
#include <cstdio>
#include <string>

class NoArvore {
 public:
    int dado;
    NoArvore* esq;
    NoArvore* dir;
    NoArvore* pai;
    int altura;
};

class ArvoreAVL {
 public:
    NoArvore* raiz;
};

void em_ordem(NoArvore* no) {
    if (no->esq) {
        em_ordem(no->esq);
    }
    printf("\n%d[", no->dado);
    printf("altura: %d, ", no->altura);
    printf("pai: %d]", no->pai ? no->pai->dado : 0);
    if (no->dir) {
        em_ordem(no->dir);
    }
    return;
}

int maior(int a, int b) {
    return (a > b) ? a : b;
}

int altura(NoArvore* no) {
    if (no == 0)
        return 0;
    return no->altura;
}

int fatorBalanceamento(NoArvore* N) {
    if (N == NULL)
        return 0;
    return altura(N->esq) - altura(N->dir);
}

NoArvore* RightRotate(ArvoreAVL* arvore, NoArvore* no) {
    // Complexidade: O(1)
    // A esquerda do nó x vira a dir do seu filho da esquerda y.
    // E X vira filho da direita de Y
    // obs: tem que ter Y, senão nao tem oq rotacionar.
    printf("\nRIGHT-ROTATE\n");
    printf("\n X = %d\n", no->dado);
    printf("\n PAI DO X = %d\n", no->pai->dado);
    printf("\n Y = %d\n", no->esq->dado);
    NoArvore* aux_y = no->esq;
    printf("\n PAI DO Y = %d\n", aux_y->pai->dado);
    // O pai de y agora é o pai de x.
    aux_y->pai = no->pai;

    // a direita de Y agora é esquerda de X
    no->esq = aux_y->dir;
    // E se a direita de Y não NIL, tb atualizamos seu pai para X.
    if (aux_y->dir) {
        aux_y->dir->pai = no;
    }

    // Definir se y fica a esq ou dir do pai do no x (se houver).
    // Este trecho é igual a LeftRotate
    if (no->pai) {
        if (no == no->pai->esq) {
            no->pai->esq = aux_y;
        } else {
            no->pai->dir = aux_y;
        }
    } else {
        arvore->raiz = aux_y;
    }

    // No x agora é o filho direito de y
    // O pai do nó x agora é y.
    aux_y->dir = no;
    no->pai = aux_y;

    // Atualiza a altura
    no->altura = 1 + maior(altura(no->esq), altura(no->dir));
    aux_y->altura = 1 + maior(altura(aux_y->esq), altura(aux_y->dir));
    printf("\n PAI DO X = %d\n", no->pai->dado);
    printf("\n PAI DO Y = %d\n", aux_y->pai->dado);
    return no;
}

NoArvore* LeftRotate(ArvoreAVL* arvore, NoArvore* no /* X */) {
    // Complexidade: O(1)
    // A direita do nó x vira a esquerda do seu filho da direita y.
    // E x vira filho da esquerda de Y
    // obs: tem que ter Y, senão nao tem oq rotacionar.
    printf("\nLEFT-ROTATE\n");
    printf("\n X = %d\n", no->dado);
    printf("\n Y = %d\n", no->dir ? no->dir->dado : 0);
    NoArvore* aux_y = no->dir;
    printf("\n PAI DO X = %d\n", no->pai->dado);
    printf("\n PAI DO Y = %d\n", aux_y->pai->dado);
    // O pai de y agora é o pai de x.
    aux_y->pai = no->pai;

    // a direita de Y agora é esquerda de X
    no->dir = aux_y->esq;
    // E se a esquerda de Y não NIL, tb atualizamos seu pai para X.
    if (aux_y->esq) {
        aux_y->esq->pai = no;
    }
    // Definir se y fica a esq ou dir do pai do no x (se houver).
    // Este trecho é igual a LeftRotate
    if (no->pai) {
        if (no == no->pai->esq) {
            no->pai->esq = aux_y;
        } else {
            no->pai->dir = aux_y;
        }
    } else {
        arvore->raiz = aux_y;
    }

    // No x agora é o filho esquerdo de y
    // O pai do nó x agora é y.
    aux_y->esq = no;
    no->pai = aux_y;

    // Atualiza a altura
    no->altura = 1 + maior(altura(no->esq), altura(no->dir));
    aux_y->altura = 1 + maior(altura(aux_y->esq), altura(aux_y->dir));
    printf("\n PAI DO X = %d\n", no->pai->dado);
    printf("\n PAI DO Y = %d\n", aux_y->pai->dado);
    return no;
}

void BalanceIt(NoArvore* no) {
    // Atualizar a altura
    no->altura = 1 + maior(altura(no->esq), altura(no->dir));
    if (no->pai == 0)
        return;
    BalanceIt(no->pai);
}

NoArvore* InsertIt(ArvoreAVL* arvore, int chave) {
    NoArvore* no = new NoArvore {
            .dado = chave
            , .esq = 0
            , .dir = 0
            , .pai = 0
            , .altura = 1
    };
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
    _posicao = no->pai;
    while (_posicao != 0) {
        // printf("\nposicao = %d", _posicao->dado);
        // printf(", altura = %d", _posicao->altura);
        _posicao->altura = 1 + maior(altura(_posicao->esq), altura(_posicao->dir));
        // printf(", NOVA_altura = %d", _posicao->altura);

        // Obter o Fator de balanceamento
        int bf = fatorBalanceamento(_posicao);

        // Left Left Case
        if (bf > 1 && chave < _posicao->esq->dado) {
            printf("\nLeft Left Case: %d\n", _posicao->dado);
            RightRotate(arvore, _posicao);
        }

        // Right Right Case
        if (bf < -1 && chave > _posicao->dir->dado) {
            printf("\nRight Right Case: %d\n", _posicao->dado);
            LeftRotate(arvore, _posicao);
        }

        // Left Right Case
        if (bf > 1 && chave > _posicao->esq->dado) {
            printf("\nLeft Right Case: %d\n",_posicao->dado);
            LeftRotate(arvore, _posicao->esq);
            RightRotate(arvore, _posicao);
        }

        // Right Left Case
        if (bf < -1 && chave < _posicao->dir->dado) {
            printf("\nRight Left Case :%d\n", _posicao->dado);
            RightRotate(arvore, _posicao->dir);
            LeftRotate(arvore, _posicao);
        }

        _posicao = _posicao->pai;
    }
    return no;
}

NoArvore* Insert(ArvoreAVL* arvore, NoArvore* no, NoArvore* no_pai,  int chave) {
    // Busca a posicao na arvore recursivamente para ir
    // atualizando as alturas dos nós.
    // Complexidade: O(lg n)
    // - A mesma de uma busca em uma Árvore Binária de Busca.

    if (no == 0) {
        NoArvore* new_node = new NoArvore {
            .dado = chave
            , .esq = 0
            , .dir = 0
            , .pai = no_pai
            , .altura = 1
        };
        if (no_pai == 0) {
            arvore->raiz = new_node;
        }

        return new_node;
    }

    if (chave < no->dado) {
        no->esq = Insert(arvore, no->esq, no, chave);
    } else {
        if (chave > no->dado)
            no->dir = Insert(arvore, no->dir, no, chave);
        else
            return no;
    }

    // Atualizar a altura
    no->altura = 1 + maior(altura(no->esq), altura(no->dir));

    // Obter o Fator de balanceamento
    int bf = fatorBalanceamento(no);


    if (chave == 7) {
        printf("\nposicao: %d, ", no ? no->dado : 0);
        printf("pai: %d, ", no_pai ? no_pai->dado : 0);
        printf("chave: %d \n", chave);
    }
    // Left Left Case
    if (bf > 1 && chave < no->esq->dado) {
        printf("\nLeft Left Case\n");
        return RightRotate(arvore, no);
    }

    // Right Right Case
    if (bf < -1 && chave > no->dir->dado) {
        printf("\nRight Right Case\n");
        return LeftRotate(arvore, no);
    }

    // Left Right Case
    if (bf > 1 && chave > no->esq->dado) {
        printf("\nLeft Right Case\n");
        no->esq = LeftRotate(arvore, no->esq);
        return RightRotate(arvore, no);
    }

    // Right Left Case
    if (bf < -1 && chave < no->dir->dado) {
        printf("\nRight Left Case :%d\n", no->dado);
        RightRotate(arvore, no->dir);
        NoArvore* um_no = LeftRotate(arvore, no);
        printf("um_no.pai == %d", um_no->pai);
        return um_no;
    }

    return no;
}

void Delete(NoArvore* no) {

}

void Search(int elemento) {

}
