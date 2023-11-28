// Copyright (C) 2023 - Italo Portinho
// Para compilar(windows): g++ main.cpp -o main
#include <cstdio>
#include <cstdlib>
// #include "./redblack/redblack.hpp"
#include "./avl/avl.hpp"

int main() {
    // ArvoreRedBlack* minha_arvore = new ArvoreRedBlack { .raiz = 0};
    ArvoreAVL* minha_arvore = new ArvoreAVL{ .raiz = 0 };
    int chave = 0;
    for (size_t i = 0; i < 100; i++) {
        chave = rand();
        printf("\nInserindo %d", chave);
        InsertIt(minha_arvore, chave);
    }
    printf("\nterminou o FOR");

/*
    NoArvore* no_onze = InsertIt(minha_arvore, 11);
    NoArvore* no_dois = InsertIt(minha_arvore,  2);
    NoArvore* no_catorze = InsertIt(minha_arvore, 14);
    NoArvore* no_quinze = InsertIt(minha_arvore, 15);
    NoArvore* no_oito = InsertIt(minha_arvore, 8);
    NoArvore* no_sete = InsertIt(minha_arvore, 7);
    NoArvore* no_quatro  = InsertIt(minha_arvore, 4);
    NoArvore* no_um  = InsertIt(minha_arvore, 1);
    NoArvore* no_cinco  = InsertIt(minha_arvore, 5);

    
    NoArvore* no_onze = Insert(minha_arvore, minha_arvore->raiz, 0, 11);
    NoArvore* no_dois = Insert(minha_arvore, minha_arvore->raiz, 0, 2);
    NoArvore* no_catorze = Insert(minha_arvore, minha_arvore->raiz, 0, 14);
    NoArvore* no_quinze = Insert(minha_arvore, minha_arvore->raiz, 0, 15);
    NoArvore* no_oito = Insert(minha_arvore, minha_arvore->raiz, 0, 8); 
    NoArvore* no_sete = Insert(minha_arvore, minha_arvore->raiz, 0, 7);
    NoArvore* no_quatro  = Insert(minha_arvore, minha_arvore->raiz, 0, 4);
    NoArvore* no_um  = Insert(minha_arvore, minha_arvore->raiz, 0, 1);
    NoArvore* no_cinco  = Insert(minha_arvore, minha_arvore->raiz, 0, 5);
      */
    // Delete(minha_arvore, 7);
    // Delete(minha_arvore, 8);
    // Delete(minha_arvore, 15);
    // Delete(minha_arvore, 2);
    // printf("\npai do 8 == %d\n", no_oito->pai);
    // printf("\npai do 7 == %d\n", no_sete->pai);

    em_ordem(minha_arvore->raiz);
    printf("\nRAIZ == %d\n", minha_arvore->raiz->dado);
    

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
