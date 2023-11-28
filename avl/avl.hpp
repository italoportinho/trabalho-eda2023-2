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
    // printf("\nRIGHT-ROTATE(%d)\n", no->dado);
    // printf("\n X = %d\n", no->dado);
    // printf("\n PAI DO X = %d\n", no->pai->dado);
    // printf("\n Y = %d\n", no->esq->dado);
    NoArvore* aux_y = no->esq;
    // printf("\n PAI DO Y = %d\n", aux_y->pai->dado);
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
        if (arvore)
            arvore->raiz = aux_y;
    }

    // No x agora é o filho direito de y
    // O pai do nó x agora é y.
    aux_y->dir = no;
    no->pai = aux_y;

    // Atualiza a altura
    no->altura = 1 + maior(altura(no->esq), altura(no->dir));
    aux_y->altura = 1 + maior(altura(aux_y->esq), altura(aux_y->dir));
    // printf("\n PAI DO X = %d\n", no->pai->dado);
    // printf("\n PAI DO Y = %d\n", aux_y->pai->dado);
    return no;
}

NoArvore* LeftRotate(ArvoreAVL* arvore, NoArvore* no /* X */) {
    // Complexidade: O(1)
    // A direita do nó x vira a esquerda do seu filho da direita y.
    // E x vira filho da esquerda de Y
    // obs: tem que ter Y, senão nao tem oq rotacionar.
    // printf("\nLEFT-ROTATE(%d)\n", no->dado);
    // printf("\n X = %d\n", no->dado);
    // printf("\n Y = %d\n", no->dir ? no->dir->dado : 0);
    NoArvore* aux_y = no->dir;
    // printf("\n PAI DO X = %d\n", no->pai->dado);
    // printf("\n PAI DO Y = %d\n", aux_y->pai->dado);
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
        if (arvore)
            arvore->raiz = aux_y;
    }

    // No x agora é o filho esquerdo de y
    // O pai do nó x agora é y.
    aux_y->esq = no;
    no->pai = aux_y;

    // Atualiza a altura
    no->altura = 1 + maior(altura(no->esq), altura(no->dir));
    aux_y->altura = 1 + maior(altura(aux_y->esq), altura(aux_y->dir));
    // printf("\n PAI DO X = %d\n", no->pai ? no->pai->dado : 0);
    // printf("\n PAI DO Y = %d\n", aux_y->pai ? aux_y->pai->dado : 0);
    return no;
}

NoArvore *RightRotateAlt(NoArvore *y) {
    NoArvore *x = y->esq;
    NoArvore *T2 = x->dir;

    // Perform rotation
    x->dir = y;
    y->esq = T2;

    // Update heights
    y->altura = maior(altura(y->esq), altura(y->dir)) + 1;
    x->altura = maior(altura(x->esq), altura(x->dir)) + 1;

    // Return new root
    return x;
}

NoArvore* LeftRotateAlt(NoArvore* x) {
    NoArvore *y = x->dir;
    NoArvore *T2 = y->esq;

    // Perform rotation
    y->esq = x;
    x->dir = T2;

    // Update heights
    x->altura = maior(altura(x->esq), altura(x->dir)) + 1;
    y->altura = maior(altura(y->esq), altura(y->dir)) + 1;

    // Return new root
    return y;
}

void BalanceIt(NoArvore* no) {
    // Atualizar a altura
    no->altura = 1 + maior(altura(no->esq), altura(no->dir));
    if (no->pai == 0)
        return;
    BalanceIt(no->pai);
}

