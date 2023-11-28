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

    /************************************************************************/
    /********************** Operações na árvore AVL *************************/
    /************************************************************************/
    /*
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
    */
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

    /************************************************************************/
    /********************** Operações no std::map ***************************/
    /************************************************************************/
    /*
    std::clock_t map_start = std::clock();
    int map_deletes = 0;
    for (int i = 0; i < 100000; i++) {
        chave = rand();
        map_tree[chave] = chave;
        if (i > 100 && i % 100 == 0) {
            map_tree.extract(rand());
            map_deletes++;
        }
    }
    std::clock_t map_end = std::clock();
*/

    /************************************************************************/
    /********************** Resultados RED-BLACK ****************************/
    /************************************************************************/
    printf("\nRAIZ RB == %d , ", rb_tree->raiz->dado);
    printf("altura RB == %d , ", calculaAltura(rb_tree->raiz, 0));
    printf("deletes RB == %d , ", rb_deletes);
    double rb_time_ms = 1000.0*(rb_end - rb_start)/CLOCKS_PER_SEC;
    printf("RB ms == %f\n ", rb_time_ms);

    /************************************************************************/
    /**************************** Resultados AVL ****************************/
    /************************************************************************/
    //printf("\nRAIZ AVL == %d , ", avl_root->dado);
    //printf("altura AVL == %d , ", avl_root->altura);
    //printf("deletes AVL == %d , ", avl_deletes);
    //double avl_time_ms = 1000.0*(avl_end - avl_start)/CLOCKS_PER_SEC;
    //printf("AVL ms == %f\n ", avl_time_ms);

    /************************************************************************/
    /********************** Resultados std::map *****************************/
    /************************************************************************/
    //double map_time_ms = 1000.0*(map_end - map_start)/CLOCKS_PER_SEC;
    //printf("\nMAP ms == %f ", map_time_ms);
    //printf("deletes MAP == %d \n", map_deletes);
}
