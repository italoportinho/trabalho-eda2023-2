// Copyright (C) 2023 - Italo Portinho
// Para compilar(windows): g++ main.cpp -o main

#include <cstdio>
#include <cstdlib>
#include <map>
#include <ctime>
#include "./redblack/redblack.hpp"
#include "./avl/avl.hpp"

int main() {
    ArvoreRedBlack* rb_tree = new ArvoreRedBlack { .raiz = 0};
    ArvoreAVL* avl_tree = new ArvoreAVL{ .raiz = 0 };
    NoArvore* avl_root = 0;
    std::map<int, int> map_tree{};
    int chave = 0;
    std::clock_t avl_start = std::clock();
    for (int i = 0; i < 100000; i++) {
        // printf("\nIteracao: %d", i);
        chave = rand();
        avl_root = InsertRec(avl_root, chave);
    }
    /*
    for (int i = 0; i < 5900; i++) {
        chave = rand();
        InsertIt(avl_tree, chave);
    }
    */
    std::clock_t avl_end = std::clock();
    std::clock_t rb_start = std::clock();
    int rb_deletes = 0;
    for (int i = 0; i < 100000; i++) {
        // printf("\nIteracao: %d", i);
        chave = rand();
        Insert(rb_tree, chave);
        if(i > 100 && i % 100 == 0) {
            rb_deletes++;
            Delete(rb_tree, rand());
        }
    }
    std::clock_t rb_end = std::clock();
    std::clock_t map_start = std::clock();
    int map_deletes = 0;
    for (int i = 0; i < 100000; i++) {
        chave = rand();
        map_tree[chave] = chave;
        if(i > 100 && i % 100 == 0) {
            map_deletes++;
            map_tree.extract(rand());
        }
    }
    std::clock_t map_end = std::clock();
    // printf("\nterminou o FOR");

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

    // em_ordem(minha_arvore->raiz);
    printf("\nRAIZ RB == %d , ", rb_tree->raiz->dado);
    printf("altura RB == %d, ", calculaAltura(rb_tree->raiz, 0));
    printf("deletes RB == %d , ", rb_deletes);
    double rb_time_ms = 1000.0*(rb_end - rb_start)/CLOCKS_PER_SEC;
    printf("RB ms == %f\n ", rb_time_ms);

    printf("\nRAIZ AVL == %d , ", avl_root->dado);
    printf("altura AVL == %d ", avl_root->altura);
    double avl_time_ms = 1000.0*(avl_end - avl_start)/CLOCKS_PER_SEC;
    printf("AVL ms == %f\n ", avl_time_ms);

    double map_time_ms = 1000.0*(map_end - map_start)/CLOCKS_PER_SEC;
    printf("\nMAP ms == %f ", map_time_ms);
    printf("deletes MAP == %d \n", map_deletes);

/*
    printf("\nRAIZ AVL == %d , ", avl_tree->raiz->dado);
    printf("altura AVL == %d ", avl_tree->raiz->altura);
    double avl_time_ms = 1000.0*(avl_end - avl_start)/CLOCKS_PER_SEC;
    printf("AVL ms == %f\n ", avl_time_ms);

    
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