NoArvore* InsertIt(ArvoreAVL* arvore, int chave) {
    // Versão iterativa do insert
    // Fazer o percurso descendente na árvore,
    // guardando o pai(y), para encontrar a posição de inserção(x).
    // Complexidade: O(lg n)
    // - A mesma de uma busca em uma Árvore Binária de Busca.
    NoArvore* no = new NoArvore {
            .dado = chave
            , .esq = 0
            , .dir = 0
            , .pai = 0
            , .altura = 1
    };

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
    int bf = 0;
    while (_posicao != 0) {
        // printf("\nposicao = %d", _posicao->dado);
        // printf(", altura = %d", _posicao->altura);
        _posicao->altura = 1 + maior(altura(_posicao->esq), altura(_posicao->dir));
        // printf(", NOVA_altura = %d", _posicao->altura);

        // Obter o Fator de balanceamento
        bf = fatorBalanceamento(_posicao);

        // printf("\nFator de Balanceamento(%d) == ", _posicao->dado);
        // printf("%d\n", bf);
        // Left Left Case
        if (bf > 1 && chave < _posicao->esq->dado) {
            // printf("\nLeft Left Case: %d\n", _posicao->dado);
            RightRotate(arvore, _posicao);
            // bf = 0;
            continue;
        }

        // Right Right Case
        if (bf < -1 && chave > _posicao->dir->dado) {
            // printf("\nRight Right Case: %d\n", _posicao->dado);
            LeftRotate(arvore, _posicao);
            // bf = 0;
            continue;
        }

        // Left Right Case
        if (bf > 1 && chave > _posicao->esq->dado) {
            // printf("\nLeft Right Case: %d\n", _posicao->dado);
            LeftRotate(arvore, _posicao->esq);
            RightRotate(arvore, _posicao);
            // bf = 0;
            continue;
        }

        // Right Left Case
        if (bf < -1 && chave < _posicao->dir->dado) {
            // printf("\nRight Left Case: %d\n", _posicao->dado);
            RightRotate(arvore, _posicao->dir);
            LeftRotate(arvore, _posicao);
            // bf = 0;
            continue;
        }
        _posicao = _posicao->pai;
    }
    return no;
}

NoArvore* InsertRec(NoArvore* no, int chave) {
    // Busca a posicao na arvore recursivamente para ir
    // atualizando as alturas dos nós.
    // Complexidade: O(lg n)
    // - A mesma de uma busca em uma Árvore Binária de Busca.

    if (no == 0) {
        NoArvore* new_node = new NoArvore {
            .dado = chave
            , .esq = 0
            , .dir = 0
            , .altura = 1
        };

        return new_node;
    }

    if (chave < no->dado) {
        no->esq = InsertRec(no->esq, chave);
    } else {
        if (chave > no->dado)
            no->dir = InsertRec(no->dir, chave);
        else
            return no;
    }

    // Atualizar a altura
    no->altura = 1 + maior(altura(no->esq), altura(no->dir));

    // Obter o Fator de balanceamento
    int bf = fatorBalanceamento(no);

    // Left Left Case
    if (bf > 1 && chave < no->esq->dado) {
        // printf("\nLeft Left Case\n");
        return RightRotateAlt(no);
    }

    // Right Right Case
    if (bf < -1 && chave > no->dir->dado) {
        // printf("\nRight Right Case\n");
        return LeftRotateAlt(no);
    }

    // Left Right Case
    if (bf > 1 && chave > no->esq->dado) {
        // printf("\nLeft Right Case\n");
        no->esq = LeftRotateAlt(no->esq);
        return RightRotateAlt(no);
    }

    // Right Left Case
    if (bf < -1 && chave < no->dir->dado) {
        // printf("\nRight Left Case :%d\n", no->dado);
        no->dir = RightRotateAlt(no->dir);
        return LeftRotateAlt(no);
    }

    return no;
}

int calculaAlturaAVL(NoArvore* no, int altura) {
    if (!no) {
        return 0;
    }
    int altura_esq = calculaAlturaAVL(no->esq, altura);
    int altura_dir = calculaAlturaAVL(no->dir, altura);
    int max_altura = maior(altura_esq, altura_dir) + 1;

    return max_altura;
}

void Delete(NoArvore* no) {

}
