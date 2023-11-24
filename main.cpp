// Copyright (C) 2023 - Italo Portinho
// Para compilar(windows): g++ main.cpp -o main
#include <cstdio>
#include "./redblack/redblack.hpp"

int main() {
    ArvoreRedBlack* minha_arvore = new ArvoreRedBlack { .raiz = 0};

    NoArvore* no_onze = Insert(minha_arvore, 11);
    NoArvore* no_dois = Insert(minha_arvore, 2);
    NoArvore* no_catorze = Insert(minha_arvore, 14);
    NoArvore* no_quinze = Insert(minha_arvore, 15);
    NoArvore* no_oito = Insert(minha_arvore, 8);
    NoArvore* no_sete = Insert(minha_arvore, 7);
    NoArvore* no_quatro  = Insert(minha_arvore, 4);
    NoArvore* no_um  = Insert(minha_arvore, 1);
    NoArvore* no_cinco  = Insert(minha_arvore, 5);
    Delete(minha_arvore, 7);
    Delete(minha_arvore, 8);
    Delete(minha_arvore, 15);
    Delete(minha_arvore, 2);

    em_ordem(minha_arvore->raiz);
    printf("\nRAIZ == %d\n", minha_arvore->raiz->dado);
    //printf("\npai do 11 == %d\n", no_onze->pai->dado);

    /*
    NoArvore* no_um = Insert(minha_arvore, 1);
    NoArvore* no_dois = Insert(minha_arvore, 2);
    NoArvore* no_tres = Insert(minha_arvore, 3);
    NoArvore* no_quatro = Insert(minha_arvore, 4);
    NoArvore* no_cinco = Insert(minha_arvore, 5);
    NoArvore* no_seis = Insert(minha_arvore, 6);
    NoArvore* no_sete = Insert(minha_arvore, 7);
    NoArvore* no_oito = Insert(minha_arvore, 8);
    */
    /*
    NoArvore* no_41 = Insert(minha_arvore, 41);
    NoArvore* no_38 = Insert(minha_arvore, 38);
    NoArvore* no_31 = Insert(minha_arvore, 31);
    NoArvore* no_12 = Insert(minha_arvore, 12);
    NoArvore* no_19 = Insert(minha_arvore, 19);
    NoArvore* no_08 = Insert(minha_arvore, 8);

    


    Delete(minha_arvore, 8);
    Delete(minha_arvore, 12);
    Delete(minha_arvore, 19);
    Delete(minha_arvore, 31);
    Delete(minha_arvore, 38);
    
    em_ordem(minha_arvore->raiz);
    printf("\nRAIZ == %d\n", minha_arvore->raiz->dado);
    */
}
