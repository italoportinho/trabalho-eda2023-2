// Copyright (C) 2023 - Italo Portinho
#include <cstdio>
#include <string>
enum color { RED, BLACK };
class NoArvoreRB {
 public:
    int dado;
    color cor;
    NoArvoreRB* esq;
    NoArvoreRB* dir;
    NoArvoreRB* pai;
};

class ArvoreRedBlack {
 public:
    NoArvoreRB* raiz;
};

//-------------------------------------------------------------------
//  c)      Percurso em-ordem (esq, no, dir)
//-------------------------------------------------------------------
void em_ordemRB(NoArvoreRB* no) {
    if (no->esq) {
        em_ordemRB(no->esq);
    }
    printf("%d[", no->dado);
    if (no->cor) {
        printf("cor: black, ");
    } else {
        printf("cor: red, ");
    }
    if (no->pai) {
        printf("pai: %d] \n", no->pai->dado);
    } else {
        printf("pai: %d] \n", no->pai);
    }

    if (no->dir) {
        em_ordemRB(no->dir);
    }
    return;
}

void RightRotateRB(ArvoreRedBlack* arvore, NoArvoreRB* no) {
    // Complexidade: O(1)
    // A esquerda do nó x vira a dir do seu filho da esquerda y.
    // E X vira filho da direita de Y
    // obs: tem que ter Y, senão nao tem oq rotacionar.
    // printf("\nRIGHT-ROTATE\n");
    // printf("\n X = %d\n", no->dado);
    // printf("\n Y = %d\n", no->esq->dado);
    NoArvoreRB* aux_y = no->esq;

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

void LeftRotateRB(ArvoreRedBlack* arvore, NoArvoreRB* no /* X */) {
    // Complexidade: O(1)
    // A direita do nó x vira a esquerda do seu filho da direita y.
    // E x vira filho da esquerda de Y
    // obs: tem que ter Y, senão nao tem oq rotacionar.
    // printf("\nLEFT-ROTATE\n");
    // printf("\n X = %d\n", no->dado);
    // printf("\n Y = %d\n", no->dir ? no->dir->dado : 0);
    NoArvoreRB* aux_y = no->dir;

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

NoArvoreRB* _rbinsert_fixup(ArvoreRedBlack* arvore, NoArvoreRB* no) {
    // O no inserido (z) é sempre vermelho.
    // Se z nao tiver pai, entao é a raíz e sera colorido no final da função.
    // Se z tiver pai e este for vermelho, é uma violação da regra RB e será
    // corrigido, pois o pai de um nó vermelho sempre deve ser preto.
    // Também, se z tem um pai vermelho, então é garantido que exista
    // o pai do pai de z, seu avô.
    NoArvoreRB* aux_y;
    NoArvoreRB* aux_z = no;

    while (aux_z->pai != 0 && aux_z->pai->cor == RED) {
        // testa se o pai de z é filho da esquerda.
        if (aux_z->pai == aux_z->pai->pai->esq) {
            // y é o tio da direita de z.
            aux_y = aux_z->pai->pai->dir;
            if (aux_y != 0 && aux_y->cor == RED) {
                // CASO 1
                // printf("\nCASO 1 (IF) - TIO VERMELHO\n");
                aux_z->pai->cor = BLACK;
                aux_y->cor = BLACK;
                aux_z->pai->pai->cor = RED;
                aux_z = aux_z->pai->pai;  // se possui tio, possui avo
            } else {
                // Se o tio do no z for preto (ou NIL) entramos nos casos 2 e 3.
                // No caso 2 z é filho da direita e no 3 é filho da esquerda.
                if (aux_z == aux_z->pai->dir) {
                    // CASO 2: z é filho da direita
                    aux_z = aux_z->pai;
                    // printf("\n CASO 2: z,pai e avo formam triang. Rotac pai\n");
                    LeftRotateRB(arvore, aux_z);
                } else {
                    // CASO 3: z é filho da esquerda
                    aux_z->pai->cor = BLACK;
                    aux_z->pai->pai->cor = RED;
                    // printf("\n CASO 3: z,pai e avo formam linha. Rotac avo\n");
                    RightRotateRB(arvore, aux_z->pai->pai);
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
                // printf("\nCASO 1.dir (ELSE) - TIO VERMELHO\n");
                aux_z->pai->cor = BLACK;
                aux_y->cor = BLACK;
                aux_z->pai->pai->cor = RED;
                aux_z = aux_z->pai->pai;
            } else {
                // CASO 2
                if (aux_z == aux_z->pai->esq) {
                    aux_z = aux_z->pai;
                    // printf("\n CASO 2.dir: z,pai,avo formam triang. Rot pai\n");
                    RightRotateRB(arvore, aux_z);
                } else {
                    // CASO 3: z é filho da direita
                    aux_z->pai->cor = BLACK;
                    aux_z->pai->pai->cor = RED;
                    // printf("\n CASO 3.dir: z,pai,avo formam linha. Rot avo\n");
                    LeftRotateRB(arvore, aux_z->pai->pai);
                }
            }
        }
    }
    arvore->raiz->cor = BLACK;
    return no;
}

NoArvoreRB* _rbinsert(ArvoreRedBlack* arvore, NoArvoreRB* no) {
    // Fazer o percurso descendente na árvore,
    // guardando o pai(y), para encontrar a posição de inserção(x).
    // Complexidade: O(lg n)
    // - A mesma de uma busca em uma Árvore Binária de Busca.
    NoArvoreRB* _pai = 0;
    NoArvoreRB* _posicao = arvore->raiz;
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
    return _rbinsert_fixup(arvore, no);
}

NoArvoreRB* Insert(ArvoreRedBlack* arvore, int elemento) {
    // printf("\n*************************************************\n");
    // printf("**************** Inserindo %d *******************", elemento);
    // printf("\n*************************************************\n");

    NoArvoreRB* new_node = new NoArvoreRB {
        .dado = elemento
        , .cor = RED
        , .esq = 0
        , .dir = 0
        , .pai = 0
    };

    return _rbinsert(arvore, new_node);
}

NoArvoreRB* TreeMinimum(NoArvoreRB* no) {
    // COMPLEXIDADE: O(lg_n) - percorre um caminho descendente na árvore
    NoArvoreRB* aux_x = no;
    while (aux_x->esq != 0) {
        // printf("\nTreeMinimum - no == %d\n", aux_x->dado);
        aux_x = aux_x->esq;
    }
    // printf("\nTreeMinimum final == %d\n", aux_x->dado);
    return aux_x;
}

NoArvoreRB* TreeSucessor(NoArvoreRB* no) {
    // COMPLEXIDADE: O(lg_n) - percorre no maximo um caminho descendente ou
    // ascendente na árvore.
    // Se houver filho direito, o sucesso sera o minimo dessa subarvore.
    NoArvoreRB* aux_x = no;
    if (aux_x->dir != 0) {
        return TreeMinimum(aux_x->dir);
    }
    NoArvoreRB* aux_y = aux_x->pai;
    // Nao havendo filho direito, subimos na arvore atualizando y e o no (x)
    // para seus pais, até que y seja um filho da esquerda, ou nulo(raíz)
    while (aux_y != 0 && aux_x == aux_y->dir) {
        aux_x = aux_y;
        aux_y = aux_y->pai;
    }
    return aux_y;
}

NoArvoreRB* Search(ArvoreRedBlack* arvore, int elemento) {
    // COMPLEXIDADE: O(lg_n) - percorre no maximo um caminho descendente
    NoArvoreRB* no = arvore->raiz;
    while (no != 0 && no->dado != elemento) {
        if (elemento < no->dado) {
            no = no->esq;
        } else {
            no = no->dir;
        }
    }
    // printf("\nSearch == %d\n", no->dado);
    return no;
}

void _rbdelete_fixup(ArvoreRedBlack* arvore, NoArvoreRB* x, NoArvoreRB* x_pai) {
    NoArvoreRB* irmao = 0;
    while (x != arvore->raiz && (x == 0 || x->cor == BLACK)) {
        // printf("\nX == %d\n", x ? x->dado : 0);
        // printf("\nX.pai == %d\n", x_pai ? x_pai->dado : 0);
        if (x == x_pai->esq) {
            // X é filho da esquerda
            irmao = x_pai->dir;
            // printf("\nirmao == %d\n", irmao->dado);
            // printf("\nirmao.cor == %d\n", irmao->cor);
            // printf("\nirmao.esq == %d\n", irmao->esq ? irmao->esq->dado : 0);
            // printf("\nirmao.dir == %d\n", irmao->dir ? irmao->dir->dado : 0);
            if (irmao) {
                if (irmao->cor == RED) {
                    // printf("\nDELETE FIX CASO 1 - irmão vermelho\n");
                    irmao->cor = BLACK;
                    x_pai->cor = RED;
                    LeftRotateRB(arvore, x_pai);
                }
                if((!irmao->esq || irmao->esq->cor == BLACK) && (!irmao->dir || irmao->dir->cor == BLACK)) {
                    // printf("\nDELETE FIX CASO 2 - irmao com ambos filhos pretos\n");
                    irmao->cor = RED;
                    x = x_pai;
                    // printf("\nNOVO X == %d\n", x ? x->dado : 0);
                } else {
                    if (irmao->dir && irmao->dir->cor == BLACK) {
                        // printf("\nDELETE FIX CASO 3 - irmao possui um filho preto\n");
                        if (irmao->esq) {
                            irmao->esq->cor = BLACK;
                        }
                        irmao->cor = RED;
                        RightRotateRB(arvore, irmao);
                        irmao = x_pai->dir;
                    }
                    // printf("\nDELETE FIX CASO 4 - irmao tem filho vermehlo\n");
                    irmao->cor = x_pai->cor;
                    x_pai->cor = BLACK;
                    if(irmao->dir) {
                        irmao->dir->cor = BLACK;
                    }
                    LeftRotateRB(arvore, x_pai);
                    x = arvore->raiz;
                }
            }
        } else {
            // x é filho da direita
            irmao = x_pai->esq;
            if (irmao) {
                if (irmao->cor == RED) {
                    // printf("\nDELETE FIX CASO 1 - irmão vermelho\n");
                    irmao->cor = BLACK;
                    x_pai->cor = RED;
                    RightRotateRB(arvore, x_pai);
                }
                if((!irmao->esq || irmao->esq->cor == BLACK) && (!irmao->dir || irmao->dir->cor == BLACK)) {
                    // printf("\nDELETE FIX CASO 2 - irmao com ambos filhos pretos\n");
                    irmao->cor = RED;
                    x = x_pai;
                } else {
                    if (irmao->esq && irmao->esq->cor == BLACK) {
                        // printf("\nDELETE FIX CASO 3 - irmao possui um filho preto\n");
                        if (irmao->dir) {
                            irmao->dir->cor = BLACK;
                        }
                        irmao->cor = RED;
                        LeftRotateRB(arvore, irmao);
                        irmao = x_pai->esq;
                    }
                    // printf("\nDELETE FIX CASO 4 - irmao tem filho vermehlo\n");
                    irmao->cor = x_pai->cor;
                    x_pai->cor = BLACK;
                    if(irmao->esq) {
                        irmao->esq->cor = BLACK;
                    }
                    RightRotateRB(arvore, x_pai);
                    x = arvore->raiz;
                }
            }
        }
    }
    if (x) {
        x->cor = BLACK;
    }
    return;
}

// Desfaz a conexão entre os nos u e v. e seta o pai de v como o pai de u.
void _rb_transplant(ArvoreRedBlack* T, NoArvoreRB* u, NoArvoreRB* v) {
    if (u->pai == 0) {
        T->raiz = v;
        v->pai = 0;
    } else {
        if (u == u->pai->esq) {
            u->pai->esq = v;  // v pode ser NIL
        } else {
            u->pai->dir = v;  // v pode ser NIL
        }
        if (v) {
            v->pai = u->pai;
        }
    }
    return;
}

void _rbdelete(ArvoreRedBlack* arvore, NoArvoreRB* z) {
    NoArvoreRB* aux_y = z;
    NoArvoreRB* aux_x = 0;
    NoArvoreRB* aux_x_pai = 0;
    color cor_original_y = aux_y->cor;

    if (!z->esq) {
        // z nao tem filho da esquerda (ou nenhum filho).
        // sobe o filho da direita (ou NIL).
        aux_x = z->dir;
        aux_x_pai = z->pai;
        _rb_transplant(arvore, z, z->dir);

    } else {
        if (!z->dir) {
            // z nao tem filho da direita.
            // sobe o filho da esquerda.
            aux_x = z->esq;
            aux_x_pai = z;
            aux_x_pai = z->pai;
            _rb_transplant(arvore, z, z->esq);

        } else {
            // z tem os dois filhos.
            //  sobe seu sucessor na árvore.
            aux_y = TreeSucessor(z);
            cor_original_y = aux_y->cor;
            aux_x = aux_y->dir;  // pode ser NIL
            if (aux_y->pai == z) {
                // o sucessor de z é um filho direto.
                if (aux_x) {
                    aux_x->pai = aux_y;
                      // ??? o pai de x já é Y
                }
                aux_x_pai = aux_y;
            } else {
                aux_x_pai = aux_y->pai;
                // Y nao é filho direto. z possui uma arvore da direita.
                // portanto z.dir nao sera nulo
                _rb_transplant(arvore, aux_y, aux_y->dir);
                aux_y->dir = z->dir;
                aux_y->dir->pai = aux_y;
            }
        }
        _rb_transplant(arvore, z, aux_y);
        aux_y->esq = z->esq;
        // z tem os dois filhos, portanto z.esq, q agora é tb o valor
        // de y.esq, nao é nulo.
        aux_y->esq->pai = aux_y;
        aux_y->cor = z->cor;
    }

    if (cor_original_y == BLACK) {
        _rbdelete_fixup(arvore, aux_x, aux_x_pai);
    }
    return;
}

void Delete(ArvoreRedBlack* arvore, int elemento) {
    NoArvoreRB* no = Search(arvore, elemento);
    if (no) {
        // printf("\nElemento [ %d ] encontrado. Prosseguindo com delete.\n"
        //, elemento);
        return _rbdelete(arvore, no);
    }
    printf("\nElemento [ %d ] nao pertence a arvore.\n", elemento);
    return;
}

int maiorRB(int a, int b) {
    return (a > b) ? a : b;
}

int calculaAltura(NoArvoreRB* no, int altura) {
    if (!no) {
        return 0;
    }
    int altura_esq = calculaAltura(no->esq, altura);
    int altura_dir = calculaAltura(no->dir, altura);
    int max_altura = maiorRB(altura_esq, altura_dir) + 1;

    return max_altura;
}