// Copyright (C) 2023 - Italo Portinho
// Para compilar(windows): g++ main.cpp -o main

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "redblack.hpp"

int main() {
    ArvoreRedBlack* rb_tree = new ArvoreRedBlack { .raiz = 0};
    int chave = 0;

    /************************************************************************/
    /********************** Operações na árvore RED-BLACK *******************/
    /************************************************************************/

    std::clock_t rb_start = std::clock();
    int rb_deletes = 0;
    for (int i = 0; i < 100000; i++) {
        // printf("\nIteracao: %d", i);
        chave = rand();
        Insert(rb_tree, chave);
        if (i > 100 && i % 100 == 0) {
            DeleteRB(rb_tree, rand());
            rb_deletes++;
        }
    }
    std::clock_t rb_end = std::clock();
    std::clock_t rb_search_start = std::clock();
    int rb_search_hits = 0;
    for (int i = 0; i < 100000; i++) {
        // printf("\nIteracao: %d", i);
        chave = rand();
        if (SearchRB(rb_tree, chave))
            rb_search_hits++;
    }
    std::clock_t rb_search_end = std::clock();

    /************************************************************************/
    /********************** Resultados RED-BLACK ****************************/
    /************************************************************************/
    printf("\nRAIZ RB == %d , ", rb_tree->raiz->dado);
    printf("altura RB == %d , ", calculaAltura(rb_tree->raiz, 0));
    printf("deletes RB == %d , ", rb_deletes);
    double rb_time_ms = 1000.0*(rb_end - rb_start)/CLOCKS_PER_SEC;
    printf("RB ms == %f , ", rb_time_ms);
    printf("search_hits_RB == %d , ", rb_search_hits);
    double rb_search_ms = 1000.0*(rb_search_end - rb_search_start)/CLOCKS_PER_SEC;
    printf("RB_search_ms ms == %f ", rb_search_ms);
}
