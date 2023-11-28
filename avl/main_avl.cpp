// Copyright (C) 2023 - Italo Portinho
// Para compilar(windows): g++ main.cpp -o main

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "avl.hpp"

int main() {
    ArvoreAVL* avl_tree = new ArvoreAVL{ .raiz = 0 };
    NoArvore* avl_root = 0;
    int chave = 0;

    /************************************************************************/
    /********************** Operações na árvore AVL *************************/
    /************************************************************************/
    std::clock_t avl_start = std::clock();
    int avl_deletes = 0;
    for (int i = 0; i < 100000; i++) {
        chave = rand();
        avl_root = InsertRec(avl_root, chave);
        if (i > 100 && i % 100 == 0) {
            // printf("\nIteracao: %d", i);
            avl_root = Delete(avl_root, rand());
            avl_deletes++;
        }
    }
    // printf("\n Terminou AVL. RAIZ == %d\n", avl_root->dado);
    // printf("\n Terminou AVL. ALTURA == %d\n", avl_root->altura);
    /*
    for (int i = 0; i < 5900; i++) {
        chave = rand();
        InsertIt(avl_tree, chave);
    }
    */
    std::clock_t avl_end = std::clock();

    /************************************************************************/
    /**************************** Resultados AVL ****************************/
    /************************************************************************/
    printf("\nRAIZ AVL == %d , ", avl_root->dado);
    printf("altura AVL == %d , ", avl_root->altura);
    printf("deletes AVL == %d , ", avl_deletes);
    double avl_time_ms = 1000.0*(avl_end - avl_start)/CLOCKS_PER_SEC;
    printf("AVL ms == %f\n ", avl_time_ms);
}
